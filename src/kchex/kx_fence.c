#include "kx_fence.h"
#include "kx_panic.h"

#include <stdlib.h>
#include <assert.h>

bool kx_fence_init(kx_fence_t* ck, uintptr_t membase, size_t memsize) {
    bool* shadowmem = (bool*) malloc(memsize);
    if (!shadowmem)
        return false;

    *ck = (kx_fence_t){
        .touched = shadowmem,
        .membase = membase,
        .memsize = memsize,
    };

    return true;
}

void kx_fence_on_store(kx_fence_t* ck, int core, uintptr_t pa, uintptr_t pc) {
    if (pa < ck->membase || pa >= ck->membase + ck->memsize) {
        return;
    }
    if (pa == 0x8023d178) {
        printf("%d: writing %lx, pc: %lx\n", core, pa, pc);
    }
    if (pa == 0x8025e97a) {
        printf("%d: writing %lx, pc: %lx\n", core, pa, pc);
    }
    ck->touched[pa - ck->membase] = true;
}

void kx_fence_on_exec(kx_fence_t* ck, int core, uintptr_t va, uintptr_t pa) {
    if (pa < ck->membase || pa >= ck->membase + ck->memsize) {
        return;
    }
    if (ck->touched[pa - ck->membase]) {
        printf("%d: ERROR: kx_fence: executed instruction without preceding fence, va: 0x%lx, pa: 0x%lx\n", core, va, pa);
        printf("auto fencing: ");
        kx_fence_on_fence(ck, core, va);
    }
}

void kx_fence_on_fence(kx_fence_t* ck, int core, uintptr_t pc) {
    printf("%d: fence.i, pc: %lx\n", core, pc);
    memset(ck->touched, 0, ck->memsize);
}

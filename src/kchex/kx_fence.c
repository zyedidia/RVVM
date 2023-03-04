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

void kx_fence_on_store(kx_fence_t* ck, uintptr_t pa) {
    if (pa < ck->membase || pa >= ck->membase + ck->memsize) {
        return;
    }
    ck->touched[pa - ck->membase] = true;
}

void kx_fence_on_exec(kx_fence_t* ck, uintptr_t va, uintptr_t pa) {
    if (pa < ck->membase || pa >= ck->membase + ck->memsize) {
        return;
    }
    if (ck->touched[pa - ck->membase]) {
        printf("kx_fence: va: 0x%lx, pa 0x%lx\n", va, pa);
        kx_panic("kx_fence: executed instruction without preceding fence");
    }
}

void kx_fence_on_fence(kx_fence_t* ck) {
    memset(ck->touched, 0, ck->memsize);
}

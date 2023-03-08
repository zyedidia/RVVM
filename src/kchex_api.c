#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void kx_panicf(const char* msg, ...) {
    printf("PANIC: ");
    va_list ap;
    va_start(ap, msg);
    vprintf(msg, ap);
    va_end(ap);
}

void* kx_malloc(size_t size) {
    return malloc(size);
}

void kx_free(void* p) {
    free(p);
}

#include "kx_vm.h"

kx_pte_t kx_vm_load_pte(kx_uintptr_t pt, int n) {
    (void) pt;
    (void) n;
    return (kx_pte_t) {};
}

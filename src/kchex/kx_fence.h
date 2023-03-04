#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    bool* touched;
    uintptr_t membase;
    size_t memsize;
} kx_fence_t;

bool kx_fence_init(kx_fence_t* ck, uintptr_t membase, size_t memsize);
void kx_fence_on_store(kx_fence_t* ck, uintptr_t pa);
void kx_fence_on_exec(kx_fence_t* ck, uintptr_t pa);
void kx_fence_on_fence(kx_fence_t* ck);

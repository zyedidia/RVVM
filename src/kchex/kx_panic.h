#pragma once

#include <stdio.h>
#include <stdlib.h>

static inline void kx_panic(const char* msg) {
    puts(msg);
    abort();
}

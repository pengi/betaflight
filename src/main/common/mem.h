#pragma once

#include <stdint.h>

typedef uint32_t mem_size_t;

void memInit(void);
void *memAlloc(mem_size_t size);
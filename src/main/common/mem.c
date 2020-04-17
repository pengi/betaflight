#include "common/mem.h"

#include <stddef.h>

#define MEM_HEAP_SIZE (16*1024)
#define MEM_HEAP_ALIGN 4

/* Make sure to be a properly aligned buffer */
union {
    uint8_t u8[MEM_HEAP_SIZE];
    uint32_t u32[MEM_HEAP_SIZE / 4];
} mem_heap_buf;
mem_size_t mem_heap_pos;


void memInit(void)
{
    mem_heap_pos = 0;
}

void *memAlloc(mem_size_t size)
{
    void *ret;
    /* Extend size to always be aligned to 32bit boundary */
    size = (size + MEM_HEAP_ALIGN - 1) & ~(MEM_HEAP_ALIGN - 1);

    if(mem_heap_pos + size > MEM_HEAP_SIZE) {
        return NULL;
    }

    ret = &mem_heap_buf.u8[mem_heap_pos];
    mem_heap_pos += size;
    return ret;
}
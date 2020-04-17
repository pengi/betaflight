#pragma once

#include <stdint.h>

#include "common/time.h"

#define FLOW_MAX_ARGS 11

typedef union flowValue_s {
    float f32;
} flowValue_t;

typedef struct flowStep_s flowStep_t;

typedef void (*flowHandler_t)(flowValue_t *regs, const flowStep_t *step);

struct flowStep_s {
    flowHandler_t handler;
    void *storage;
    uint16_t num_args;
    uint16_t args[FLOW_MAX_ARGS];
};

typedef struct flowContext_s {
    flowValue_t *vars;
    flowStep_t *steps;
    int num_steps;
    int max_steps;
    int max_vars;
} flowContext_t;

void flowInit(void);
void flowUpdate(timeUs_t currentTimeUs);
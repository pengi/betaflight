#pragma once

#include <stdint.h>

#include "common/time.h"
#include "scheduler/scheduler.h"

typedef union {
    float f32;
} flowValue_t;

typedef void (*flowHandler_t)(flowValue_t *outputs, const flowValue_t *inputs, const flowValue_t *params);

typedef struct {
    const char *ident;
    flowHandler_t handler;
    int num_in;
    int num_out;
    int num_params;
} flowNodeConfig_t;

#define FLOW_NODE_CONFIG_SECTION __attribute__ ((section(".flow_node_config"), used))

#define FLOW_NODE_CONFIG(_ident, _handler, _num_in, _num_out, _num_params) \
    static void _handler(flowValue_t *outputs, const flowValue_t *inputs, const flowValue_t *params); \
    extern const flowNodeConfig_t _handler ## _Config;                  \
    const flowNodeConfig_t _handler ## _Config FLOW_NODE_CONFIG_SECTION = { \
        .ident = _ident,                                                \
        .handler = _handler,                                            \
        .num_in = _num_in,                                              \
        .num_out = _num_out,                                            \
        .num_params = _num_params                                       \
    }                                                                   \
    /**/

void flowInit(void);
void flowUpdate(timeUs_t currentTimeUs);

const flowNodeConfig_t *flowGetNodeConfigByIndex(int index);
const flowNodeConfig_t *flowGetNodeConfigByName(const char *name);
int flowGetNodeConfigCount();
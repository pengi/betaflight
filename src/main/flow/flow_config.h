#pragma once

#include <stdbool.h>

#include "flow/flow.h"

typedef struct flowNodeConfig_s flowNodeConfig_t;

typedef bool (*flowBuilder_t)(flowContext_t *context, const flowNodeConfig_t *config, char *line);

#define FLOW_NODE_CONFIG_SECTION __attribute__ ((section(".flow_node_config"), used))

#define FLOW_NODE_CONFIG_CUSTOM(_ident, _handler, _builder, _min_params, _max_params) \
    static void _handler(flowValue_t *regs, const flowStep_t *step); \
    extern const flowNodeConfig_t _handler ## _Config;                  \
    const flowNodeConfig_t _handler ## _Config FLOW_NODE_CONFIG_SECTION = { \
        .ident = _ident,                                                \
        .handler = _handler,                                            \
        .builder = _builder,                                            \
        .min_params = _min_params,                                      \
        .max_params = _max_params,                                      \
    }                                                                   \
    /**/

#define FLOW_NODE_CONFIG(_ident, _handler, _min_params, _max_params) \
    FLOW_NODE_CONFIG_CUSTOM(_ident, _handler, flowConfigDefaultBuilder, _min_params, _max_params)

struct flowNodeConfig_s {
    const char *ident;
    flowHandler_t handler;
    flowBuilder_t builder;
    int min_params;
    int max_params;
};

const flowNodeConfig_t *flowConfigGetByIndex(int index);
const flowNodeConfig_t *flowConfigGetByName(const char *name);
int flowConfigGetCount();

bool flowConfigDefaultBuilder(flowContext_t *context, const flowNodeConfig_t *config, char *line);

bool flowConfigBuildStep(flowContext_t *context, char *line);
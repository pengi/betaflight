#include "flow/flow.h"

FLOW_NODE_CONFIG("const", flow_node_in_const, 0, 1, 1);
void flow_node_in_const(flowValue_t *outputs, const flowValue_t *inputs, const flowValue_t *params)
{
    (void)inputs;
    outputs[0] = params[0];
}

FLOW_NODE_CONFIG("mult_f", flow_node_mult_f, 1, 2, 0);
void flow_node_mult_f(flowValue_t *outputs, const flowValue_t *inputs, const flowValue_t *params)
{
    (void)params;
    outputs[0].f32 = inputs[0].f32 * inputs[1].f32;
}

FLOW_NODE_CONFIG("mult_cf", flow_node_mult_cf, 1, 1, 1);
void flow_node_mult_cf(flowValue_t *outputs, const flowValue_t *inputs, const flowValue_t *params)
{
    outputs[0].f32 = inputs[0].f32 * params[0].f32;
}
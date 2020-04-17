#include "flow/flow.h"
#include "flow/flow_config.h"

FLOW_NODE_CONFIG("mult", flow_node_mult_f, 2, FLOW_MAX_ARGS);
void flow_node_mult_f(flowValue_t *regs, const flowStep_t *step)
{
    int i;
    float out = 1.0f;
    for(i=1; i<step->num_args; i++) {
        out *= regs[step->args[i]].f32;
    }
    regs[step->args[0]].f32 = out;
}

FLOW_NODE_CONFIG("add", flow_node_add_f, 2, FLOW_MAX_ARGS);
void flow_node_add_f(flowValue_t *regs, const flowStep_t *step)
{
    int i;
    float out = 0.0f;
    for(i=1; i<step->num_args; i++) {
        out += regs[step->args[i]].f32;
    }
    regs[step->args[0]].f32 = out;
}
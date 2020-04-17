#include "flow/flow.h"
#include "flow/flow_config.h"
#include "rx/rx.h"

FLOW_NODE_CONFIG("rx_input", flow_node_rx_input, 1, FLOW_MAX_ARGS);
void flow_node_rx_input(flowValue_t *regs, const flowStep_t *step)
{
    uint16_t i;
    for(i=0; i<step->num_args; i++) {
        regs[step->args[i]].f32 = (rcData[i] - 1500) / 500.0f;
    }
}
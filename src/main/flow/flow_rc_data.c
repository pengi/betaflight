#include "flow/flow.h"
#include "rx/rx.h"

FLOW_NODE_CONFIG("rx_input", flow_node_rx_input, 0, 8, 0);
void flow_node_rx_input(flowValue_t *outputs, const flowValue_t *inputs, const flowValue_t *params)
{
    int i;
    (void)inputs;
    (void)params;
    for(i=0; i<8; i++) {
        outputs[i].f32 = (rcData[i] - 1500) / 500.0f;
    }
}
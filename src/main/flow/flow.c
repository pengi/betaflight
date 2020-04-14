#include "flow/flow.h"

extern const flowNodeConfig_t __flow_node_config_start[];
extern const flowNodeConfig_t __flow_node_config_end[];

const flowNodeConfig_t *flowGetNodeConfig(int index) {
    return &__flow_node_config_start[index];
}
int flowGetNodeConfigCount() {
    return __flow_node_config_end - __flow_node_config_start;
}

void flowInit(void) {
}
#include "flow/flow.h"
#include "flow/flow_config.h"

#include <string.h>
#include <stdlib.h>

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

FLOW_NODE_CONFIG("div", flow_node_div_f, 3, 3);
void flow_node_div_f(flowValue_t *regs, const flowStep_t *step)
{
    regs[step->args[0]].f32 = regs[step->args[1]].f32 / regs[step->args[2]].f32;
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

FLOW_NODE_CONFIG_CUSTOM("const", flow_node_const_f, flow_node_const_builder_f, 2, 2);
bool flow_node_const_builder_f(flowContext_t *context, const struct flowNodeConfig_s *config, char *line)
{
    char *saveptr;
    char *argstr;
    int var_id;

    (void)config;

    /* field id */
    argstr = strtok_r(line, " ", &saveptr);
    if(argstr == NULL) {
        return false;
    }
    var_id = atoi(argstr);

    /* Value */
    argstr = strtok_r(NULL, " ", &saveptr);
    if(argstr == NULL) {
        return false;
    }
    context->vars[var_id].f32 = atoi(argstr)/1000.0f;

    /* end of string */
    argstr = strtok_r(NULL, " ", &saveptr);
    if(argstr != NULL) {
        return false;
    }

    /* Success */
    return true;
}
void flow_node_const_f(flowValue_t *regs, const flowStep_t *step)
{
    (void)regs;
    (void)step;
}
#include "flow/flow_config.h"

#include <string.h>
#include <stdlib.h>

extern const flowNodeConfig_t __flow_node_config_start[];
extern const flowNodeConfig_t __flow_node_config_end[];

const flowNodeConfig_t *flowConfigGetByIndex(int index)
{
    return &__flow_node_config_start[index];
}

const flowNodeConfig_t *flowConfigGetByName(const char *name)
{
    const flowNodeConfig_t *cur;
    for(cur = __flow_node_config_start; cur < __flow_node_config_end; cur++) {
        if(0==strcmp(cur->ident, name)) {
            return cur;
        }
    }
    return NULL;
}

int flowConfigGetCount()
{
    return __flow_node_config_end - __flow_node_config_start;
}

bool flowConfigDefaultBuilder(flowContext_t *context, const struct flowNodeConfig_s *config, char *line) {
    flowStep_t *step;
    char *saveptr;
    char *argstr;
    int arg;

    if(context->num_steps >= context->max_steps) {
        return false;
    }

    step = &context->steps[context->num_steps];
    step->handler = config->handler;
    step->storage = NULL;

    for (arg = 0, argstr = strtok_r(line, " ", &saveptr);
        arg < config->max_params &&  argstr != NULL;
        arg++, argstr = strtok_r(NULL, " ", &saveptr))
    {
        step->args[arg] = (uint16_t)atoi(argstr);
    }

    if(arg < config->min_params || arg > config->max_params) {
        return false;
    }

    step->num_args = arg;

    context->num_steps++;
    return true;
}

bool flowConfigBuildStep(flowContext_t *context, char *line) {
    char *args;
    const flowNodeConfig_t *config;

    args = strchr(line, ' ');
    if(args == NULL) {
        return false;
    }

    /* Split string */
    *args = '\0';
    args++;

    /* Locate config */
    config = flowConfigGetByName(line);
    if(config == NULL) {
        return false;
    }

    /* Build */
    return config->builder(context, config, args);
}
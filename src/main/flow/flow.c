#include "flow/flow.h"
#include "common/time.h"

#include <string.h>

extern const flowNodeConfig_t __flow_node_config_start[];
extern const flowNodeConfig_t __flow_node_config_end[];


static const flowNodeConfig_t *program[8];
static int program_length;

const flowNodeConfig_t *flowGetNodeConfigByIndex(int index)
{
    return &__flow_node_config_start[index];
}

const flowNodeConfig_t *flowGetNodeConfigByName(const char *name)
{
    const flowNodeConfig_t *cur;
    for(cur = __flow_node_config_start; cur < __flow_node_config_end; cur++) {
        if(0==strcmp(cur->ident, name)) {
            return cur;
        }
    }
    return NULL;
}

int flowGetNodeConfigCount()
{
    return __flow_node_config_end - __flow_node_config_start;
}

void flowInit(void)
{
    int i;

    program_length = 0;
    program[program_length++] = flowGetNodeConfigByName("servo_output");

    for(i=0; i<program_length; i++) {
        if(program[i] == NULL) {
            /* Not a complete program, bail out */
            return;
        }
    }
    setTaskEnabled(TASK_FLOW, true);
}

void flowUpdate(timeUs_t currentTimeUs) {
    int i,j;
    flowValue_t input[8];
    flowValue_t output[8];
    flowValue_t params[8];

    (void)currentTimeUs;

    for(j=0; j<8; j++) {
        params[i].f32 = 0.5f;
        input[i].f32 = 0.5f;
    }

    for(i=0; i<program_length; i++) {
        program[i]->handler(output, input, params);

        for(j=0; j<8; j++) {
            input[j] = output[j];
        }
    }
}
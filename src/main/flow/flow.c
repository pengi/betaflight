#include "flow/flow.h"
#include "flow/flow_config.h"
#include "common/mem.h"
#include "common/time.h"
#include "scheduler/scheduler.h"

#include <string.h>

#define FLOW_NUM_VARS 64
#define FLOW_NUM_STEPS 64

static flowContext_t ctx;

const char * const program[] = {
    "rx_input 0 1 2 3",
    "add 4 0 2",
    "add 5 1 3",
    "servo_output 4 5",
    NULL
};

void flowInit(void)
{
    char tmpline[128];
    int i;
    ctx.max_vars = FLOW_NUM_VARS;
    ctx.max_steps = FLOW_NUM_STEPS;
    ctx.num_steps = 0;

    ctx.vars = memAlloc(sizeof(flowValue_t)*ctx.max_vars);
    ctx.steps = memAlloc(sizeof(flowStep_t)*ctx.max_steps);

    for(i=0; program[i] != NULL; i++) {
        strcpy(tmpline, program[i]);
        if(!flowConfigBuildStep(&ctx, tmpline)) {
            return;
        }
    }

    setTaskEnabled(TASK_FLOW, true);
}

void flowUpdate(timeUs_t currentTimeUs) {
    int i;
    (void)currentTimeUs;
    for(i=0; i<ctx.num_steps; i++) {
        ctx.steps[i].handler(ctx.vars, &ctx.steps[i]);
    }
}
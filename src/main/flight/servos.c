/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Betaflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "platform.h"

#ifdef USE_SERVOS

#include "common/maths.h"

#include "config/config_reset.h"

#include "drivers/pwm_output.h"

#include "flight/servos.h"

#include "flow/flow.h"

#include "pg/pg.h"
#include "pg/pg_ids.h"

#include "rx/rx.h"

#define CHANNEL_FORWARDING_DISABLED (uint8_t)0xFF

PG_REGISTER_ARRAY_WITH_RESET_FN(servoParam_t, MAX_SUPPORTED_SERVOS, servoParams, PG_SERVO_PARAMS, 0);

void pgResetFn_servoParams(servoParam_t *instance)
{
    for (int i = 0; i < MAX_SUPPORTED_SERVOS; i++) {
        RESET_CONFIG(servoParam_t, &instance[i],
            .min = DEFAULT_SERVO_MIN,
            .max = DEFAULT_SERVO_MAX,
            .middle = DEFAULT_SERVO_MIDDLE,
            .rate = 100,
            .forwardFromChannel = CHANNEL_FORWARDING_DISABLED
        );
    }
}

PG_REGISTER_WITH_RESET_FN(servoConfig_t, servoConfig, PG_SERVO_CONFIG, 0);

void pgResetFn_servoConfig(servoConfig_t *servoConfig)
{
    servoConfig->dev.servoCenterPulse = 1500;
    servoConfig->dev.servoPwmRate = 50;
    servoConfig->tri_unarmed_servo = 1;
    servoConfig->servo_lowpass_freq = 0;
    servoConfig->channelForwardingStartChannel = 0;

    for (unsigned servoIndex = 0; servoIndex < MAX_SUPPORTED_SERVOS; servoIndex++) {
        servoConfig->dev.ioTags[servoIndex] = timerioTagGetByUsage(TIM_USE_SERVO, servoIndex);
    }
}

void servosInit(void)
{
}

FLOW_NODE_CONFIG("servo_output", flow_servo_output, 8, 0, 0);
void flow_servo_output(flowValue_t *outputs, const flowValue_t *inputs, const flowValue_t *params)
{
    (void)outputs;
    (void)params;
    for (uint8_t i = 0; i < MAX_SUPPORTED_SERVOS; i++) {
        const servoParam_t *param = servoParams(i);
        int16_t value;
        if(inputs[i].f32 < 0.0f) {
            value = param->middle - (int16_t)(inputs[i].f32 * (param->min - param->middle));
        } else {
            value = param->middle + (int16_t)(inputs[i].f32 * (param->max - param->middle));
        }
        pwmWriteServo(i, constrain(value, param->min, param->max));
    }
}
#endif // USE_SERVOS

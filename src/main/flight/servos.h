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

#pragma once

#include "pg/pg.h"
#include "drivers/io_types.h"
#include "drivers/pwm_output.h"

typedef struct servoParam_s {
    uint32_t reversedSources;               // the direction of servo movement for each input source of the servo mixer, bit set=inverted
    int16_t min;                            // servo min
    int16_t max;                            // servo max
    int16_t middle;                         // servo middle
    int8_t rate;                            // range [-125;+125] ; can be used to adjust a rate 0-125% and a direction
    int8_t forwardFromChannel;              // RX channel index, 0 based.  See CHANNEL_FORWARDING_DISABLED
} servoParam_t;

PG_DECLARE_ARRAY(servoParam_t, MAX_SUPPORTED_SERVOS, servoParams);

typedef struct servoConfig_s {
    servoDevConfig_t dev;
    uint16_t servo_lowpass_freq;            // lowpass servo filter frequency selection; 1/1000ths of loop freq
    uint8_t tri_unarmed_servo;              // send tail servo correction pulses even when unarmed
    uint8_t channelForwardingStartChannel;
} servoConfig_t;

PG_DECLARE(servoConfig_t, servoConfig);

void servoMixerLoadMix(int index);
void loadCustomServoMixer(void);
void servoConfigureOutput(void);
void servosInit(void);
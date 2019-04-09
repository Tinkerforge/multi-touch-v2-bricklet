/* multi-touch-v2-bricklet
 * Copyright (C) 2018-2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * mpr121.c: Driver for MPR121
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "mpr121.h"
#include "configs/config_mpr121.h"

#include "bricklib2/os/coop_task.h"
#include "bricklib2/hal/i2c_fifo/i2c_fifo.h"
#include "bricklib2/hal/system_timer/system_timer.h"
#include "bricklib2/utility/util_definitions.h"

#include "communication.h"

MPR121 mpr121;
CoopTask mpr121_task;

const uint8_t mpr121_config[][2] = {
    // Touch

	// Rising (when the electrode data is greater than the baseline value).
	{MPR121_MHD_R, 0x01}, // Largest magnitude of variation to pass through baseline filter (1-63).
	{MPR121_NHD_R, 0x01}, // Incremental Change when non-noise drift is detected (1-63).
	{MPR121_NCL_R, 0x00}, // Number of samples consecutively greater than the Max Half Delta value (0-255).
	{MPR121_FDL_R, 0x00}, // Operation rate of the filter A larger count limit means the filter delay is operating more slowly (0-255).
	// Falling (when the electrode data is less than the baseline value).
	{MPR121_MHD_F, 0x01},
	{MPR121_NHD_F, 0x01},
	{MPR121_NCL_F, 0xFF},
	{MPR121_FDL_F, 0x02},

	// Proximity

	// Rising
	{MPR121_PROX_MHD_R, 0xFF},
	{MPR121_PROX_NHDA_R, 0xFF},
	{MPR121_PROX_NCL_R, 0x00},
	{MPR121_PROX_FDL_R, 0x00},
    // Falling
	{MPR121_PROX_MHD_F, 0x01},
	{MPR121_PROX_NHDA_F, 0x01},
	{MPR121_PROX_NCL_F, 0xFF},
	{MPR121_PROX_NDL_F, 0xFF},

	// Thresholds

	// Touch
	{MPR121_ELE0_T, MPR121_TOUCH_THRESHOLD},
	{MPR121_ELE0_R, MPR121_RELEASE_THRESHOLD},
	{MPR121_ELE1_T, MPR121_TOUCH_THRESHOLD},
	{MPR121_ELE1_R, MPR121_RELEASE_THRESHOLD},
	{MPR121_ELE2_T, MPR121_TOUCH_THRESHOLD},
	{MPR121_ELE2_R, MPR121_RELEASE_THRESHOLD},
	{MPR121_ELE3_T, MPR121_TOUCH_THRESHOLD},
	{MPR121_ELE3_R, MPR121_RELEASE_THRESHOLD},
	{MPR121_ELE4_T, MPR121_TOUCH_THRESHOLD},
	{MPR121_ELE4_R, MPR121_RELEASE_THRESHOLD},
	{MPR121_ELE5_T, MPR121_TOUCH_THRESHOLD},
	{MPR121_ELE5_R, MPR121_RELEASE_THRESHOLD},
	{MPR121_ELE6_T, MPR121_TOUCH_THRESHOLD},
	{MPR121_ELE6_R, MPR121_RELEASE_THRESHOLD},
	{MPR121_ELE7_T, MPR121_TOUCH_THRESHOLD},
	{MPR121_ELE7_R, MPR121_RELEASE_THRESHOLD},
	{MPR121_ELE8_T, MPR121_TOUCH_THRESHOLD},
	{MPR121_ELE8_R, MPR121_RELEASE_THRESHOLD},
	{MPR121_ELE9_T, MPR121_TOUCH_THRESHOLD},
	{MPR121_ELE9_R, MPR121_RELEASE_THRESHOLD},
	{MPR121_ELE10_T, MPR121_TOUCH_THRESHOLD},
	{MPR121_ELE10_R, MPR121_RELEASE_THRESHOLD},
	{MPR121_ELE11_T, MPR121_TOUCH_THRESHOLD},
	{MPR121_ELE11_R, MPR121_RELEASE_THRESHOLD},
	// Proximity
	{MPR121_PROX_T, MPR121_PROXIMITY_TOUCH_THRESHOLD},
	{MPR121_PROX_R, MPR121_PROXIMITY_RELEASE_THRESHOLD},

	// Auto Config

	{MPR121_ATO_CFGU, MPR121_ELECTRODE_SENSITIVITY_MAX},
//	{MPR121_ATO_CFGL, MPR121_TL_TO_UTL(ELECTRODE_SENSITIVITY_DEFAULT)},
//	{MPR121_ATO_CFGT, ELECTRODE_SENSITIVITY_DEFAULT},
	{MPR121_ATO_CFG0, 0x03},

	{MPR121_ENDOFCONFIG, 0}
};

void mpr121_task_write_register(const uint8_t reg, const uint8_t value) {
	i2c_fifo_coop_write_register(&mpr121.i2c_fifo, reg, 1, &value, true);
}

void mpr121_task_reset(void) {
	mpr121_task_write_register(MPR121_SOFT_RESET, 0x63);
}

void mpr121_task_disable(void) {
	mpr121_task_write_register(MPR121_ELE_CFG, 0x00);
}

void mpr121_task_update_sensitivity(void) {
	mpr121_task_write_register(MPR121_ATO_CFGL, MPR121_TL_TO_UTL(mpr121.sensitivity));
	mpr121_task_write_register(MPR121_ATO_CFGT, mpr121.sensitivity);
}

void mpr121_task_enable(void) {
	uint16_t value = mpr121.enabled_electrodes & 0xFFF;
	if(mpr121.enabled_electrodes & (1 << 12)) {
		value |= MPR121_ELE_CFG_ELEPROX_EN_11;
	}

	mpr121_task_write_register(MPR121_ELE_CFG, value);
}

void mpr121_task_configure(void) {
	mpr121_task_update_sensitivity();

	for(uint8_t i = 0; mpr121_config[i][0] != MPR121_ENDOFCONFIG; i++) {
		mpr121_task_write_register(mpr121_config[i][0], mpr121_config[i][1]);
	}
}

void mpr121_task_recalibrate(void) {
	mpr121_task_reset();
	coop_task_sleep_ms(2);
	mpr121_task_disable();
	mpr121_task_configure();
	mpr121_task_enable();

	mpr121.force_read = true;
}

void mpr121_task_tick(void) {
	mpr121_task_recalibrate();
	coop_task_sleep_ms(2);

	while(true) {
		if(mpr121.recalibrate) {
			mpr121.recalibrate = false;
			mpr121_task_recalibrate();
		}

		if(mpr121.new_sensitivity) {
			mpr121.new_sensitivity = false;
			mpr121_task_update_sensitivity();
		}

		if(mpr121.new_enabled_electrodes) {
			mpr121.new_enabled_electrodes = false;
			mpr121_task_enable();
		}

		if(!XMC_GPIO_GetInput(MPR121_INT_PIN) || mpr121.force_read) {
			mpr121.force_read = false;

			uint16_t new_state = 0;
			i2c_fifo_coop_read_register(&mpr121.i2c_fifo, MPR121_ELE07_T, 2, (uint8_t*)&new_state);
			mpr121.state = new_state & mpr121.enabled_electrodes;
			if(mpr121.led.config == MULTI_TOUCH_V2_TOUCH_LED_CONFIG_SHOW_TOUCH) {
				if(mpr121.state == 0) {
					XMC_GPIO_SetOutputHigh(MPR121_TOUCH_LED_PIN);
				} else {
					XMC_GPIO_SetOutputLow(MPR121_TOUCH_LED_PIN);
				}
			}
		}
		coop_task_yield();
	}
}

void mpr121_init_i2c(void) {
	mpr121.i2c_fifo.baudrate         = MPR121_I2C_BAUDRATE;
	mpr121.i2c_fifo.address          = MPR121_I2C_ADDRESS;
	mpr121.i2c_fifo.i2c              = MPR121_I2C;

	mpr121.i2c_fifo.scl_port         = MPR121_SCL_PORT;
	mpr121.i2c_fifo.scl_pin          = MPR121_SCL_PIN;
	mpr121.i2c_fifo.scl_mode         = MPR121_SCL_PIN_MODE;
	mpr121.i2c_fifo.scl_input        = MPR121_SCL_INPUT;
	mpr121.i2c_fifo.scl_source       = MPR121_SCL_SOURCE;
	mpr121.i2c_fifo.scl_fifo_size    = MPR121_SCL_FIFO_SIZE;
	mpr121.i2c_fifo.scl_fifo_pointer = MPR121_SCL_FIFO_POINTER;

	mpr121.i2c_fifo.sda_port         = MPR121_SDA_PORT;
	mpr121.i2c_fifo.sda_pin          = MPR121_SDA_PIN;
	mpr121.i2c_fifo.sda_mode         = MPR121_SDA_PIN_MODE;
	mpr121.i2c_fifo.sda_input        = MPR121_SDA_INPUT;
	mpr121.i2c_fifo.sda_source       = MPR121_SDA_SOURCE;
	mpr121.i2c_fifo.sda_fifo_size    = MPR121_SDA_FIFO_SIZE;
	mpr121.i2c_fifo.sda_fifo_pointer = MPR121_SDA_FIFO_POINTER;

	i2c_fifo_init(&mpr121.i2c_fifo);
}

void mpr121_init(void) {
	memset(&mpr121, 0, sizeof(MPR121));

	mpr121.enabled_electrodes = 0x1FFF;
	mpr121.sensitivity        = MPR121_ELECTRODE_SENSITIVITY_DEFAULT;
	mpr121.led.config         = MULTI_TOUCH_V2_TOUCH_LED_CONFIG_SHOW_TOUCH;

	mpr121_init_i2c();

	const XMC_GPIO_CONFIG_t config_high = {
		.mode                = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
		.output_level        = XMC_GPIO_OUTPUT_LEVEL_HIGH,
	};

	const XMC_GPIO_CONFIG_t config_pullup = {
		.mode                = XMC_GPIO_MODE_INPUT_PULL_UP,
		.input_hysteresis    = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
	};

	XMC_GPIO_Init(MPR121_TOUCH_LED_PIN, &config_high);
	XMC_GPIO_Init(MPR121_INT_PIN, &config_pullup);
	coop_task_init(&mpr121_task, mpr121_task_tick);
}

void mpr121_tick(void) {
	if(mpr121.led.config != MULTI_TOUCH_V2_TOUCH_LED_CONFIG_SHOW_TOUCH) {
		led_flicker_tick(&mpr121.led, system_timer_get_ms(), MPR121_TOUCH_LED_PIN);
	}
	coop_task_tick(&mpr121_task);
}

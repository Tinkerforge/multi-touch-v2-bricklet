/* multi-touch-v2-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.c: TFP protocol message handling
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

#include "communication.h"

#include "bricklib2/utility/communication_callback.h"
#include "bricklib2/utility/util_definitions.h"
#include "bricklib2/protocols/tfp/tfp.h"

#include "mpr121.h"
#include "configs/config_mpr121.h"

#include "xmc_gpio.h"

BootloaderHandleMessageResponse handle_message(const void *message, void *response) {
	switch(tfp_get_fid_from_message(message)) {
		case FID_GET_TOUCH_STATE: return get_touch_state(message, response);
		case FID_SET_TOUCH_STATE_CALLBACK_CONFIGURATION: return set_touch_state_callback_configuration(message);
		case FID_GET_TOUCH_STATE_CALLBACK_CONFIGURATION: return get_touch_state_callback_configuration(message, response);
		case FID_RECALIBRATE: return recalibrate(message);
		case FID_SET_ELECTRODE_CONFIG: return set_electrode_config(message);
		case FID_GET_ELECTRODE_CONFIG: return get_electrode_config(message, response);
		case FID_SET_ELECTRODE_SENSITIVITY: return set_electrode_sensitivity(message);
		case FID_GET_ELECTRODE_SENSITIVITY: return get_electrode_sensitivity(message, response);
		case FID_SET_TOUCH_LED_CONFIG: return set_touch_led_config(message);
		case FID_GET_TOUCH_LED_CONFIG: return get_touch_led_config(message, response);
		default: return HANDLE_MESSAGE_RESPONSE_NOT_SUPPORTED;
	}
}


BootloaderHandleMessageResponse get_touch_state(const GetTouchState *data, GetTouchState_Response *response) {
	response->header.length = sizeof(GetTouchState_Response);
	response->state         = mpr121.state & 0x1FFF;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse set_touch_state_callback_configuration(const SetTouchStateCallbackConfiguration *data) {
	mpr121.touch_state_period              = data->period;
	mpr121.touch_state_value_has_to_change = data->value_has_to_change;

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_touch_state_callback_configuration(const GetTouchStateCallbackConfiguration *data, GetTouchStateCallbackConfiguration_Response *response) {
	response->header.length       = sizeof(GetTouchStateCallbackConfiguration_Response);
	response->period              = mpr121.touch_state_period;
	response->value_has_to_change = mpr121.touch_state_value_has_to_change;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse recalibrate(const Recalibrate *data) {
	mpr121.recalibrate = true;

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse set_electrode_config(const SetElectrodeConfig *data) {
	mpr121.enabled_electrodes     = data->enabled_electrodes & 0x1FFF;
	mpr121.new_enabled_electrodes = true;

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_electrode_config(const GetElectrodeConfig *data, GetElectrodeConfig_Response *response) {
	response->header.length      = sizeof(GetElectrodeConfig_Response);
	response->enabled_electrodes = mpr121.enabled_electrodes;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse set_electrode_sensitivity(const SetElectrodeSensitivity *data) {
	mpr121.sensitivity     = BETWEEN(MPR121_ELECTRODE_SENSITIVITY_MIN, data->sensitivity, MPR121_ELECTRODE_SENSITIVITY_MAX);
	mpr121.new_sensitivity = true;

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_electrode_sensitivity(const GetElectrodeSensitivity *data, GetElectrodeSensitivity_Response *response) {
	response->header.length = sizeof(GetElectrodeSensitivity_Response);
	response->sensitivity   = mpr121.sensitivity;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse set_touch_led_config(const SetTouchLEDConfig *data) {
	if(data->config > MULTI_TOUCH_V2_TOUCH_LED_CONFIG_SHOW_TOUCH) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	mpr121.led.config = data->config;
	if(data->config == MULTI_TOUCH_V2_TOUCH_LED_CONFIG_OFF) {
		XMC_GPIO_SetOutputHigh(MPR121_TOUCH_LED_PIN);
	} else if((data->config == MULTI_TOUCH_V2_TOUCH_LED_CONFIG_ON) || ((data->config == MULTI_TOUCH_V2_TOUCH_LED_CONFIG_SHOW_TOUCH) && (mpr121.state != 0))) {
		XMC_GPIO_SetOutputLow(MPR121_TOUCH_LED_PIN);
	}

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_touch_led_config(const GetTouchLEDConfig *data, GetTouchLEDConfig_Response *response) {
	response->header.length = sizeof(GetTouchLEDConfig_Response);
	response->config        = mpr121.led.config;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}


bool handle_touch_state_callback(void) {
	static bool is_buffered = false;
	static TouchState_Callback cb;
	static uint16_t last_state = 0;
	static uint32_t last_time = 0;

	if(!is_buffered) {
		if(mpr121.touch_state_period == 0 || !system_timer_is_time_elapsed_ms(last_time, mpr121.touch_state_period)) {
			return false;
		}

		if(mpr121.touch_state_value_has_to_change && last_state == mpr121.state) {
			return false;
		}

		tfp_make_default_header(&cb.header, bootloader_get_uid(), sizeof(TouchState_Callback), FID_CALLBACK_TOUCH_STATE);
		cb.state   = mpr121.state;
		last_state = mpr121.state;
		last_time  = system_timer_get_ms();
	}

	if(bootloader_spitfp_is_send_possible(&bootloader_status.st)) {
		bootloader_spitfp_send_ack_and_message(&bootloader_status, (uint8_t*)&cb, sizeof(TouchState_Callback));
		is_buffered = false;
		return true;
	} else {
		is_buffered = true;
	}

	return false;
}

void communication_tick(void) {
	communication_callback_tick();
}

void communication_init(void) {
	communication_callback_init();
}

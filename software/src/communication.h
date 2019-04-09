/* multi-touch-v2-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.h: TFP protocol message handling
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

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include <stdbool.h>

#include "bricklib2/protocols/tfp/tfp.h"
#include "bricklib2/bootloader/bootloader.h"

// Default functions
BootloaderHandleMessageResponse handle_message(const void *data, void *response);
void communication_tick(void);
void communication_init(void);

// Constants
#define MULTI_TOUCH_V2_TOUCH_LED_CONFIG_OFF 0
#define MULTI_TOUCH_V2_TOUCH_LED_CONFIG_ON 1
#define MULTI_TOUCH_V2_TOUCH_LED_CONFIG_SHOW_HEARTBEAT 2
#define MULTI_TOUCH_V2_TOUCH_LED_CONFIG_SHOW_TOUCH 3

#define MULTI_TOUCH_V2_BOOTLOADER_MODE_BOOTLOADER 0
#define MULTI_TOUCH_V2_BOOTLOADER_MODE_FIRMWARE 1
#define MULTI_TOUCH_V2_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2
#define MULTI_TOUCH_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3
#define MULTI_TOUCH_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

#define MULTI_TOUCH_V2_BOOTLOADER_STATUS_OK 0
#define MULTI_TOUCH_V2_BOOTLOADER_STATUS_INVALID_MODE 1
#define MULTI_TOUCH_V2_BOOTLOADER_STATUS_NO_CHANGE 2
#define MULTI_TOUCH_V2_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3
#define MULTI_TOUCH_V2_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4
#define MULTI_TOUCH_V2_BOOTLOADER_STATUS_CRC_MISMATCH 5

#define MULTI_TOUCH_V2_STATUS_LED_CONFIG_OFF 0
#define MULTI_TOUCH_V2_STATUS_LED_CONFIG_ON 1
#define MULTI_TOUCH_V2_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2
#define MULTI_TOUCH_V2_STATUS_LED_CONFIG_SHOW_STATUS 3

// Function and callback IDs and structs
#define FID_GET_TOUCH_STATE 1
#define FID_SET_TOUCH_STATE_CALLBACK_CONFIGURATION 2
#define FID_GET_TOUCH_STATE_CALLBACK_CONFIGURATION 3
#define FID_RECALIBRATE 5
#define FID_SET_ELECTRODE_CONFIG 6
#define FID_GET_ELECTRODE_CONFIG 7
#define FID_SET_ELECTRODE_SENSITIVITY 8
#define FID_GET_ELECTRODE_SENSITIVITY 9
#define FID_SET_TOUCH_LED_CONFIG 10
#define FID_GET_TOUCH_LED_CONFIG 11

#define FID_CALLBACK_TOUCH_STATE 4

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetTouchState;

typedef struct {
	TFPMessageHeader header;
	uint16_t state;
} __attribute__((__packed__)) GetTouchState_Response;

typedef struct {
	TFPMessageHeader header;
	uint32_t period;
	bool value_has_to_change;
} __attribute__((__packed__)) SetTouchStateCallbackConfiguration;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetTouchStateCallbackConfiguration;

typedef struct {
	TFPMessageHeader header;
	uint32_t period;
	bool value_has_to_change;
} __attribute__((__packed__)) GetTouchStateCallbackConfiguration_Response;

typedef struct {
	TFPMessageHeader header;
	uint16_t state;
} __attribute__((__packed__)) TouchState_Callback;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) Recalibrate;

typedef struct {
	TFPMessageHeader header;
	uint16_t enabled_electrodes;
} __attribute__((__packed__)) SetElectrodeConfig;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetElectrodeConfig;

typedef struct {
	TFPMessageHeader header;
	uint16_t enabled_electrodes;
} __attribute__((__packed__)) GetElectrodeConfig_Response;

typedef struct {
	TFPMessageHeader header;
	uint8_t sensitivity;
} __attribute__((__packed__)) SetElectrodeSensitivity;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetElectrodeSensitivity;

typedef struct {
	TFPMessageHeader header;
	uint8_t sensitivity;
} __attribute__((__packed__)) GetElectrodeSensitivity_Response;

typedef struct {
	TFPMessageHeader header;
	uint8_t config;
} __attribute__((__packed__)) SetTouchLEDConfig;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetTouchLEDConfig;

typedef struct {
	TFPMessageHeader header;
	uint8_t config;
} __attribute__((__packed__)) GetTouchLEDConfig_Response;


// Function prototypes
BootloaderHandleMessageResponse get_touch_state(const GetTouchState *data, GetTouchState_Response *response);
BootloaderHandleMessageResponse set_touch_state_callback_configuration(const SetTouchStateCallbackConfiguration *data);
BootloaderHandleMessageResponse get_touch_state_callback_configuration(const GetTouchStateCallbackConfiguration *data, GetTouchStateCallbackConfiguration_Response *response);
BootloaderHandleMessageResponse recalibrate(const Recalibrate *data);
BootloaderHandleMessageResponse set_electrode_config(const SetElectrodeConfig *data);
BootloaderHandleMessageResponse get_electrode_config(const GetElectrodeConfig *data, GetElectrodeConfig_Response *response);
BootloaderHandleMessageResponse set_electrode_sensitivity(const SetElectrodeSensitivity *data);
BootloaderHandleMessageResponse get_electrode_sensitivity(const GetElectrodeSensitivity *data, GetElectrodeSensitivity_Response *response);
BootloaderHandleMessageResponse set_touch_led_config(const SetTouchLEDConfig *data);
BootloaderHandleMessageResponse get_touch_led_config(const GetTouchLEDConfig *data, GetTouchLEDConfig_Response *response);

// Callbacks
bool handle_touch_state_callback(void);

#define COMMUNICATION_CALLBACK_TICK_WAIT_MS 1
#define COMMUNICATION_CALLBACK_HANDLER_NUM 1
#define COMMUNICATION_CALLBACK_LIST_INIT \
	handle_touch_state_callback, \


#endif

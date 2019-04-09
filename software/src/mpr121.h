/* multi-touch-v2-bricklet
 * Copyright (C) 2018-2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * mpr121.h: Driver for MPR121
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

#ifndef MPR121_H
#define MPR121_H

#include <stdint.h>

#include "bricklib2/hal/i2c_fifo/i2c_fifo.h"
#include "bricklib2/utility/led_flicker.h"

typedef struct {
	I2CFifo i2c_fifo;

	bool new_enabled_electrodes;
	uint16_t enabled_electrodes;

	bool new_sensitivity;
	uint8_t sensitivity;

	uint16_t state;

	uint32_t touch_state_period;
	bool touch_state_value_has_to_change;

	bool recalibrate;
	bool force_read;

	LEDFlickerState led;
} MPR121;

extern MPR121 mpr121;

void mpr121_init(void);
void mpr121_tick(void);


#define MPR121_TOUCH_THRESHOLD              0x1F
#define MPR121_RELEASE_THRESHOLD            0x1A
#define MPR121_PROXIMITY_TOUCH_THRESHOLD    0x34
#define MPR121_PROXIMITY_RELEASE_THRESHOLD  0x30

#define MPR121_ELE07_T     0x00
#define MPR121_ELE811_T    0x01
#define MPR121_ELE07_OOR   0x02
#define MPR121_ELE811_OOR  0x03
#define MPR121_ELE0_F_LSB  0x04
#define MPR121_ELE0_F_MSB  0x05
#define MPR121_ELE1_F_LSB  0x06
#define MPR121_ELE1_F_MSB  0x07
#define MPR121_ELE2_F_LSB  0x08
#define MPR121_ELE2_F_MSB  0x09
#define MPR121_ELE3_F_LSB  0x0A
#define MPR121_ELE3_F_MSB  0x0B
#define MPR121_ELE4_F_LSB  0x0C
#define MPR121_ELE4_F_MSB  0x0D
#define MPR121_ELE5_F_LSB  0x0E
#define MPR121_ELE5_F_MSB  0x0F
#define MPR121_ELE6_F_LSB  0x10
#define MPR121_ELE6_F_MSB  0x11
#define MPR121_ELE7_F_LSB  0x12
#define MPR121_ELE7_F_MSB  0x13
#define MPR121_ELE8_F_LSB  0x14
#define MPR121_ELE8_F_MSB  0x15
#define MPR121_ELE9_F_LSB  0x16
#define MPR121_ELE9_F_MSB  0x17
#define MPR121_ELE10_F_LSB 0x18
#define MPR121_ELE10_F_MSB 0x19
#define MPR121_ELE11_F_LSB 0x1A
#define MPR121_ELE11_F_MSB 0x1B
#define MPR121_ELEPROX_LSB 0x1C
#define MPR121_ELEPROX_MSB 0x1D
#define MPR121_E0BV        0x1E
#define MPR121_E1BV        0x1F
#define MPR121_E2BV        0x20
#define MPR121_E3BV        0x21
#define MPR121_E4BV        0x22
#define MPR121_E5BV        0x23
#define MPR121_E6BV        0x24
#define MPR121_E7BV        0x25
#define MPR121_E8BV        0x26
#define MPR121_E9BV        0x27
#define MPR121_E10BV       0x28
#define MPR121_E11BV       0x29
#define MPR121_EPROXBV     0x2A
#define MPR121_MHD_R       0x2B
#define MPR121_NHD_R       0x2C
#define MPR121_NCL_R       0x2D
#define MPR121_FDL_R       0x2E
#define MPR121_MHD_F       0x2F
#define MPR121_NHD_F       0x30
#define MPR121_NCL_F       0x31
#define MPR121_FDL_F       0x32
#define MPR121_PROX_MHD_R  0x36
#define MPR121_PROX_NHDA_R 0x37
#define MPR121_PROX_NCL_R  0x38
#define MPR121_PROX_FDL_R  0x39
#define MPR121_PROX_MHD_F  0x3A
#define MPR121_PROX_NHDA_F 0x3B
#define MPR121_PROX_NCL_F  0x3C
#define MPR121_PROX_NDL_F  0x3D
#define MPR121_PROX_NHDAT  0x3E
#define MPR121_PROX_NCLT   0x3F
#define MPR121_PROX_FDLT   0x40
#define MPR121_ELE0_T      0x41
#define MPR121_ELE0_R      0x42
#define MPR121_ELE1_T      0x43
#define MPR121_ELE1_R      0x44
#define MPR121_ELE2_T      0x45
#define MPR121_ELE2_R      0x46
#define MPR121_ELE3_T      0x47
#define MPR121_ELE3_R      0x48
#define MPR121_ELE4_T      0x49
#define MPR121_ELE4_R      0x4A
#define MPR121_ELE5_T      0x4B
#define MPR121_ELE5_R      0x4C
#define MPR121_ELE6_T      0x4D
#define MPR121_ELE6_R      0x4E
#define MPR121_ELE7_T      0x4F
#define MPR121_ELE7_R      0x50
#define MPR121_ELE8_T      0x51
#define MPR121_ELE8_R      0x52
#define MPR121_ELE9_T      0x53
#define MPR121_ELE9_R      0x54
#define MPR121_ELE10_T     0x55
#define MPR121_ELE10_R     0x56
#define MPR121_ELE11_T     0x57
#define MPR121_ELE11_R     0x58
#define MPR121_PROX_T      0x59
#define MPR121_PROX_R      0x5A
#define MPR121_DEBOUNCE    0x5B
#define MPR121_FIL_CFG_CDC 0x5C
#define MPR121_FIL_CFG_CDT 0x5D
#define MPR121_ELE_CFG     0x5E
#define MPR121_GPIO_CTRL0  0x73
#define MPR121_GPIO_CTRL1  0x74
#define MPR121_GPIO_DATA   0x75
#define MPR121_GPIO_DIR    0x76
#define MPR121_GPIO_EN     0x77
#define MPR121_GPIO_SET    0x78
#define MPR121_GPIO_CLEAR  0x79
#define MPR121_GPIO_TOGGLE 0x7A
#define MPR121_ATO_CFG0    0x7B
#define MPR121_ATO_CFGU    0x7D
#define MPR121_ATO_CFGL    0x7E
#define MPR121_ATO_CFGT    0x7F
#define MPR121_SOFT_RESET  0x80

#define MPR121_ENDOFCONFIG 0xFF

#define MPR121_FIL_CFG_CDC_FFI_00       (0b00 << 6)
#define MPR121_FIL_CFG_CDC_FFI_01       (0b01 << 6)
#define MPR121_FIL_CFG_CDC_FFI_10       (0b10 << 6)
#define MPR121_FIL_CFG_CDC_FFI_11       (0b11 << 6)
#define MPR121_FIL_CFG_CDC_CDC_ENC(x)   (x) // Charge Discharge Current

#define MPR121_FIL_CFG_CDT_CDT(x)       ((x) << 5) // Charge Discharge Time
#define MPR121_FIL_CFG_CDT_SFI(x)       ((x) << 3) // Second Filter Iterations
#define MPR121_FIL_CFG_CDT_ESI(x)       (x) // Electrode Sample Interval

#define MPR121_ELE_CFG_ENABLE_ALL       0x0C
#define MPR121_ELE_CFG_ELEPROX_EN_00    (0b00 << 4)
#define MPR121_ELE_CFG_ELEPROX_EN_01    (0b01 << 4)
#define MPR121_ELE_CFG_ELEPROX_EN_10    (0b10 << 4)
#define MPR121_ELE_CFG_ELEPROX_EN_11    (0b11 << 4)
#define MPR121_ELE_CFG_CL_00            (0b00 << 6)
#define MPR121_ELE_CFG_CL_01            (0b01 << 6)
#define MPR121_ELE_CFG_CL_10            (0b10 << 6)
#define MPR121_ELE_CFG_CL_11            (0b11 << 6)

#define MPR121_ELECTRODE_SENSITIVITY_DEFAULT  0xB5 // Default value taken from MPR121 datasheet
#define MPR121_ELECTRODE_SENSITIVITY_MIN      0x05
#define MPR121_ELECTRODE_SENSITIVITY_MAX      0xC9

#define MPR121_TL_TO_UTL(x) ((x)*72/100) // LSL = USL*0.65 == TL*0.72!

#endif
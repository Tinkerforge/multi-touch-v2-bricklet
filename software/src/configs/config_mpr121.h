/* multi-touch-v2-bricklet
 * Copyright (C) 2018 Olaf Lüke <olaf@tinkerforge.com>
 *
 * config_mpr121.h: Config for MPR121
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

#ifndef CONFIG_MPR121
#define CONFIG_MPR121

#include "xmc_gpio.h"
#include "xmc_i2c.h"

#define MPR121_TOUCH_LED_PIN             P1_0
#define MPR121_INT_PIN                   P0_9

#define MPR121_I2C_BAUDRATE              400000

#define MPR121_I2C_ADDRESS               0b1011010 // 0x5A
#define MPR121_I2C                       XMC_I2C0_CH1

#define MPR121_SCL_PORT                  XMC_GPIO_PORT0
#define MPR121_SCL_PIN                   8
#define MPR121_SCL_PIN_MODE              XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7
#define MPR121_SCL_INPUT                 XMC_USIC_CH_INPUT_DX1
#define MPR121_SCL_SOURCE                1
#define MPR121_SCL_FIFO_SIZE             XMC_USIC_CH_FIFO_SIZE_16WORDS
#define MPR121_SCL_FIFO_POINTER          32

#define MPR121_SDA_PORT                  XMC_GPIO_PORT0
#define MPR121_SDA_PIN                   6
#define MPR121_SDA_PIN_MODE              XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7
#define MPR121_SDA_INPUT                 XMC_USIC_CH_INPUT_DX0
#define MPR121_SDA_SOURCE                2
#define MPR121_SDA_FIFO_SIZE             XMC_USIC_CH_FIFO_SIZE_16WORDS
#define MPR121_SDA_FIFO_POINTER          48


#define MPR121_CONF_I2C_BAUDRATE         400000

#define MPR121_CONF_I2C_ADDRESS          0b0010000 // 0x10
#define MPR121_CONF_I2C                  XMC_I2C0_CH1

#define MPR121_CONF_SCL_PORT             XMC_GPIO_PORT
#define MPR121_CONF_SCL_PIN              3
#define MPR121_CONF_SCL_PIN_MODE         XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7
#define MPR121_CONF_SCL_INPUT            XMC_USIC_CH_INPUT_DX1
#define MPR121_CONF_SCL_SOURCE           0
#define MPR121_CONF_SCL_FIFO_SIZE        XMC_USIC_CH_FIFO_SIZE_16WORDS
#define MPR121_CONF_SCL_FIFO_POINTER     32

#define MPR121_CONF_SDA_PORT             XMC_GPIO_PORT0
#define MPR121_CONF_SDA_PIN              7
#define MPR121_CONF_SDA_PIN_MODE         XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7
#define MPR121_CONF_SDA_INPUT            XMC_USIC_CH_INPUT_DX0
#define MPR121_CONF_SDA_SOURCE           3
#define MPR121_CONF_SDA_FIFO_SIZE        XMC_USIC_CH_FIFO_SIZE_16WORDS
#define MPR121_CONF_SDA_FIFO_POINTER     48

#endif
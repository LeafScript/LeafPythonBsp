/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-19     RealThread   first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <stm32f4xx.h>
#include <drv_common.h>


#ifdef __cplusplus
extern "C"
{
#endif

/*-------------------------- CHIP CONFIG BEGIN --------------------------*/

#define CHIP_FAMILY_STM32
#define CHIP_SERIES_STM32F4
#define CHIP_NAME_STM32F429ZI

/*-------------------------- CHIP CONFIG END --------------------------*/

/*-------------------------- ROM/RAM CONFIG BEGIN --------------------------*/

#define ROM_START              ((uint32_t)0x08000000)
#define ROM_SIZE               (2048 * 1024)
#define ROM_END                ((uint32_t)(ROM_START + ROM_SIZE))

#define RAM_START              (0x20000000)
#define RAM_SIZE               (192 * 1024)
#define RAM_END                (RAM_START + RAM_SIZE)

/*-------------------------- ROM/RAM CONFIG END --------------------------*/

/*-------------------------- CLOCK CONFIG BEGIN --------------------------*/

#define BSP_CLOCK_SOURCE                  ("HSI")
#define BSP_CLOCK_SOURCE_FREQ_MHZ         ((int32_t)0)
#define BSP_CLOCK_SYSTEM_FREQ_MHZ         ((int32_t)180)

/*-------------------------- CLOCK CONFIG END --------------------------*/

/*-------------------------- UART CONFIG BEGIN --------------------------*/

/** After configuring corresponding UART or UART DMA, you can use it.
 *
 * STEP 1, define macro define related to the serial port opening based on the serial port number
 *                 such as     #define BSP_USING_UART1
 *
 * STEP 2, according to the corresponding pin of serial port, define the related serial port information macro
 *                 such as     #define BSP_UART1_TX_PIN       "PA9"
 *                             #define BSP_UART1_RX_PIN       "PA10"
 *
 * STEP 3, if you want using SERIAL DMA, you must open it in the RT-Thread Settings.
 *                 RT-Thread Setting -> Components -> Device Drivers -> Serial Device Drivers -> Enable Serial DMA Mode
 *
 * STEP 4, according to serial port number to define serial port tx/rx DMA function in the board.h file
 *                 such as     #define BSP_UART1_RX_USING_DMA
 *
 */

#define BSP_USING_UART1
#define BSP_UART1_TX_PIN       "PA9"
#define BSP_UART1_RX_PIN       "PA10"

/*-------------------------- UART CONFIG END --------------------------*/

/*-------------------------- I2C CONFIG BEGIN --------------------------*/

/** if you want to use i2c bus(soft simulate) you can use the following instructions.
 *
 * STEP 1, open i2c driver framework(soft simulate) support in the RT-Thread Settings file
 *
 * STEP 2, define macro related to the i2c bus
 *                 such as     #define BSP_USING_I2C1
 *
 * STEP 3, according to the corresponding pin of i2c port, modify the related i2c port and pin information
 *                 such as     #define BSP_I2C1_SCL_PIN    GET_PIN(port, pin)   ->   GET_PIN(C, 11)
 *                             #define BSP_I2C1_SDA_PIN    GET_PIN(port, pin)   ->   GET_PIN(C, 12)
 */

/*#define BSP_USING_I2C1*/
#ifdef BSP_USING_I2C1
#define BSP_I2C1_SCL_PIN    GET_PIN(port, pin)
#define BSP_I2C1_SDA_PIN    GET_PIN(port, pin)
#endif

/*#define BSP_USING_I2C2*/
#ifdef BSP_USING_I2C2
#define BSP_I2C2_SCL_PIN    GET_PIN(port, pin)
#define BSP_I2C2_SDA_PIN    GET_PIN(port, pin)
#endif

/*-------------------------- I2C CONFIG END --------------------------*/

/*-------------------------- SPI CONFIG BEGIN --------------------------*/

/** if you want to use spi bus you can use the following instructions.
 *
 * STEP 1, open spi driver framework support in the RT-Thread Settings file
 *
 * STEP 2, define macro related to the spi bus
 *                 such as     #define BSP_USING_SPI1
 *
 * STEP 3, copy your spi init function from stm32xxxx_hal_msp.c generated by stm32cubemx to the end of board.c file
 *                 such as     void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
 *
 * STEP 4, modify your stm32xxxx_hal_config.h file to support spi peripherals. define macro related to the peripherals
 *                 such as     #define HAL_SPI_MODULE_ENABLED
 */

/*#define BSP_USING_SPI1*/
/*#define BSP_USING_SPI2*/
/*#define BSP_USING_SPI3*/

/*-------------------------- SPI CONFIG END --------------------------*/

/*-------------------------- QSPI CONFIG BEGIN --------------------------*/

/** if you want to use qspi you can use the following instructions.
 *
 * STEP 1, open qspi driver framework support in the RT-Thread Settings file
 *
 * STEP 2, define macro related to the qspi
 *                 such as     #define BSP_USING_QSPI
 *
 * STEP 3, copy your qspi init function from stm32xxxx_hal_msp.c generated by stm32cubemx to the end of board.c file
 *                 such as     void HAL_QSPI_MspInit(QSPI_HandleTypeDef* hqspi)
 *
 * STEP 4, modify your stm32xxxx_hal_config.h file to support qspi peripherals. define macro related to the peripherals
 *                 such as     #define HAL_QSPI_MODULE_ENABLED
 *
 */

/*#define BSP_USING_QSPI*/

/*-------------------------- QSPI CONFIG END --------------------------*/

/*-------------------------- PWM CONFIG BEGIN --------------------------*/

/** if you want to use pwm you can use the following instructions.
 *
 * STEP 1, open pwm driver framework support in the RT-Thread Settings file
 *
 * STEP 2, define macro related to the pwm
 *                 such as     #define BSP_USING_PWM1
 *
 * STEP 3, copy your pwm timer init function from stm32xxxx_hal_msp.c generated by stm32cubemx to the end if board.c file
 *                 such as     void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)  and
 *                             void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
 *
 * STEP 4, modify your stm32xxxx_hal_config.h file to support pwm peripherals. define macro related to the peripherals
 *                 such as     #define HAL_TIM_MODULE_ENABLED
 *
 */

/*#define BSP_USING_PWM1*/
/*#define BSP_USING_PWM2*/
/*#define BSP_USING_PWM3*/

/*-------------------------- PWM CONFIG END --------------------------*/

/*-------------------------- ADC CONFIG BEGIN --------------------------*/

/** if you want to use adc you can use the following instructions.
 *
 * STEP 1, open adc driver framework support in the RT-Thread Settings file
 *
 * STEP 2, define macro related to the adc
 *                 such as     #define BSP_USING_ADC1
 *
 * STEP 3, copy your adc init function from stm32xxxx_hal_msp.c generated by stm32cubemx to the end of board.c file
 *                 such as     void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
 *
 * STEP 4, modify your stm32xxxx_hal_config.h file to support adc peripherals. define macro related to the peripherals
 *                 such as     #define HAL_ADC_MODULE_ENABLED
 *
 */

/*#define BSP_USING_ADC1*/
/*#define BSP_USING_ADC2*/
/*#define BSP_USING_ADC3*/

/*-------------------------- ADC CONFIG END --------------------------*/

/*-------------------------- WDT CONFIG BEGIN --------------------------*/

/** if you want to use wdt you can use the following instructions.
 *
 * STEP 1, open wdt driver framework support in the RT-Thread Settings file
 *
 * STEP 2, modify your stm32xxxx_hal_config.h file to support wdt peripherals. define macro related to the peripherals
 *                 such as     #define HAL_IWDG_MODULE_ENABLED
 *
 */

/*-------------------------- WDT CONFIG END --------------------------*/

/*-------------------------- HARDWARE TIMER CONFIG BEGIN --------------------------*/

/** if you want to use hardware timer you can use the following instructions.
 *
 * STEP 1, open hwtimer driver framework support in the RT-Thread Settings file
 *
 * STEP 2, define macro related to the hwtimer
 *                 such as     #define BSP_USING_TIM  and
 *                             #define BSP_USING_TIM1
 *
 * STEP 3, copy your hardwire timer init function from stm32xxxx_hal_msp.c generated by stm32cubemx to the end of board.c file
 *                 such as     void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
 *
 * STEP 4, modify your stm32xxxx_hal_config.h file to support hardwere timer peripherals. define macro related to the peripherals
 *                 such as     #define HAL_TIM_MODULE_ENABLED
 *
 */

/*#define BSP_USING_TIM*/
#ifdef BSP_USING_TIM
/*#define BSP_USING_TIM15*/
/*#define BSP_USING_TIM16*/
/*#define BSP_USING_TIM17*/
#endif

/*-------------------------- HAREWARE TIMER CONFIG END --------------------------*/

/*-------------------------- RTC CONFIG BEGIN --------------------------*/

/** if you want to use rtc(hardware) you can use the following instructions.
 *
 * STEP 1, open rtc driver framework(hardware) support in the RT-Thread Settings file
 *
 * STEP 2, define macro related to the rtc
 *                 such as    BSP_USING_ONCHIP_RTC
 *
 * STEP 3, modify your stm32xxxx_hal_config.h file to support rtc peripherals. define macro related to the peripherals
 *                 such as     #define HAL_RTC_MODULE_ENABLED
 *
 */
/*#define BSP_USING_ONCHIP_RTC*/

/*-------------------------- RTC CONFIG END --------------------------*/

/*-------------------------- SDIO CONFIG BEGIN --------------------------*/

/** if you want to use sdio you can use the following instructions.
 *
 * STEP 1, open sdio driver framework support in the RT-Thread Settings file
 *
 * STEP 2, define macro related to the sdio
 *                 such as    BSP_USING_SDIO
 *
 * STEP 3, copy your sdio init function from stm32xxxx_hal_msp.c generated by stm32cubemx to the end of board.c file
 *                 such as     void HAL_SD_MspInit(SD_HandleTypeDef* hsd)
 *
 * STEP 4, modify your stm32xxxx_hal_config.h file to support sdio peripherals. define macro related to the peripherals
 *                 such as     #define HAL_SD_MODULE_ENABLED
 *
 * STEP 5, config your device file system or another applications
 *
 */

/*#define BSP_USING_SDIO*/

/*-------------------------- SDIO CONFIG END --------------------------*/

/*-------------------------- ETH CONFIG BEGIN --------------------------*/

/** if you want to use eth you can use the following instructions.
 *
 * STEP 1, define macro related to the eth
 *                 such as    BSP_USING_ETH
 *
 * STEP 2, copy your eth init function from stm32xxxx_hal_msp.c generated by stm32cubemx to the end if board.c file
 *                 such as     void HAL_ETH_MspInit(ETH_HandleTypeDef* heth)
 *
 * STEP 3, modify your stm32xxxx_hal_config.h file to support eth peripherals. define macro related to the peripherals
 *                 such as     #define HAL_ETH_MODULE_ENABLED
 *
 * STEP 4, config your phy type
 *                 such as     #define PHY_USING_LAN8720A
 *                             #define PHY_USING_DM9161CEP
 *                             #define PHY_USING_DP83848C
 * STEP 5, implement your phy reset function in the end of board.c file
 *                 void phy_reset(void)
 *
 * STEP 6, config your lwip or other network stack
 *
 */

/*#define BSP_USING_ETH*/
#ifdef BSP_USING_ETH
/*#define PHY_USING_LAN8720A*/
/*#define PHY_USING_DM9161CEP*/
/*#define PHY_USING_DP83848C*/
#endif
/*-------------------------- ETH CONFIG END --------------------------*/

/*-------------------------- USB HOST CONFIG BEGIN --------------------------*/

/** if you want to use usb host you can use the following instructions.
 *
 * STEP 1, open usb host driver framework support in the RT-Thread Settings file
 *
 * STEP 2, define macro related to the usb host
 *                 such as    BSP_USING_USBHOST
 *
 * STEP 3, copy your usb host init function from stm32xxxx_hal_msp.c generated by stm32cubemx to the end of board.c file
 *                 such as     void HAL_HCD_MspInit(HCD_HandleTypeDef* hhcd)
 *
 * STEP 4, config your usb peripheral clock in SystemClock_Config() generated by STM32CubeMX and replace this function in board.c
 *
 * STEP 5, modify your stm32xxxx_hal_config.h file to support usb host peripherals. define macro related to the peripherals
 *                 such as     #define HAL_HCD_MODULE_ENABLED
 *
 */

/*#define BSP_USING_USBHOST*/

/*-------------------------- USB HOST CONFIG END --------------------------*/

/*-------------------------- USB DEVICE CONFIG BEGIN --------------------------*/

/** if you want to use usb device you can use the following instructions.
 *
 * STEP 1, open usb device driver framework support in the RT-Thread Settings file
 *
 * STEP 2 define macro related to the usb device
 *                 such as    BSP_USING_USBDEVICE
 *
 * STEP 3, copy your usb device init function from stm32xxxx_hal_msp.c generated by stm32cubemx to the end of board.c file
 *                 such as     void HAL_PCD_MspInit(PCD_HandleTypeDef* hpcd)
 *
 * STEP 4, config your usb peripheral clock in SystemClock_Config() generated by STM32CubeMX and replace this function in board.c
 *
 * STEP 5, modify your stm32xxxx_hal_config.h file to support usb device peripherals. define macro related to the peripherals
 *                 such as     #define HAL_PCD_MODULE_ENABLED
 *
 */

/*#define BSP_USING_USBDEVICE*/

/*-------------------------- USB DEVICE CONFIG END --------------------------*/

/*-------------------------- ON_CHIP_FLASH CONFIG BEGIN --------------------------*/

/** if you want to use on chip flash you can use the following instructions.
 *
 * STEP 1 define macro related to the on chip flash
 *                 such as    BSP_USING_ON_CHIP_FLASH
 *
 * STEP 2, modify your stm32xxxx_hal_config.h file to support on chip flash peripherals. define macro related to the peripherals
 *                 such as     #define HAL_FLASH_MODULE_ENABLED
 *
 */

/*#define BSP_USING_ON_CHIP_FLASH*/

/*-------------------------- ON_CHIP_FLASH CONFIG END --------------------------*/

/*-------------------------- BSP_USING_SDRAM CONFIG BEGIN --------------------------*/

#define BSP_USING_SDRAM

/* parameters for sdram peripheral */
/* Bank1 or Bank2 */
#define SDRAM_TARGET_BANK               1
/* stm32f4 Bank1:0XC0000000  Bank2:0XD0000000 */
#define SDRAM_BANK_ADDR                 ((uint32_t)0XC0000000)
/* data width: 8, 16, 32 */
#define SDRAM_DATA_WIDTH                16
/* column bit numbers: 8, 9, 10, 11 */
#define SDRAM_COLUMN_BITS               9
/* row bit numbers: 11, 12, 13 */
#define SDRAM_ROW_BITS                  13
/* cas latency clock number: 1, 2, 3 */
#define SDRAM_CAS_LATENCY               3
/* read pipe delay: 0, 1, 2 */
#define SDRAM_RPIPE_DELAY               1
/* clock divid: 2, 3 */
#define SDCLOCK_PERIOD                  2
/* refresh rate counter */
#define SDRAM_REFRESH_COUNT             ((uint32_t)0x02AB)
#define SDRAM_SIZE                      ((uint32_t)0x2000000)

/* Timing configuration for W9825G6KH-6 */
/* 90 MHz of SD clock frequency (180MHz/2) */
/* TMRD: 2 Clock cycles */
#define LOADTOACTIVEDELAY               2
/* TXSR: 7x11.90ns */
#define EXITSELFREFRESHDELAY            8
/* TRAS: 4x11.90ns */
#define SELFREFRESHTIME                 6
/* TRC:  7x11.90ns */
#define ROWCYCLEDELAY                   6
/* TWR:  2 Clock cycles */
#define WRITERECOVERYTIME               2
/* TRP:  2x11.90ns */
#define RPDELAY                         2
/* TRCD: 2x11.90ns */
#define RCDDELAY                        2

/* memory mode register */
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

/*-------------------------- BSP_USING_SDRAM CONFIG END --------------------------*/

/*-------------------------- BSP_USING_LCD CONFIG BEGIN --------------------------*/

#define BSP_USING_LCD

#define LCD_WIDTH           800
#define LCD_HEIGHT          480
#define LCD_BITS_PER_PIXEL  16
#define LCD_BUF_SIZE        (LCD_WIDTH * LCD_HEIGHT * LCD_BITS_PER_PIXEL / 8)
#define LCD_PIXEL_FORMAT    RTGRAPHIC_PIXEL_FORMAT_RGB565

#define LCD_HSYNC_WIDTH     2
#define LCD_VSYNC_HEIGHT    2
#define LCD_HBP             46
#define LCD_VBP             23
#define LCD_HFP             22
#define LCD_VFP             22

#define LCD_BACKLIGHT_USING_GPIO
#define LCD_BL_GPIO_NUM     GET_PIN(D, 7)
#define LCD_DISP_GPIO_NUM   GET_PIN(D, 4)

/*-------------------------- BSP_USING_LCD CONFIG END --------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */

/*!
 * @file       apm32e10x_rtc.h
 *
 * @brief      This file contains all the functions prototypes for the RTC firmware library
 *
 * @version    V1.0.0
 *
 * @date       2021-07-26
 *
 */

#ifndef __APM32E10X_RTC_H
#define __APM32E10X_RTC_H

#include "apm32e10x.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup RTC_Driver RTC Driver
  @{
*/

/** @addtogroup RTC_Enumerations Enumerations
  @{
*/

typedef enum
{
    RTC_FLAG_OC    = 0x0020,    //!< RTC Operation Complete flag
    RTC_FLAG_RSYNC = 0x0008,    //!< Registers Synchronized flag
    RTC_FLAG_OVR   = 0x0004,    //!< Overflow flag
    RTC_FLAG_ALR   = 0x0002,    //!< Alarm flag
    RTC_FLAG_SEC   = 0x0001     //!< Second flag
} RTC_FLAG_T;

typedef enum
{
    RTC_INT_OVR = 0x0004,       //!< Overflow interrupt
    RTC_INT_ALR = 0x0002,       //!< Alarm interrupt
    RTC_INT_SEC = 0x0001        //!< Second interrupt
} RTC_INT_T;

/**@} end of group RTC_Enumerations*/


/** @addtogroup RTC_Fuctions Fuctions
  @{
*/

/** Operation modes */
void RTC_EnableConfigMode(void);
void RTC_DisableConfigMode(void);

/** Configuration */
uint32_t RTC_ReadCounter(void);
void RTC_ConfigCounter(uint32_t value);
void RTC_ConfigPrescaler(uint32_t value);
void RTC_ConfigAlarm(uint32_t value);
uint32_t RTC_ReadDivider(void);
void RTC_WaitForLastTask(void);
void RTC_WaitForSynchor(void);

/** Interrupts and flags */
void RTC_EnableInterrupt(uint16_t interrupt);
void RTC_DisableInterrupt(uint16_t interrupt);
uint8_t RTC_ReadStatusFlag(RTC_FLAG_T flag);
void RTC_ClearStatusFlag(uint16_t flag);
uint8_t RTC_ReadIntFlag(RTC_INT_T flag);
void RTC_ClearIntFlag(uint16_t flag);

/**@} end of group RTC_Fuctions*/
/**@} end of group RTC_Driver*/
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32E10X_RTC_H */

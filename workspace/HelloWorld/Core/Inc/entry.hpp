/*
 * entry.hpp
 *
 *  Created on: Jun 5, 2023
 *      Author: JERZSTAN
 */

#ifndef INC_ENTRY_HPP_
#define INC_ENTRY_HPP_

#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_rtc.h"

#ifdef __cplusplus
extern "C" {
#endif

void Init();
void CheckAndSwitchLights();
void http_listen();
void TriggerScheduler(RTC_TimeTypeDef sTime, RTC_DateTypeDef sDate);
const char * TimeToString(RTC_TimeTypeDef sTime, RTC_DateTypeDef sDate);

#ifdef __cplusplus
}
#endif

#endif /* INC_ENTRY_HPP_ */
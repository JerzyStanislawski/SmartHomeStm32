/*
 * entry.c
 *
 *  Created on: Jun 5, 2023
 *      Author: JERZSTAN
 */

#include "entry.hpp"
#include "HttpServer.hpp"
#include "stm32f7xx_hal_rtc.h"

#ifdef __cplusplus
extern "C" {
#endif

Lights lights;
Blinds blinds;
Scheduler scheduler(&lights, &blinds);
Board board(&scheduler);
HttpServer server(board);

void Init()
{
	board.ResetHolidaySettings();
}

void http_listen()
{
	server.http_thread();
}

void TriggerScheduler(RTC_TimeTypeDef sTime, RTC_DateTypeDef sDate)
{
	scheduler.Execute(sTime.Hours, sTime.Minutes, sTime.Seconds);
	board.TimerEvent(sTime, sDate);
}

void CheckAndSwitchLights()
{
	lights.CheckAndSwitchLights();
}

const char * TimeToString(RTC_TimeTypeDef sTime, RTC_DateTypeDef sDate)
{
	std::string time = "Time: ";
	time += std::to_string(sTime.Hours);
	time += ":";
	time += std::to_string(sTime.Minutes);
	time += ":";
	time += std::to_string(sTime.Seconds);
	time += "\n";
	time += "Date: ";
	time += std::to_string(sDate.Year);
	time += "-";
	time += std::to_string(sDate.Month);
	time += "-";
	time += std::to_string(sDate.Date);
	time += "\n";

	//length = time.length();
	return time.c_str();
}

#ifdef __cplusplus
}
#endif

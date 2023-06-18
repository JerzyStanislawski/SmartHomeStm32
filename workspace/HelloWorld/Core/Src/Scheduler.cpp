/*
 * Scheduler.cpp
 *
 *  Created on: May 7, 2023
 *      Author: JERZSTAN
 */

#include "scheduler.hpp"
#include "FLASH_SECTOR_F4.h"
#include <memory>

TimeRecord::TimeRecord(byte roomId, RecordType type, byte hour, byte minute, byte days, bool onOrUp)
{
	this->roomId = roomId;
	this->type = type;
	this->hour = hour;
	this->minute = minute;
	this->onOrUp = onOrUp;
	this->days = days;
}

TimeRecord Scheduler::Add(std::string room, RecordType type, byte hour, byte minute, byte days, bool onOrUp)
{
	byte id = (byte)2;//type == RecordType::LIGHTS ? lights->GetId(room) : blinds->GetId(room);
	records[count] = TimeRecord(id, type, hour, minute, days, onOrUp);
	count++;

	return records[count - 1];
}

void Scheduler::Schedule(string * records, int recordsCount)
{
	  uint32_t address = startAddress;
	  Flash_Write_Data(address, reinterpret_cast<uint8_t*>(&recordsCount), sizeof(int), true);
	  address += sizeof(int);

	  count = 0;
	  for (int i = 0; i < recordsCount; i++)
	  {
	      int comma = records[i].find(',');
	      std::string room = records[i].substr(0, comma);
	      std::string type = records[i].substr(comma + 1, 1);
	      byte hours = (byte)atoi(records[i].substr(comma + 3, 2).c_str());
	      byte minutes = (byte)atoi(records[i].substr(comma + 6, 2).c_str());
	      byte days = (byte)atoi(records[i].substr(comma + 9, 3).c_str());
	      byte onOrUp = (byte)atoi(records[i].substr(comma + 13, 1).c_str());

	      TimeRecord record = Add(room, type == "L" ? RecordType::LIGHTS : RecordType::BLINDS, hours, minutes, days, onOrUp == (byte)1);

	      Flash_Write_Data(address, reinterpret_cast<uint8_t*>(&record), sizeof(TimeRecord), false);
	      address += sizeof(TimeRecord);
	  }
}

void Scheduler::Clear()
{
	count = 0;
	Flash_Write_Data(startAddress, reinterpret_cast<uint8_t*>(&count), sizeof(int), true);
}

void Scheduler::Execute(int hour, int minute, int currentDay)
{
	for (int i = 0; i < count; i++)
	{
		TimeRecord record = records[i];

		if ((int)record.hour == hour && (int)record.minute == minute && ((int)record.days & (1 << (int)currentDay)) == (1 << (int)currentDay))
		{
			if (record.type == RecordType::LIGHTS)
				lights->SwitchLight(lights->GetNameById(record.roomId), record.onOrUp ? true : false);
			else
				blinds->MoveBlind(blinds->GetNameById(record.roomId));
		}
	}
}

std::string Scheduler::GetEvents()
{
	 std::string output = "2";
 	 for (int i = 0; i < count; i++)
	 {
		 TimeRecord record = records[i];

		 char hourStr[2];
		 char minuteStr[2];
		 char daysStr[3];
		 itoa((int)record.hour, hourStr, 10);
		 itoa((int)record.minute, minuteStr, 10);
		 itoa((int)record.days, daysStr, 10);

		 //output += record.type == RecordType::LIGHTS ? lights->GetNameById(record.roomId) : blinds->GetNameById(record.roomId);
		 output += ",";
		 output += record.type == RecordType::LIGHTS ? "L" : "B";
		 output += ",";
		 output += hourStr;
		 output += ":";
		 output += minuteStr;
		 output += ",";
		 output += daysStr;
		 output += ",";
		 output += record.onOrUp ? "1" : "0";
		 output += ";\n";
	 }
	 return output;
}

void Scheduler::RestoreScheduledEvents()
{
	uint32_t address = startAddress;
	Flash_Read_Data(address, reinterpret_cast<uint8_t*>(&count), sizeof(int));

	address += sizeof(int);
	for (int i = 0; i < count; i++)
	{
		TimeRecord record;
		Flash_Read_Data(address, reinterpret_cast<uint8_t*>(&record), sizeof(TimeRecord));
		records[i] = record;
		address += sizeof(TimeRecord);
	}
}

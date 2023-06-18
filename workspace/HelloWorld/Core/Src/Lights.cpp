/*
 * Lights.cpp
 *
 *  Created on: May 7, 2023
 *      Author: JERZSTAN
 */

#include "lights.hpp"
#include <string>


Light::Light(GPIO_TypeDef * outputPeripheral, uint16_t output, GPIO_TypeDef * switchPeripheral, uint16_t mainSwitch, string roomName,
		GPIO_TypeDef * altSwitchPeripheral, uint16_t altSwitch, byte id)
{
	this->outputPeripheral = outputPeripheral;
	this->outputNumber = output;
	this->switchPeripheral = switchPeripheral;
	this->switchNumber = mainSwitch;
	this->room = roomName;
	this->altSwitchPeripheral = altSwitchPeripheral;
	this->altSwitchNumber = altSwitch;
	this->state = false;
	this->switchState = CheckSwitchState();
	this->altSwitchState = CheckAltSwitchState();
	this->id = id;
}

//Lights::Lights(const Lights & old)
//{
//	initializedLights = old.initializedLights;
//	for (int i = 0; i < initializedLights; i++)
//	{
//		lights[i] = Light(old.lights[i].outputPeripheral, old.lights[i].outputNumber, old.lights[i].switchPeripheral, old.lights[i].switchNumber,
//				old.lights[i].room, old.lights[i].altSwitchPeripheral, old.lights[i].altSwitchNumber, old.lights[i].id);
//	}
//}

void Light::SwitchLight(bool value)
{
	HAL_GPIO_WritePin(outputPeripheral, outputNumber, value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

bool Light::CheckSwitchState()
{
	return HAL_GPIO_ReadPin(switchPeripheral, switchNumber) == GPIO_PIN_SET;
}

bool Light::CheckAltSwitchState()
{
	if (altSwitchNumber != 0)
		return HAL_GPIO_ReadPin(altSwitchPeripheral, (uint16_t)altSwitchNumber) == GPIO_PIN_SET;
	else
		return false;
}

void Lights::AllLightsOff()
{
	for (int i = 0; i < initializedLights; i++)
	{
		if (lights[i].state == true)
		{
			lights[i].SwitchLight(false);
			lights[i].state = false;
		}
	}
}

bool Lights::CheckAndSwitchLights()
{
	for (int i = 0; i < initializedLights; i++)
	{
		bool switchState = lights[i].CheckSwitchState();
		if (lights[i].switchState != switchState)
		{
			lights[i].switchState = switchState;
			lights[i].state = !lights[i].state;
			lights[i].SwitchLight(lights[i].state);

			return true;
		}
		else if (lights[i].altSwitchNumber != 0)
		{
			bool altSwitchState = lights[i].CheckAltSwitchState();
			if (lights[i].altSwitchState != altSwitchState)
			{
				lights[i].altSwitchState = altSwitchState;
				lights[i].state = !lights[i].state;
				lights[i].SwitchLight(lights[i].state);

				return true;
			}
		}
	}
	return false;
}

void Lights::SwitchLight(std::string room, bool value)
{
	for (int i = 0; i < initializedLights; i++)
	{
		if (lights[i].room == room)
		{
			lights[i].state = value;
			lights[i].SwitchLight(lights[i].state);
			return;
		}
	}
}

void Lights::DoForEach(LightAction action)
{
	for (int i = 0; i < initializedLights; i++)
	{
		action(lights[i].outputNumber, lights[i].room, lights[i].switchNumber, lights[i].altSwitchNumber);
	}
}

std::string Lights::GetStatus()
{
	std::string status;
	for (int i = 0; i < initializedLights; i++)
	{
		//client->print(lights[i].outputNumber);
		//client->print('=');
		//client->println(lights[i].state);
		status += std::to_string((int)lights[i].outputNumber);
		status += "=";
		status += std::to_string(lights[i].state);
		status += "\n";
	}
	return status;
}

byte Lights::GetId(std::string name)
{
	for (int i = 0; i < initializedLights; i++)
	{
		if (lights[i].room == name)
			return lights[i].id;
	}
	return (byte)0;
}

std::string Lights::GetNameById(byte id)
{
	for (int i = 0; i < initializedLights; i++)
	{
		if (lights[i].id == id)
			return lights[i].room;
	}
	return "";
}


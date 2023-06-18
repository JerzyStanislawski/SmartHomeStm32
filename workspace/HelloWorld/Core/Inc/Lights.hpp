/*
 * Lights.hpp
 *
 *  Created on: Apr 27, 2023
 *      Author: JERZSTAN
 */

#ifndef INC_LIGHTS_HPP_
#define INC_LIGHTS_HPP_

#include <string>
#include <cstddef>
#include "lwip/api.h"

using namespace std;

typedef void (*LightAction) (uint16_t outputNumber, string room, uint16_t mainSwitch, uint16_t altSwitch);

class Light
{
public:
	GPIO_TypeDef * outputPeripheral;
	uint16_t outputNumber;
	GPIO_TypeDef * switchPeripheral;
	uint16_t switchNumber;
	GPIO_TypeDef * altSwitchPeripheral;
	uint16_t altSwitchNumber;
	string room;
	bool state;
	bool switchState;
	bool altSwitchState;
	byte id;

	Light(GPIO_TypeDef * outputPeripheral, uint16_t output, GPIO_TypeDef * switchPeripheral, uint16_t mainSwitch, string roomName,
			GPIO_TypeDef * altSwitchPeripheral, uint16_t altSwitch, byte id);
	Light() {}

	void SwitchLight(bool value);
	bool CheckSwitchState();
	bool CheckAltSwitchState();
};

class Lights
{
public:
	void AddLight(GPIO_TypeDef * outputPeripheral, uint16_t output, GPIO_TypeDef * switchPeripheral, uint16_t mainSwitch, string roomName,
			GPIO_TypeDef * altSwitchPeripheral, uint16_t altSwitch);
	bool CheckAndSwitchLights();
	void SwitchLight(string room, bool value);
	void AllLightsOff();
	void DoForEach(LightAction action);
	string GetStatus();
	string GetNameById(byte id);
	byte GetId(string name);

private:
	const static int initializedLights = 33;
	Light lights[initializedLights] =
	{
			Light(GPIOA, GPIO_PIN_0, GPIOB, GPIO_PIN_0, "barek", NULL, 0, (byte)0),
			Light(GPIOA, GPIO_PIN_4, GPIOB, GPIO_PIN_4, "garaz", NULL, 0, (byte)1),
			Light(GPIOA, GPIO_PIN_5, GPIOB, GPIO_PIN_5, "kotlownia", NULL, 0, (byte)2),
			Light(GPIOA, GPIO_PIN_6, GPIOB, GPIO_PIN_6, "wiatrolap", GPIOG, GPIO_PIN_9, (byte)3),
			Light(GPIOA, GPIO_PIN_8, GPIOB, GPIO_PIN_8, "hall", NULL, 0, (byte)4),
			Light(GPIOA, GPIO_PIN_9, GPIOB, GPIO_PIN_9, "lazienka2", NULL, 0, (byte)5),
			Light(GPIOA, GPIO_PIN_10, GPIOB, GPIO_PIN_10, "salon_led", NULL, 0, (byte)6),
			Light(GPIOA, GPIO_PIN_11, GPIOB, GPIO_PIN_11, "jadalnia", NULL, 0, (byte)7),
			Light(GPIOA, GPIO_PIN_12, GPIOB, GPIO_PIN_12, "kuchnia", NULL, 0, (byte)8),
			Light(GPIOA, GPIO_PIN_15, GPIOB, GPIO_PIN_15, "spizarnia", NULL, 0, (byte)9),
			Light(GPIOG, GPIO_PIN_10, GPIOG, GPIO_PIN_12, "gabinet", NULL, 0, (byte)10),
			Light(GPIOB, GPIO_PIN_1, GPIOB, GPIO_PIN_2, "lazienka", NULL, 0, (byte)11),
			Light(GPIOC, GPIO_PIN_0, GPIOD, GPIO_PIN_0, "wejscie", NULL, 0, (byte)12),
			Light(GPIOC, GPIO_PIN_2, GPIOD, GPIO_PIN_2, "wejscie_kolumna", NULL, 0, (byte)13),
			Light(GPIOC, GPIO_PIN_3, GPIOD, GPIO_PIN_3, "front", NULL, 0, (byte)14),
			Light(GPIOD, GPIO_PIN_4, GPIOD, GPIO_PIN_5, "salon_kominek", NULL, 0, (byte)15),
			Light(GPIOC, GPIO_PIN_6, GPIOD, GPIO_PIN_6, "lazienka_lustro", NULL, 0, (byte)16),
			Light(GPIOC, GPIO_PIN_7, GPIOD, GPIO_PIN_7, "salon", NULL, 0, (byte)17),
			Light(GPIOC, GPIO_PIN_9, GPIOD, GPIO_PIN_9, "kuchnia_szafki", NULL, 0, (byte)18),

			Light(GPIOC, GPIO_PIN_10, GPIOD, GPIO_PIN_10, "sypialnia", NULL, 0, (byte)19),
			Light(GPIOC, GPIO_PIN_11, GPIOD, GPIO_PIN_11, "pokoj1", NULL, 0, (byte)20),
			Light(GPIOC, GPIO_PIN_12, GPIOD, GPIO_PIN_12, "pokoj2", NULL, 0, (byte)21),
			Light(GPIOD, GPIO_PIN_8, GPIOD, GPIO_PIN_13, "lazienka_gora", NULL, 0, (byte)22),
			Light(GPIOC, GPIO_PIN_14, GPIOD, GPIO_PIN_14, "lazienka_kinkiety", NULL, 0, (byte)23),
			Light(GPIOC, GPIO_PIN_15, GPIOD, GPIO_PIN_15, "lazienka_led", NULL, 0, (byte)24),
			Light(GPIOE, GPIO_PIN_0, GPIOF, GPIO_PIN_0, "pralnia", NULL, 0, (byte)25),
			Light(GPIOE, GPIO_PIN_1, GPIOF, GPIO_PIN_1, "garderoba_gora", NULL, 0, (byte)26),
			Light(GPIOE, GPIO_PIN_2, GPIOF, GPIO_PIN_2, "korytarz", GPIOE, GPIO_PIN_3, (byte)27),
			Light(GPIOE, GPIO_PIN_4, GPIOF, GPIO_PIN_4, "korytarz_nocne", GPIOF, GPIO_PIN_3, (byte)28),
			Light(GPIOE, GPIO_PIN_5, GPIOF, GPIO_PIN_5, "schody", NULL, 0, (byte)29),
			Light(GPIOE, GPIO_PIN_6, GPIOF, GPIO_PIN_6, "taras", NULL, 0, (byte)30),
			Light(GPIOE, GPIO_PIN_7, GPIOF, GPIO_PIN_7, "taras_punktowe", NULL, 0, (byte)31),
			Light(GPIOE, GPIO_PIN_8, GPIOF, GPIO_PIN_8, "taras_kolumna", NULL, 0, (byte)32)
	};
};


#endif /* INC_LIGHTS_HPP_ */

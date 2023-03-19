/*
 * leds.c
 *
 *  Created on: Nov 8, 2022
 *      Author: drzacek
 */

// Includes
#include <string.h>
#include "leds.h"

// Defines
#define BUTTON1_Pin GPIO_PIN_8
#define BUTTON1_GPIO_Port GPIOB
#define BLU_LED1_Pin GPIO_PIN_5
#define BLU_LED1_GPIO_Port GPIOA
#define BLU_LED2_Pin GPIO_PIN_6
#define BLU_LED2_GPIO_Port GPIOA
#define BLU_LED3_Pin GPIO_PIN_7
#define BLU_LED3_GPIO_Port GPIOA
#define BLU_LED4_Pin GPIO_PIN_8
#define BLU_LED4_GPIO_Port GPIOA
#define BLU_LED5_Pin GPIO_PIN_11
#define BLU_LED5_GPIO_Port GPIOA
#define BUTTON2_Pin GPIO_PIN_6
#define BUTTON2_GPIO_Port GPIOB

// Variables
SPI_HandleTypeDef hSPI_LED;
uint8_t LED_SPI_INITALIZED = 0;

uint8_t resetBuffer[RESET_LENGTH] = {0};
uint8_t grbData[LED_BUFFER_SIZE];
uint8_t txBuf[RESET_LENGTH + LED_BUFFER_SIZE + RESET_LENGTH];


void ws2813_init(SPI_HandleTypeDef hspi)
{
	hSPI_LED = hspi;
	LED_SPI_INITALIZED = 1;
}

void ws2813_reset()
{
	if (LED_SPI_INITALIZED)
	{

	}
}


// The WS2813 addressable LEDs define 0 and 1 signals as PWM of different duty cycle
// From the datasheet:
//
// 0:    T0H
//  --------|
//			|    T0L
//			|------------
//
// 1:    T1H
//  ------------|
//				|    T1L
//				|--------
//
// Bit "0" needs to have 300-450ns high, followed by 300ns-100us low
// Bit "1" needs to have 750-1000ns high, followed by 300ns-100us low
// With frame reset 300us long
//
// At 8MHz SPI, one bit is 0.125us = 125ns long, so we can use one byte SPI data as PWM signal and vary the duty cycle with 8 bits
// Lets try 2-bit-high-6-bit-low for "0" and 5-bit-high-3-bit-low for 1 - it's not quite like what the table wants, but apparently
// the tolerances are pretty wide and it tolerates that.

uint8_t ws2813_bit(uint8_t bit)
{
	uint8_t byte;
	if (LED_SPI_INITALIZED)
	{
		if (bit)
		{
			byte = 0xf8;
		}
		else
		{
			byte = 0xc0;

		}
	}
	return byte;
}

void ws2813_clearAllLed()
{
	memset(grbData, 0xe0, 24 * LED_NUMBER);

	HAL_GPIO_WritePin(BLU_LED1_GPIO_Port, BLU_LED1_Pin, 0);
	HAL_GPIO_WritePin(BLU_LED2_GPIO_Port, BLU_LED2_Pin, 0);
	HAL_GPIO_WritePin(BLU_LED3_GPIO_Port, BLU_LED3_Pin, 0);
	HAL_GPIO_WritePin(BLU_LED4_GPIO_Port, BLU_LED4_Pin, 0);
	HAL_GPIO_WritePin(BLU_LED5_GPIO_Port, BLU_LED5_Pin, 0);
}

void ws2813_setLedRGB(uint8_t grb[3], uint32_t led_position)
{
	// Set buffer for GREEN/RED/BLUE color data for LED at [led_position] position - yes, LEDs start at 0, not at 1
	for (int i = 0; i < 3; i++)
	{
		grbData[0 + (led_position * 24) + (i*8)] = ws2813_bit(grb[i] & 0x80);
		grbData[1 + (led_position * 24) + (i*8)] = ws2813_bit(grb[i] & 0x40);
		grbData[2 + (led_position * 24) + (i*8)] = ws2813_bit(grb[i] & 0x20);
		grbData[3 + (led_position * 24) + (i*8)] = ws2813_bit(grb[i] & 0x10);
		grbData[4 + (led_position * 24) + (i*8)] = ws2813_bit(grb[i] & 0x08);
		grbData[5 + (led_position * 24) + (i*8)] = ws2813_bit(grb[i] & 0x04);
		grbData[6 + (led_position * 24) + (i*8)] = ws2813_bit(grb[i] & 0x02);
		grbData[7 + (led_position * 24) + (i*8)] = ws2813_bit(grb[i] & 0x01);
	}
}

void ws2813_sendLEDs()
{
	if (LED_SPI_INITALIZED)
	{
		memcpy(txBuf, resetBuffer, RESET_LENGTH);
		memcpy(txBuf+RESET_LENGTH, grbData, LED_BUFFER_SIZE);
		memcpy(txBuf+RESET_LENGTH+LED_BUFFER_SIZE, resetBuffer, RESET_LENGTH);

		HAL_SPI_Transmit(&hSPI_LED, txBuf, RESET_LENGTH + LED_BUFFER_SIZE + RESET_LENGTH, 200);
	}
}


void led_effect_0()
{
	static uint32_t prescaler = 0;
	static uint8_t counter = 0;

	uint8_t grbGreen[3]	 = {255, 0, 0};
	uint8_t grbRed[3]	 = {0, 255, 0};



	HAL_GPIO_WritePin(BLU_LED1_GPIO_Port, BLU_LED1_Pin, counter);
	HAL_GPIO_WritePin(BLU_LED2_GPIO_Port, BLU_LED2_Pin, counter);
	HAL_GPIO_WritePin(BLU_LED3_GPIO_Port, BLU_LED3_Pin, counter);
	HAL_GPIO_WritePin(BLU_LED4_GPIO_Port, BLU_LED4_Pin, counter);
	HAL_GPIO_WritePin(BLU_LED5_GPIO_Port, BLU_LED5_Pin, counter);

	if (counter)
	{
		ws2813_setLedRGB(grbGreen, 2);
		ws2813_setLedRGB(grbGreen, 4);
		ws2813_setLedRGB(grbGreen, 6);
		ws2813_setLedRGB(grbGreen, 8);
		ws2813_setLedRGB(grbGreen, 10);
	}
	else
	{
		ws2813_setLedRGB(grbRed, 0);

		ws2813_setLedRGB(grbRed, 1);
		ws2813_setLedRGB(grbRed, 3);
		ws2813_setLedRGB(grbRed, 5);
		ws2813_setLedRGB(grbRed, 7);
		ws2813_setLedRGB(grbRed, 9);
	}


	// Reduce speed for slower effects
	prescaler++;
	if (prescaler > 29)
	{
		prescaler = 0;
		counter++;
	}

	if (counter > 1)
		counter = 0;
}

void led_effect_1()
{
	static uint8_t counter = 0;
	HAL_GPIO_WritePin(BLU_LED1_GPIO_Port, BLU_LED1_Pin, counter);
	HAL_GPIO_WritePin(BLU_LED2_GPIO_Port, BLU_LED2_Pin, counter);
	HAL_GPIO_WritePin(BLU_LED3_GPIO_Port, BLU_LED3_Pin, counter);
	HAL_GPIO_WritePin(BLU_LED4_GPIO_Port, BLU_LED4_Pin, counter);
	HAL_GPIO_WritePin(BLU_LED5_GPIO_Port, BLU_LED5_Pin, counter);

	if (counter)
		counter = 0;
	else
		counter = 1;
}

void led_effect_2()
{
	static uint16_t counter = 0;
	static uint16_t counter2 = 127;
	static uint16_t counter3 = 255;

	static uint8_t grb0[3] = {0};
	static uint8_t grb1[3] = {0};
	static uint8_t grb2[3] = {0};

	grb0[0] = (counter < 256) ? counter : 510 - counter;
	grb1[0] = (counter2 < 256) ? counter2 : 510 - counter2;
	grb2[0] = (counter3 < 256) ? counter3 : 510 - counter3;

	grb0[1] = (counter < 256) ? counter : 510 - counter;
	grb1[1] = (counter2 < 256) ? counter2 : 510 - counter2;
	grb2[1] = (counter3 < 256) ? counter3 : 510 - counter3;


	ws2813_setLedRGB(grb0, 0);

	ws2813_setLedRGB(grb1, 1);
	ws2813_setLedRGB(grb1, 3);
	ws2813_setLedRGB(grb1, 5);
	ws2813_setLedRGB(grb1, 7);
	ws2813_setLedRGB(grb1, 9);

	ws2813_setLedRGB(grb2, 2);
	ws2813_setLedRGB(grb2, 4);
	ws2813_setLedRGB(grb2, 6);
	ws2813_setLedRGB(grb2, 8);
	ws2813_setLedRGB(grb2, 10);

	counter += 2;
	if (counter > 255*2)
		counter = 0;

	counter2 += 2;
	if (counter2 > 255*2)
		counter2 = 0;

	counter3 += 2;
	if (counter3 > 255*2)
		counter3 = 0;
}

void led_effect_3()
{
	static uint16_t counter = 0;
	static uint16_t counter2 = 127;
	static uint16_t counter3 = 255;

	static uint8_t grb0[3] = {0};

	grb0[0] = 50 * ((counter < 256) ? counter : 510 - counter)/256;
	grb0[1] = 50 * ((counter < 256) ? counter : 510 - counter)/256;
	grb0[2] = (counter < 256) ? counter : 510 - counter;

	ws2813_setLedRGB(grb0, 0);

	ws2813_setLedRGB(grb0, 1);
	ws2813_setLedRGB(grb0, 3);
	ws2813_setLedRGB(grb0, 5);
	ws2813_setLedRGB(grb0, 7);
	ws2813_setLedRGB(grb0, 9);

	ws2813_setLedRGB(grb0, 2);
	ws2813_setLedRGB(grb0, 4);
	ws2813_setLedRGB(grb0, 6);
	ws2813_setLedRGB(grb0, 8);
	ws2813_setLedRGB(grb0, 10);

	counter += 2;
	if (counter > 255*2)
		counter = 0;

}

void led_effect_4()
{
	static uint32_t counter = 0;

	static uint8_t grb0[3] = {0};

	grb0[0] = 255;
	grb0[1] = 255;

	switch(counter / 20)
	{
	default:
	case 2:
		ws2813_setLedRGB(grb0, 0);
		break;

	case 1:
		ws2813_setLedRGB(grb0, 1);
		ws2813_setLedRGB(grb0, 3);
		ws2813_setLedRGB(grb0, 5);
		ws2813_setLedRGB(grb0, 7);
		ws2813_setLedRGB(grb0, 9);
		break;

	case 0:
		ws2813_setLedRGB(grb0, 2);
		ws2813_setLedRGB(grb0, 4);
		ws2813_setLedRGB(grb0, 6);
		ws2813_setLedRGB(grb0, 8);
		ws2813_setLedRGB(grb0, 10);
		break;
	}

	counter += 1;
	if (counter > 59)
		counter = 0;
}

void led_effect_5()
{
	static uint16_t counter = 0;
		static uint16_t counter2 = 170;
		static uint16_t counter3 = 340;

		static uint8_t grb0[3] = {0};
		static uint8_t grb1[3] = {0};
		static uint8_t grb2[3] = {0};

		uint8_t faktor0 = 0;
		uint8_t faktor1 = 0;
		uint8_t faktor2 = 0;

		faktor0 = (counter < 256) ? counter : 510 - counter;
		faktor1 = (counter2 < 256) ? counter2 : 510 - counter2;
		faktor2 = (counter3 < 256) ? counter3 : 510 - counter3;

		grb0[0] = (faktor0 * 12)/255;
		grb0[1] = (faktor0 * 209)/255;
		grb0[2] = (faktor0 * 128)/255;

		grb1[0] = (faktor1 * 17)/255;
		grb1[1] = (faktor1 * 110)/255;
		grb1[2] = (faktor1 * 243)/255;

		grb2[0] = (faktor2 * 121)/255;
		grb2[1] = (faktor2 * 17)/255;
		grb2[2] = (faktor2 * 243)/255;

		ws2813_setLedRGB(grb0, 0);

		ws2813_setLedRGB(grb1, 1);
		ws2813_setLedRGB(grb1, 3);
		ws2813_setLedRGB(grb1, 5);
		ws2813_setLedRGB(grb1, 7);
		ws2813_setLedRGB(grb1, 9);

		ws2813_setLedRGB(grb2, 2);
		ws2813_setLedRGB(grb2, 4);
		ws2813_setLedRGB(grb2, 6);
		ws2813_setLedRGB(grb2, 8);
		ws2813_setLedRGB(grb2, 10);

		counter += 2;
		if (counter > 255*2)
			counter = 0;

		counter2 += 2;
		if (counter2 > 255*2)
			counter2 = 0;

		counter3 += 2;
		if (counter3 > 255*2)
			counter3 = 0;
}

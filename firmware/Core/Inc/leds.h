/*
 * leds.h
 *
 *  Created on: Nov 7, 2022
 *      Author: drzacek
 */

#ifndef INC_LEDS_H_
#define INC_LEDS_H_

// This file contains declarations of functions and variables
// used for driving LEDs on Pixel-Star PCB.
// Basic low-level driving of the WS2813 protocol, and the complex animations

#include "stm32g0xx.h"

#define RESET_LENGTH 250	// RESET will be 250 bytes long (SPI)
#define LED_NUMBER 11		// number of LEDS
#define LED_BUFFER_SIZE LED_NUMBER*24

void ws2813_init(SPI_HandleTypeDef hspi);	// init SPI handle and variables for ws2813 LEDs

void ws2813_reset();	// send RESET signal

uint8_t ws2813_bit(uint8_t bit);	// get the SPI value for "1" and "0"

void ws2813_setLedRGB(uint8_t grb[3], uint32_t led_position);	// Set color for LED X
void ws2813_sendLEDs();	// Send the LED buffer (complete, all LEDs)
void ws2813_clearAllLed();	// Set all LEDs to 0/0/0 (off)

void led_effect_0();
void led_effect_1();
void led_effect_2();
void led_effect_3();
void led_effect_4();
void led_effect_5();

#endif /* INC_LEDS_H_ */

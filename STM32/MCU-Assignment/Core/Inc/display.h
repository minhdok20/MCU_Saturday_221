/*
 * display.h
 *
 *  Created on: Nov 1, 2022
 *      Author: dell
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "main.h"
#include "global.h"
#include "stdio.h"
#include "stdlib.h"

// Display traffic light
void redl_greenp();
void redl_yellowp();
void redp_greenl();
void redp_yellowl();
void toggle_red();
void toggle_yellow();
void toggle_green();

extern int index_led;
extern int counterL, counterP;

void display(int counter, UART_HandleTypeDef huart2);
void update();

void updateClockBufferMode1();
void updateClockBufferRed();
void updateClockBufferYellow();
void updateClockBufferGreen();

#endif /* INC_DISPLAY_H_ */

/*
 * button.h
 *
 *  Created on: Oct 7, 2022
 *      Author: dell
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include "software_timer.h"

#define NORMAL_STATE SET
#define PRESSED_STATE RESET

#define NUM_OF_BUTTONS 4			// Number of Buttons to use

int longkeyPress;					// Thoi gian de su kien longkeyPress dien ra
int change_statelongkey;			// Set thoi gian dieu kien cho nhung lan change trang thai tiep theo neu van con nhan giu

int isButtonPressed(int index);

void getKeyInput();

#endif /* INC_BUTTON_H_ */

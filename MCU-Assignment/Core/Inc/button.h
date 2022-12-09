/*
 * button.h
 *
 *  Created on: Dec 9, 2022
 *      Author: HP PV
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include "software_timer.h"


#define NORMAL_STATE SET
#define PRESSED_STATE RESET

#define NUM_OF_BUTTONS 3						// Number of Buttons to use
#define TIMEOUTFORLONGKEYPRESS 3000/TIME_CYCLE	// So chu ki dem nguoc cho 3s (thoi gian dieu kien cho longkeypress)

int isButtonPressed(int index);

void getKeyInput();


#endif /* INC_BUTTON_H_ */

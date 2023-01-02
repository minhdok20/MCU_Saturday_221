 /*
 * software_timer.h
 *
 *  Created on: Sep 30, 2022
 *      Author: Admin
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define NUM_OF_TIMERS 	4  				// Number of Timers to use
// Timer 0: Set thoi gian chuyen doi cac trang thai cua MODE 1
// Timer 1: Gui qua UART (Mode1)
// Timer 2: Blinking LED MODE3
// Timer 3: Dem 2 chu ki cho Pedestrian

extern int TIME_CYCLE;					// Time cycle

extern int timer_flag[NUM_OF_TIMERS];
extern int timer_counter[NUM_OF_TIMERS];

void setTimer(int index, int duration);
void clearTimer(int index);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */

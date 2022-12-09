/*
 * software_timer.h
 *
 *  Created on: Dec 9, 2022
 *      Author: HP PV
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define TIME_CYCLE 		10 				// Time cycle: 10ms
#define NUM_OF_TIMERS 	2  				// Number of Timers to use

extern int timer_flag[NUM_OF_TIMERS];

void setTimer(int index, int duration);
void clearTimer(int index);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
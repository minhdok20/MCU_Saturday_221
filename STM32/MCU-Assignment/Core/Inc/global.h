/*
 * global.h
 *
 *  Created on: Sep 30, 2022
 *      Author: Admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
// Mode INIT
#define INIT				0

// Mode 1
#define MODE1				1
#define AUTO_REDL_GREENP	11
#define AUTO_REDL_YELLOWP	12
#define AUTO_REDP_GREENL	13
#define	AUTO_REDP_YELLOWL	14

// Mode 2
#define MODE2				2
#define MAN_REDL_GREENP		21  	// Init
#define MAN_REDL_YELLOWP	22
#define MAN_REDP_GREENL		23
#define	MAN_REDP_YELLOWL	24

// Mode 3
#define MODE3				3
#define SET_TIMER_RED		31		// Init
#define SET_TIMER_YELLOW	32
#define SET_TIMER_GREEN		33

// Mode Pedestrian
#define MODEPEDES			4
#define PEDES_OFF			41		// Init
#define PEDES_ON			42

extern int RED;
extern int YELLOW;
extern int GREEN;

extern int status;

// Display UART
extern char str[50];
extern uint8_t temp;

#endif /* INC_GLOBAL_H_ */

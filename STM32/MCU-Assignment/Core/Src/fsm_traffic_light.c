/*
 * mode2.c
 *
 *  Created on: Nov 1, 2022
 *      Author: dell
 */

#include "fsm_traffic_light.h"

int man_status = 1;

void fsm_traffic_light() {
	switch(status){

//----------------------------------------------------------------------------------------------
// MODE INIT
	case INIT:
		// Chuyen ve trang thai mode 1
		status = MODE1;
		break;
//----------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------
// MODE 1: AUTOMATIC MODE
	case MODE1:
		// Chuyen ve trang thai period AUTO_REDL_GREENP
		switch(man_status) {
		// Xac dinh trang thai manual set lan gan nhat de setup sang trang thai auto tuong ung
		// Setup ban dau va cap nhat gia tri
		case 1:	// AUTO_REDL_GREENP
			status = AUTO_REDL_GREENP;
			setTimer(0, GREEN * 1000);	// Timer
			counterL = 1;
			counterP = 1;
			break;
		case 2: // AUTO_REDL_YELLOWP
			status = AUTO_REDL_YELLOWP;
			setTimer(0, YELLOW * 1000);	// Timer
			counterL = GREEN + 1;
			counterP = GREEN + 1;
			break;
		case 3: // AUTO_REDP_GREENL
			status = AUTO_REDP_GREENL;
			setTimer(0, GREEN * 1000);	// Timer
			counterL = RED + 1;
			counterP = RED + 1;
			break;
		case 4: // AUTO_REDP_YELLOWL
			status = AUTO_REDP_YELLOWL;
			setTimer(0, YELLOW * 1000); // Timer
			counterL = RED + GREEN + 1;
			counterP = RED + GREEN + 1;
			break;
		default:
			break;
		}
		// Set Timer
		setTimer(1, 1000);			// Timer updateClockBufferMode1
		clearTimer(2);				// O mode 1 khong su dung Timer cho blinking LED
		// Hien thi ra UART
		updateClockBufferMode1();
		update();
		break;

	case AUTO_REDL_GREENP:
		// Setup cho den Landscape_RED va Portrait_GREEN sang
		redl_greenp();
		// Neu timer_flag[0] == 1, chuyen den trang thai AUTO_REDL_YELLOWP dong thoi setTimer cho truong hop ke tiep
		if (timer_flag[0] == 1) {
			status = AUTO_REDL_YELLOWP;
			setTimer(0, YELLOW * 1000);
		}
		// Neu timer_flag[1] == 1, update gia tri thoi gian dem nguoc va setTimer lai
		if (timer_flag[1] == 1) {
			updateClockBufferMode1();
			update();
			setTimer(1, 1000);
		}
		// Neu nhan nut MODE, he thong chuyen sang mode 2
		if (isButtonPressed(0) == 1) {
			status = MODE2;
		}
		break;

	case AUTO_REDL_YELLOWP:
		// Setup cho den Landscape_RED va Portrait_YELLOW sang
		redl_yellowp();
		// Neu timer_flag[0] == 1, chuyen den trang thai AUTO_REDP_GREENL dong thoi setTimer cho truong hop ke tiep
		if (timer_flag[0] == 1) {
			status = AUTO_REDP_GREENL;
			setTimer(0, GREEN * 1000);
		}
		// Neu timer_flag[1] == 1, update gia tri thoi gian dem nguoc va setTimer lai
		if (timer_flag[1] == 1) {
			updateClockBufferMode1();
			update();
			setTimer(1, 1000);
		}
		// Neu nhan nut MODE, he thong chuyen sang mode 2
		if (isButtonPressed(0) == 1) {
			status = MODE2;
		}
		break;

	case AUTO_REDP_GREENL:
		// Setup cho den Portrait_RED va Landscape_GREEN sang
		redp_greenl();
		// Neu timer_flag[0] == 1, chuyen den trang thai AUTO_REDP_YELLOWL dong thoi setTimer cho truong hop ke tiep
		if (timer_flag[0] == 1) {
			status = AUTO_REDP_YELLOWL;
			setTimer(0, YELLOW * 1000);
		}
		// Neu timer_flag[1] == 1, update gia tri thoi gian dem nguoc va setTimer lai
		if (timer_flag[1] == 1) {
			updateClockBufferMode1();
			update();
			setTimer(1, 1000);
		}
		// Neu nhan nut MODE, he thong chuyen sang mode 2
		if (isButtonPressed(0) == 1) {
			status = MODE2;
		}
		break;

	case AUTO_REDP_YELLOWL:
		// Setup cho den Portrait_RED va Landscape_YELLOW sang
		redp_yellowl();
		// Neu timer_flag[0] == 1, chuyen den trang thai AUTO_REDL_GREENP dong thoi setTimer cho truong hop ke tiep
		if (timer_flag[0] == 1) {
			status = AUTO_REDL_GREENP;
			setTimer(0, GREEN * 1000);
		}
		// Neu timer_flag[1] == 1, update gia tri thoi gian dem nguoc va setTimer lai
		if (timer_flag[1] == 1) {
			updateClockBufferMode1();
			update();
			setTimer(1, 1000);
		}
		// Neu nhan nut MODE, he thong chuyen sang mode 2
		if (isButtonPressed(0) == 1) {
			status = MODE2;
		}
		break;
//----------------------------------------------------------------------------------------------





//----------------------------------------------------------------------------------------------
// MODE 2: MANUAL MODE
	case MODE2:
		// State ban dau o mode 2 se mac dinh la MAN_REDL_GREENP
		status = MAN_REDL_GREENP;
		// Clear cac timer khong duoc su dung o mode 2
		for (int i = 0; i < NUM_OF_TIMERS; i++)
			clearTimer(i);
		break;
	case MAN_REDL_GREENP:
		// Setup cho den Landscape_RED va Portrait_GREEN sang
		redl_greenp();
		// Neu nhan nut MODE, chuyen sang MODE3
		if (isButtonPressed(0) == 1) {
			status = MODE3;
		}
		// Neu nhan nut INC, chuyen sang trang thai MAN_REDL_YELLOWP
		if (isButtonPressed(1) == 1) {
			status = MAN_REDL_YELLOWP;
		}
		// Neu nhan nut SET, chuyen sang trang thai MODE1, cap nhat man_status de setup cho tu MODE1
		// se sang trang thai auto tuong ung voi trang thai manual vua set xong
		if (isButtonPressed(2) == 1) {
			man_status = 1;
			status = MODE1;
		}
		break;
	case MAN_REDL_YELLOWP:
		// Setup Landscape_RED va Portrait_YELLOW sang
		redl_yellowp();
		// Neu nhan nut MODE, chuyen sang MODE3
		if (isButtonPressed(0) == 1) {
			status = MODE3;
		}
		// Neu nhan nut INC, chuyen sang trang thai MAN_REDP_GREENL
		if (isButtonPressed(1) == 1) {
			status = MAN_REDP_GREENL;
		}
		// Neu nhan nut SET, cap nhat man_status va chuyen sang trang thai MODE1
		if (isButtonPressed(2) == 1) {
			man_status = 2;
			status = MODE1;
		}
		break;
	case MAN_REDP_GREENL:
		// Setup Landscape_GREEN va Portrait_RED sang
		redp_greenl();
		// Neu nhan nut MODE, chuyen sang MODE3
		if (isButtonPressed(0) == 1) {
			status = MODE3;
		}
		// Neu nhan nut INC, chuyen sang trang thai MAN_REDP_GREENL
		if (isButtonPressed(1) == 1) {
			status = MAN_REDP_YELLOWL;
		}
		// Neu nhan nut SET, cap nhat man_status va chuyen sang trang thai MODE1
		if (isButtonPressed(2) == 1) {
			man_status = 3;
			status = MODE1;
		}
		break;
	case MAN_REDP_YELLOWL:
		// Setup Landscape_YELLOW va Portrait_RED sang
		redp_yellowl();
		// Neu nhan nut MODE, chuyen sang MODE3
		if (isButtonPressed(0) == 1) {
			status = MODE3;
		}
		// Neu nhan nut INC, chuyen sang trang thai MAN_REDP_GREENL
		if (isButtonPressed(1) == 1) {
			status = MAN_REDL_GREENP;
		}
		// Neu nhan nut SET, cap nhat man_status va chuyen sang trang thai MODE1
		if (isButtonPressed(2) == 1) {
			man_status = 4;
			status = MODE1;
		}
		break;
//----------------------------------------------------------------------------------------------





//----------------------------------------------------------------------------------------------
// MODE 3: TUNING MODE
	case MODE3:
		// State ban dau o mode 2 se mac dinh la SET_TIMER_RED
		// Setup cho tat ca cac den RED sang
		toggle_red();
		// SetTimer
		clearTimer(0);
		clearTimer(1);
		setTimer(2, 500);	// Timer blinking
		// Update lai gia tri hien thi
		updateClockBufferRed();
		update();
		// Chuyen ve trang thai SET_TIMER_RED
		status = SET_TIMER_RED;
		break;

	case SET_TIMER_RED:
		// Neu timer_flag[3] == 1, toggle tat ca cac den RED va setTimer lai
		if (timer_flag[2] == 1) {
			setTimer(2, 500);
			toggle_red();
		}
		// Neu nhan nut MODE, he thong chuyen sang trang thai mode 1
		if (isButtonPressed(0) == 1) {
			status = MODE1;
			// Cap nhat lai bo ba gia tri thoi gian RED, YELLOW va GREEN
			GREEN = RED - YELLOW;
		}
		// Neu nhan nut INC, thay doi gia tri thoi gian RED, cap nhat lai bo ba gia tri thoi gian RED, YELLOW va GREEN
		if (isButtonPressed(1) == 1) {
			if (RED >= 99) RED = YELLOW + 1;
			else RED++;
			updateClockBufferRed();
			update();
		}
		// Neu nhan nut SET, chuyen sang trang thai SET_TIMER_YELLOW
		if (isButtonPressed(2) == 1) {
			// Cap nhat lai bo ba gia tri thoi gian RED, YELLOW va GREEN
			GREEN = RED - YELLOW;
			status = SET_TIMER_YELLOW;
			setTimer(2, 500);
			toggle_yellow();
			updateClockBufferYellow();
			update();
		}
		break;

	case SET_TIMER_YELLOW:
		// Neu timer_flag[3] == 1, toggle tat ca cac den YELLOW va setTimer lai
		if (timer_flag[2] == 1) {
			setTimer(2, 500);
			toggle_yellow();
		}
		// Neu nhan nut MODE, he thong chuyen sang trang thai mode 1
		if (isButtonPressed(0) == 1) {
			status = MODE1;
			// Cap nhat lai bo ba gia tri thoi gian RED, YELLOW va GREEN
			if (RED <= YELLOW) RED = YELLOW + 1;
			GREEN = RED - YELLOW;
		}
		// Neu nhan nut INC, thay doi gia tri thoi gian YELLOW, cap nhat lai bo ba gia tri thoi gian RED, YELLOW va GREEN
		if (isButtonPressed(1) == 1) {
			if (YELLOW >= 5) YELLOW = 1;
			else YELLOW++;
			updateClockBufferYellow();
			update();
		}
		// Neu nhan nut SET, chuyen sang trang thai SET_TIMER_GREEN
		if (isButtonPressed(2) == 1) {
			// Cap nhat lai bo ba gia tri thoi gian RED, YELLOW va GREEN
			if (RED <= YELLOW) RED = YELLOW + 1;
			GREEN = RED - YELLOW;
			status = SET_TIMER_GREEN;
			setTimer(2, 500);
			toggle_green();
			updateClockBufferGreen();
			update();
		}
		break;

	case SET_TIMER_GREEN:
		// Neu timer_flag[2] == 1, toggle tat ca cac den GREEN va setTimer lai
		if (timer_flag[3] == 1) {
			setTimer(2, 500);
			toggle_green();
		}
		// Neu nhan nut MODE, he thong chuyen sang trang thai mode 1
		if (isButtonPressed(0) == 1) {
			status = MODE1;
			// Cap nhat lai bo ba gia tri thoi gian RED, YELLOW va GREEN
			RED = GREEN + YELLOW;
		}
		// Neu nhan nut INC, thay doi gia tri thoi gian YELLOW, cap nhat lai bo ba gia tri thoi gian RED, YELLOW va GREEN
		if (isButtonPressed(1) == 1) {
			if (GREEN >= RED - YELLOW) GREEN = 1;
			else GREEN++;
			updateClockBufferGreen();
			update();
		}
		// Neu nhan nut SET, chuyen sang trang thai SET_TIMER_GREEN
		if (isButtonPressed(2) == 1) {
			// Cap nhat lai bo ba gia tri thoi gian RED, YELLOW va GREEN
			RED = GREEN + YELLOW;
			status = SET_TIMER_RED;
			setTimer(2, 500);
			toggle_red();
			updateClockBufferRed();
			update();
		}
		break;
//--------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------
// DEFAULT
	default:
		break;
	}
}

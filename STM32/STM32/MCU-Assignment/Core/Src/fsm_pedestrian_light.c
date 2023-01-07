/*
 * fsm_pedestrian_light.c
 *
 *  Created on: Dec 16, 2022
 *      Author: Admin
 */

#include "fsm_pedestrian_light.h"


void fsm_pedestrian_light(TIM_HandleTypeDef htim3){
	switch (status_pedes){
	case MODEPEDES:
		status_pedes = PEDES_OFF;
		timer_flag[5] = 1;
		timer_flag[4] = 1;
		break;
	case PEDES_OFF:
		__HAL_TIM_SetCompare (&htim3, TIM_CHANNEL_1, 0);
		HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 0);
		HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, 0);
		if (isButtonPressed(3) == 1){
			status_pedes = PEDES_ON;
			setTimer(4, (RED + YELLOW + GREEN) * 2000);
			clearTimer(6);
			clearTimer(7);
			timer_flag[5] = 1;
		}
		break;
	case PEDES_ON:
		if (timer_flag[4] == 0) {
			switch (status){
			case AUTO_REDL_GREENP:
				HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 0);
				HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, 1);

				if (sec_RED <= 10 && sec_RED > 0){
					if (timer_counter[6] == 0 && timer_counter[7] == 0 && !timer_flag[6] && !timer_flag[7]){
						setTimer(6, sec_RED*100);
					}
					if (timer_flag[6]){
						timer_flag[6] = 0;
						__HAL_TIM_SetCompare (&htim3, TIM_CHANNEL_1, (10 - sec_RED)*9);
						setTimer(7, sec_RED*100);
					}
					if (timer_flag[7]){
						timer_flag[7] = 0;
						__HAL_TIM_SetCompare (&htim3, TIM_CHANNEL_1, 0);
					}
				  }
				else {
					if (sec_RED == 0){__HAL_TIM_SetCompare (&htim3, TIM_CHANNEL_1, (10 - sec_RED)*9);}
					else {
					__HAL_TIM_SetCompare (&htim3, TIM_CHANNEL_1, 0);
					}
				}
				break;
			case AUTO_REDL_YELLOWP:
				HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 0);
				if (timer_flag[5] == 1){
					HAL_GPIO_TogglePin(D7_GPIO_Port, D7_Pin);
					setTimer(5, 500);
				}
				if (sec_RED > 0){
					if (timer_counter[6] == 0 && timer_counter[7] == 0 && !timer_flag[6] && !timer_flag[7]){
						setTimer(6, sec_RED*100);
					}
					if (timer_flag[6]){
						timer_flag[6] = 0;
						__HAL_TIM_SetCompare (&htim3, TIM_CHANNEL_1, (10-sec_RED)*9);
						setTimer(7, sec_RED*100);
					}
					if (timer_flag[7]){
						timer_flag[7] = 0;
						__HAL_TIM_SetCompare (&htim3, TIM_CHANNEL_1, 0);
					}
				  }
				else {
					if (sec_RED == 0){__HAL_TIM_SetCompare (&htim3, TIM_CHANNEL_1, (10 - sec_RED)*9);}
					else {
					__HAL_TIM_SetCompare (&htim3, TIM_CHANNEL_1, 0);
					}
				}
				break;
			case AUTO_REDP_GREENL:
				HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 1);
				HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, 0);
				__HAL_TIM_SetCompare (&htim3, TIM_CHANNEL_1, 0);
				clearTimer(6);
				clearTimer(7);
				break;
			case AUTO_REDP_YELLOWL:
				HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 1);
				HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, 0);
				__HAL_TIM_SetCompare (&htim3, TIM_CHANNEL_1, 0);
				clearTimer(6);
				clearTimer(7);
				break;
			default:
				status_pedes = PEDES_OFF;
				timer_flag[4] = 1;
				HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 0);
				HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, 0);
				__HAL_TIM_SetCompare (&htim3, TIM_CHANNEL_1, 0);
				clearTimer(6);
				clearTimer(7);
				break;
			}
		} else {
			status_pedes = PEDES_OFF;
//			timer_flag[4] = 1;
			HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 0);
			HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, 0);
			__HAL_TIM_SetCompare (&htim3, TIM_CHANNEL_1, 0);
			clearTimer(6);
			clearTimer(7);
		}
		break;
	default:
		status_pedes = MODEPEDES;
		break;
	}
}

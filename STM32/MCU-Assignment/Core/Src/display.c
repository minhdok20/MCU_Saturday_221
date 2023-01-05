/*
 * display.c
 *
 *  Created on: Nov 1, 2022
 *      Author: dell
 */

#include "display.h"

UART_HandleTypeDef huart2;

// Display traffic light
void redl_greenp() {
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, SET);
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, RESET);
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, RESET);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, SET);
}

void redl_yellowp() {
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, SET);
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, RESET);
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, SET);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, SET);
}

void redp_greenl() {
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, RESET);
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, SET);
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, SET);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, RESET);
}

void redp_yellowl() {
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, SET);
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, SET);
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, SET);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, RESET);
}

void toggle_red() {
	HAL_GPIO_TogglePin(D2_GPIO_Port, D2_Pin);
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, RESET);
	HAL_GPIO_TogglePin(D4_GPIO_Port, D4_Pin);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, RESET);
}

int toggle = 0;
void toggle_yellow() {
	if (toggle == 0) {
		HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, SET);
		HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, SET);
		HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, SET);
		HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, SET);
		toggle = 1;
	}
	else {
		HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, RESET);
		HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, RESET);
		HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, RESET);
		HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, RESET);
		toggle = 0;
	}
}

void toggle_green() {
	HAL_GPIO_TogglePin(D3_GPIO_Port, D3_Pin);
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, RESET);
	HAL_GPIO_TogglePin(D5_GPIO_Port, D5_Pin);
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, RESET);
}


void display(int counter, UART_HandleTypeDef huart2) {
	int t = counter / 10;
	int u = counter % 10;
	HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!7SEG=%u%u#\r\n", t, u), 1000);
}

int indexL, indexP;
void update() {
	if (indexL != -1)
		display(indexL, huart2);
	if (indexP != -1)
		display(indexP, huart2);
}


int counterL, counterP;
void updateClockBufferMode1() {
	// Cap nhat gia tri thoi gian vao trong clockBuffer
	// Doi voi Landscape
	/* Den RED-Landscape sang (dem nguoc tu RED-1 -> 0) */
	if (counterL <= RED) {
		indexL = RED - counterL;
		sec_RED = indexL;
	}
	/* Den GREEN-Landscape sang (dem nguoc tu GREEN-1 -> 0) */
	else if (counterL <= (RED + GREEN)) {
		indexL = RED + GREEN - counterL;
	}
	/* Den YELLOW-Landscape sang (dem nguoc tu YELLOW-1 -> 0) */
	else if (counterL <= (RED + GREEN + YELLOW)){
		indexL = RED + GREEN + YELLOW - counterL;
	}
	counterL++;
	/* Neu thoi gian YELLOW-Landscape ket thuc, quay tro lai setup thoi gian cho RED-Landscape sang lai */
	if (counterL > RED + YELLOW + GREEN) {
		counterL = 1;
		indexL = RED - counterL;
		sec_RED = indexL;
	}



	// Doi voi 2 LED 7-SEG Portrait
	/* Den GREEN-Portrait sang (dem nguoc tu GREEN-1 -> 0) */
	if (counterP <= GREEN) {
		indexP = GREEN - counterP;
	}
	/* Den YELLOW-Portrait sang (dem nguoc tu YELLOW-1 -> 0) */
	else if (counterP <= (YELLOW + GREEN)) {
		indexP = YELLOW + GREEN - counterP;
	}
	/* Den RED-Portrait sang (dem nguoc tu RED-1 -> 0) */
	else if (counterP <= (RED + GREEN + YELLOW)) {
		indexP = RED + GREEN + YELLOW - counterP;
	}
	counterP++;
	/* Neu thoi gian RED-Portrait ket thuc, quay tro lai setup thoi gian cho GREEN-Portrait sang lai */
	if (counterP > RED + YELLOW + GREEN) counterP = 1;
}

void updateClockBufferRed() {
	// Hien thi value RED
	indexL = RED;
	indexP = -1;
}

void updateClockBufferYellow() {
	// Hien thi value YELLOW
	indexL = YELLOW;
	indexP = -1;
}

void updateClockBufferGreen() {
	// Hien thi value GREEN
	indexL = GREEN;
	indexP = -1;
}


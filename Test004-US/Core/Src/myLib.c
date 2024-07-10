/*
 * myLib.c
 *
 *  Created on: Jul 4, 2024
 *      Author: user
 */

#include "main.h"
extern UART_HandleTypeDef huart2;

int __io_putchar(int ch) // 1ch output to terminal
{
	HAL_UART_Transmit(&huart2, &ch, 1, 10);
	return ch;
}
int __io_getchar(void)
{
	char ch;
	while(HAL_UART_Receive(&huart2, &ch, 1, 10) != HAL_OK);	// Input wait

	HAL_UART_Transmit(&huart2, &ch, 1, 10);	// echo
	if(ch == '\r') HAL_UART_Transmit(&huart2, "\n", 1, 10);	// CR => LF
	return ch;
}
void Wait()
{
	while( HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) != 0);
}
void ProgramStart(char *name)	// B1 for start
{
	  printf("\033[2J\n");		// 2J : clear screen
	  printf("\033[1;1H\n");	// y;xH : (x,y) move cursor

	  printf("Program(%s) Ready. Press Blue Button to start\r\n", name);
	  Wait();
}

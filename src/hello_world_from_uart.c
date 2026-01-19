#include<hello_world_from_uart.h>

#include "stm32f4xx_hal.h"

void print_hello_world_from_uart(UART_HandleTypeDef* huart)
{
	const char msg[] = "Hello, world!\r\n";

	HAL_UART_Transmit(
		&huart,                  /* UART handle */
		(uint8_t *)msg,          /* data buffer */
		sizeof(msg) - 1,         /* length (exclude '\0') */
		HAL_MAX_DELAY            /* blocking timeout */
	);
}
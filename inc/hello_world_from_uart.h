#ifndef HELLO_WORLD_FROM_UART_H
#define HELLO_WORLD_FROM_UART_H

#include"stm32f4xx_hal_dma.h"
#include"stm32f4xx_hal_uart.h"

void print_hello_world_from_uart(UART_HandleTypeDef* huart);

#endif
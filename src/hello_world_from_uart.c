#include<hello_world_from_uart.h>

#include<capp/capp.h>

#include<string.h>

void print_hello_world_from_uart(UART_HandleTypeDef* huart)
{
	static int i = 0;
	static char msg[] = "Hello, world!";

	temp t;
	init_temp(&t, i, msg);
	char buffer[100];
	sprintf(buffer, "%s, %d\r\n", t.str, t.s);
	i++;

	HAL_UART_Transmit(
		huart,                  /* UART handle */
		(uint8_t *)buffer,      /* data buffer */
		strlen(buffer),         /* length (exclude '\0') */
		HAL_MAX_DELAY           /* blocking timeout */
	);
}

#include<hello_world_from_uart.h>

void main(void)
{
	// setup clock to run at highest frequency

	// setup LED pin as output

	// setup UART at baud of 115200

	while(1)
	{
		// diminishing delay by a fraction of 0.93, and reset delay if the delay is lesser than 10 ms

		// toggle LED

		// print hello world on UART, blockingly
		print_hello_world_from_uart();
	}
}
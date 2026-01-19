#include "stm32f4xx.h"               // device header
#include "stm32f4xx_hal.h"           // main HAL header
#include "stm32f4xx_hal_gpio.h"      // GPIO types and functions
#include "stm32f4xx_hal_rcc.h"       // RCC types/functions
#include "stm32f4xx_hal_uart.h"      // UART types/functions

#include<hello_world_from_uart.h>

static void SystemClock_Config(void);
static void GPIO_Init(void);
static void UART2_Init(UART_HandleTypeDef* huart2);

int main(void)
{
	HAL_Init();

	// setup clock to run at highest frequency
	SystemClock_Config();

	// setup LED pin as output
	GPIO_Init();

	// setup UART at baud of 115200
	UART_HandleTypeDef huart2;
	UART2_Init(&huart2);

	uint32_t delay_ms = 1000;
	while(1)
	{
		// diminishing delay by a fraction of 0.93, and reset delay if the delay is lesser than 10 ms
		delay_ms = (uint32_t)(delay_ms * 0.93f);
		if (delay_ms < 10)
			delay_ms = 1000;

		// toggle LED
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);

		// print hello world on UART, blockingly
		print_hello_world_from_uart(&huart2);
	}
}

/* ---------------- clock ---------------- */

static void SystemClock_Config(void)
{
	RCC_OscInitTypeDef osc = {0};
	RCC_ClkInitTypeDef clk = {0};

	osc.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc.HSEState       = RCC_HSE_ON;
	osc.PLL.PLLState   = RCC_PLL_ON;
	osc.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
	osc.PLL.PLLM       = 8;
	osc.PLL.PLLN       = 336;
	osc.PLL.PLLP       = RCC_PLLP_DIV2;
	osc.PLL.PLLQ       = 7;

	HAL_RCC_OscConfig(&osc);

	clk.ClockType      = RCC_CLOCKTYPE_SYSCLK |
	                     RCC_CLOCKTYPE_HCLK   |
	                     RCC_CLOCKTYPE_PCLK1  |
	                     RCC_CLOCKTYPE_PCLK2;
	clk.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
	clk.AHBCLKDivider  = RCC_SYSCLK_DIV1;
	clk.APB1CLKDivider = RCC_HCLK_DIV4;
	clk.APB2CLKDivider = RCC_HCLK_DIV2;

	HAL_RCC_ClockConfig(&clk, FLASH_ACR_LATENCY_5WS);
}

/* ---------------- GPIO ---------------- */

static void GPIO_Init(void)
{
	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitTypeDef gpio = {0};
	gpio.Pin   = GPIO_PIN_13;
	gpio.Mode  = GPIO_MODE_OUTPUT_PP;
	gpio.Pull  = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(GPIOC, &gpio);
}

/* ---------------- UART ---------------- */

static void UART2_Init(UART_HandleTypeDef* huart2)
{
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef gpio = {0};
	gpio.Pin       = GPIO_PIN_2 | GPIO_PIN_3;
	gpio.Mode      = GPIO_MODE_AF_PP;
	gpio.Pull      = GPIO_NOPULL;
	gpio.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
	gpio.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &gpio);

	huart2->Instance          = USART2;
	huart2->Init.BaudRate     = 115200;
	huart2->Init.WordLength   = UART_WORDLENGTH_8B;
	huart2->Init.StopBits     = UART_STOPBITS_1;
	huart2->Init.Parity       = UART_PARITY_NONE;
	huart2->Init.Mode         = UART_MODE_TX_RX;
	huart2->Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	huart2->Init.OverSampling = UART_OVERSAMPLING_16;

	HAL_UART_Init(huart2);
}
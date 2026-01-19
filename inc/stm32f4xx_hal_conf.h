#ifndef STM32F4xx_HAL_CONF_H
#define STM32F4xx_HAL_CONF_H

/* Core HAL module */
#define HAL_MODULE_ENABLED

/* Enabled HAL modules */
#define HAL_RCC_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
#define HAL_UART_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED

/* Oscillator values */
#define HSE_VALUE    8000000U
#define HSI_VALUE    16000000U
#define LSI_VALUE    32000U
#define LSE_VALUE    32768U

/* SysTick interrupt priority */
#define TICK_INT_PRIORITY  0x0FU

/* Include HAL core definitions */
#include "stm32f4xx_hal_def.h"

/* Include enabled peripheral headers */
#include"stm32f4xx_hal_rcc.h"
#include"stm32f4xx_hal_gpio.h"
#include"stm32f4xx_hal_dma.h"
#include"stm32f4xx_hal_uart.h"
#include"stm32f4xx_hal_cortex.h"
#include"stm32f4xx_hal_flash.h"
#include"stm32f4xx_hal_pwr.h"

#ifdef USE_FULL_ASSERT
  #define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
#else
  #define assert_param(expr) ((void)0U)
#endif

#endif /* STM32F4xx_HAL_CONF_H */

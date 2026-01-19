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
#define HAL_TIM_MODULE_ENABLED

/* External oscillator values */
#define HSE_VALUE            ((uint32_t)8000000)   /* 8 MHz */
#define HSE_STARTUP_TIMEOUT  ((uint32_t)100)       /* 100 ms */
#define LSE_VALUE            ((uint32_t)32768)     /* 32.768 kHz RTC */
#define LSE_STARTUP_TIMEOUT  ((uint32_t)5000)      /* 5 s */
#define EXTERNAL_CLOCK_VALUE ((uint32_t)8000000)   /* If using external clock directly */
#define HSI_VALUE            ((uint32_t)16000000)  /* 16 MHz */
#define HSI_STARTUP_TIMEOUT  ((uint32_t)100) /* 100 ms timeout for stabilization */

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
#include"stm32f4xx_hal_tim.h"

#ifdef USE_FULL_ASSERT
  #define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
#else
  #define assert_param(expr) ((void)0U)
#endif

#endif /* STM32F4xx_HAL_CONF_H */

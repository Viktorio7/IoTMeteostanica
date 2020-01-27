/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

#include "ili9163.h"
#include <stdio.h>

#include "lps25hb.h"
#include "hts221.h"



float temperature=0;
float pressure=0;
float humidity=0;
float acc[3];



void SystemClock_Config(void);
void display_init_clear(void);
void get_values();
void write_values();
void transmit_values(uint8_t startTx, uint8_t endTx);



int main(void)
{
  uint8_t startTx = 0xFE;
  uint8_t endTx = 0xFF;


  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  SystemClock_Config();

  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();

  display_init_clear();

  while (1)
  {
	  get_values();
	  LL_mDelay(2500);
	  transmit_values(startTx, endTx);
	  LL_mDelay(10);
	  write_values();
    }
}



void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

  if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0)
  {
  Error_Handler();  
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {
    
  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  
  }
  LL_Init1msTick(8000000);
  LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
  LL_SetSystemCoreClock(8000000);
  LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK1);
  LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_HSI);
}



void display_init_clear(void)
{
	LL_SPI_Enable(SPI1);

	lcdInitialise(LCD_ORIENTATION3);
	lcdClearDisplay(decodeRgbValue(0, 0, 0));

	LL_SPI_Disable(SPI1);
}


void get_values()
{
	LL_I2C_Enable(I2C1);

	//tlak
	lps25hb_init();
	lps25hb_get_press(&pressure);

	//teplota + vlhkost
	hts221_init();
	hts221_get_temp(&temperature);
	hts221_get_hum(&humidity);

	LL_I2C_Disable(I2C1);
}



void write_values()
{
	char stringToWrite[100];

	LL_SPI_Enable(SPI1);

	sprintf(stringToWrite, "Dobry den!");
	lcdPutS(stringToWrite, lcdTextX(2), lcdTextY(2), decodeRgbValue(255, 255, 255), decodeRgbValue(0, 0, 0));
	sprintf(stringToWrite,"Teplota  %.1f C", temperature);
	lcdPutS(stringToWrite, lcdTextX(2), lcdTextY(6), decodeRgbValue(255, 255, 255), decodeRgbValue(0, 0, 0));
	sprintf(stringToWrite,"Vlhkost  %.1f %%", humidity);
	lcdPutS(stringToWrite, lcdTextX(2), lcdTextY(10), decodeRgbValue(255, 255, 255), decodeRgbValue(0, 0, 0));
	sprintf(stringToWrite,"Tlak     %.1f hPA", pressure);
	lcdPutS(stringToWrite, lcdTextX(2), lcdTextY(14), decodeRgbValue(255, 255, 255), decodeRgbValue(0, 0, 0));

	LL_SPI_Disable(SPI1);
}



void transmit_values(uint8_t startTx, uint8_t endTx)
{
	uint8_t tempT=(uint8_t)temperature;
	uint8_t tempH=(uint8_t)humidity;
	double temp=pressure-1000;
	uint8_t tempP=(uint8_t)temp;

	LL_USART_TransmitData8(USART1, startTx);
	LL_mDelay(10);
	LL_USART_TransmitData8(USART1, tempT);
	LL_mDelay(10);
	LL_USART_TransmitData8(USART1, tempH);
	LL_mDelay(10);
	LL_USART_TransmitData8(USART1, tempP);
	LL_mDelay(10);
	LL_USART_TransmitData8(USART1, endTx);
}



/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

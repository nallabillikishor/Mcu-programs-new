/* USER CODE BEGIN Header */
/**
  **************************
  * @file           : main.c
  * @brief          : Main program body
  **************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
#define DS1307_ADDR_SEC 0x00
#define DS1307_ADDR_MINIUTE 0x01
#define DS1307_ADDR_HRS 0x02
#define DS1307_ADDR_DAY 0x03
#define DS1307_ADDR_DATE 0x04
#define DS1307_ADDR_MONTH 0x05
#define DS1307_ADDR_YEAR 0x06
#define SLAVE_ADDR 0xD0
#define DS1307_SLAVE_ADDR 0b1101000
#define DS1307_CH_DATA 0x00
#define AM_Time 0
#define PM_Time 1
#define TwentyFourHoursMode 2

#define Sunday 1
#define Monday 2
#define Tuesday 3
#define Wednesday 4
#define Thursday 5
#define Friday 6
#define Saturday 7

void delay(uint32_t x);
 uint8_t bcd_to_binary(uint8_t value);
 void RTC_BCD_data(char *bin);
 void I2C1_init(void);
 void I2C1_burstWrite(char saddr, char maddr, int n, char* data);
 void I2C1_burstRead(char saddr, char maddr, int n, char* data);
 void deci_2_bcd_conver(char *ptr);
 void split_num_conditinal(int digit);
 void digit_split(unsigned int p);
 int decimalToBCD(int decimal);
 int BCDtoDecimal(int BCD);

 void LCD_command(unsigned char command);
 void LCD_data(char data);
 void LCD_pin_init(void);
 void LCD_disp_init();
 void lcd_send_string (char *str);

 void Get_Time();

 typedef struct {
 uint8_t seconds;
 uint8_t minutes;
 uint8_t hour;
 uint8_t dayofweek;
 uint8_t dayofmonth;
 uint8_t month;
 uint8_t year;
 } TIME;
 TIME time;

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char timeDateToSet[15] = {55, 33, 13, 4, 05, 7, 22, 0};
char timeDateReadback[15];
char set_time[15];
unsigned char numaric_value[20];
unsigned char numaric_value[20];
int rtc_data[15];
char buffer[15];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	I2C1_init();
	 LCD_pin_init();
	 LCD_disp_init();
	// LCD_data('m');
	 lcd_send_string("RTC:");
	 deci_2_bcd_conver(timeDateToSet);
	 I2C1_burstWrite(SLAVE_ADDR, 0x00, 7, set_time);
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  LCD_command(0x80);
	   Get_Time(); //reading RTC data
	   sprintf (buffer, "%02d:%02d:%02d", time.hour, time.minutes, time.seconds);
	   // delay(1);
	   lcd_send_string(buffer);
	   // delay(1);
	   sprintf (buffer, "%02d-%02d-20%02d", time.dayofmonth, time.month, time.year);
	   // delay(1);
	   LCD_command(0xC0);
	   lcd_send_string(buffer);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PC0 PC1 PC2 PC3
                           PC4 PC5 PC6 PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB5 PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void I2C1_init(void)
{
RCC->AHB1ENR |= 2; /* Enable GPIOB clock */
 RCC->APB1ENR |= 0x00200000; /* Enable I2C1 clock */
 /* configure PB8, PB9 pins for I2C1 */
 GPIOB->AFR[1] &= ~0x000000FF; /* PB8, PB9 I2C1 SCL, SDA */
 GPIOB->AFR[1] |= 0x00000044;
 GPIOB->MODER &= ~0x000F0000; /* PB8, PB9 use alternate function */
 GPIOB->MODER |= 0x000A0000;
 GPIOB->OTYPER |= 0x00000300; /* output open-drain */
 GPIOB->PUPDR &= ~0x000F0000; /* with pull-ups */
 GPIOB->PUPDR |= 0x00050000;
 I2C1->CR1 = 0x8000; /* software reset I2C1 */
 I2C1->CR1 &= ~0x8000; /* out of reset */
 I2C1->CR2 = 0x0010; /* peripheral clock is 16 MHz */
I2C1->CR1 |= 0x400; /* Enabling the
acknowledgment */
 I2C1->CCR = 80; /* standard mode, 100kHz clock */
 I2C1->TRISE = 17; /* maximum rise time */
 I2C1->CR1 |= 0x0001; /* enable I2C1 module */
}


void I2C1_burstWrite(char saddr, char maddr, int n, char* data)
{
 int i;
 volatile int tmp;
 while (I2C1->SR2 & 2); /* wait until bus not busy */
 I2C1->CR1 &= ~0x800; /* disable POS */
 I2C1->CR1 |= 0x100; /* generate start */
 while (!(I2C1->SR1 & 1)); /* wait until start flag is set */
 I2C1->DR = saddr << 1; /* transmit slave address */
 while (!(I2C1->SR1 & 0x2)); /* wait until addr flag is set */
 tmp = I2C1->SR2; /* clear addr flag */
 while (!(I2C1->SR1 & 0x80)); /* wait until data register empty */
 I2C1->DR = maddr; /* send memory address */
 /* write all the data */
 for (i = 0; i < n; i++) {
 while (!(I2C1->SR1 & 0x80)); /* wait until data register empty */
 I2C1->DR = data++;
 }
 while (!(I2C1->SR1 & 4)); /* wait until transfer finished */
 I2C1->CR1 |= 0x200; /* generate stop */
}

void I2C1_burstRead(char saddr, char maddr, int n, char* data)
{
 volatile int tmp;
 while (I2C1->SR2 & 2);               /* wait until bus not busy */
 I2C1->CR1 &= ~0x800;                   /* disable POS */
 I2C1->CR1 |= 0x100;                          /* generate start */
 while (!(I2C1->SR1 & 1));                 /* wait until start flag is set */
 I2C1->DR = saddr << 1;                   /* transmit slave address + Write */
 while (!(I2C1->SR1 & 2));                 /* wait until addr flag is set */
 tmp = I2C1->SR2;                          /* clear addr flag */
 while (!(I2C1->SR1 & 0x80));               /* wait until transmitter empty */
 I2C1->DR = maddr;                      /* send memory address */
 while (!(I2C1->SR1 & 0x80));             /* wait until transmitter empty */
 I2C1->CR1 |= 0x100;                        /* generate restart */
 while (!(I2C1->SR1 & 1));            /* wait until start flag is set */
 I2C1->DR = saddr << 1 | 1;                /* transmit slave address + Read */
 while (!(I2C1->SR1 & 2));                      /* wait until addr flag is set */
 tmp = I2C1->SR2;                    /* clear addr flag */
 I2C1->CR1 |= 0x0400;              /* Enable Acknowledge */
 while(n > 0)
 {
 /* One byte left */
 if(n == 1)
 {
 I2C1->CR1 &= ~(0x400);         /* Disable Acknowledge */
 I2C1->CR1 |= 0x200;              /* Generate Stop */
 while (!(I2C1->SR1 & 0x40));    /* Wait for RXNE flag set */
 *data++ = I2C1->DR;
 break;
 }
 else
 {
 while (!(I2C1->SR1 & 0x40)); /* Wait until RXNE flag is set */
 *data++ = I2C1->DR;
 n--;
 }
 }
}

void Get_Time()
{
//uint8_t get_time[7];
I2C1_burstRead(SLAVE_ADDR, 0x00, 7, timeDateReadback);
time.seconds = BCDtoDecimal(timeDateReadback[0]);
time.minutes = BCDtoDecimal(timeDateReadback[1]);
time.hour = BCDtoDecimal(timeDateReadback[2]);
time.dayofweek = BCDtoDecimal(timeDateReadback[3]);
time.dayofmonth = BCDtoDecimal(timeDateReadback[4]);
time.month = BCDtoDecimal(timeDateReadback[5]);
time.year = BCDtoDecimal(timeDateReadback[6]);
}


void delay(uint32_t x)
{
for(int i=0;i<x;i++)
{
for(int j=0;j<3000;j++);
}
}
int BCDtoDecimal(int BCD)
{
return(((BCD>>4)*10) + (BCD & 0xf));
}
int decimalToBCD(int decimal)
{
return(((decimal/10)<<4) | (decimal%10));
}
void deci_2_bcd_conver(char *ptr)
{
int i=0;
while(i<7)
{
set_time[i] = decimalToBCD(*ptr);
i++;
ptr++;
}
}


void LCD_pin_init()
{
//port initialization
RCC -> AHB1ENR |= 0x06; //enable clock for port B and C
GPIOB -> MODER &= ~0x0000FC00; //clear pin PB5,6,7
GPIOB -> MODER |= 0x00005400; //set as output PB5,6,7
GPIOB -> ODR &= 0x0000FF1F; // making pin PB5,6,7
GPIOC -> MODER &= ~0x0000FFFF;
GPIOC -> MODER |= 0x00005555; // port c pin 0-7 configured as output pin
}

void LCD_disp_init()
{
LCD_command(0x38);//8 bit 2*16 data
delay(100);
LCD_command(0x06);//entry and cursur move right to left
delay(100);
LCD_command(0x01);//clear screen
delay(100);
LCD_command(0x80);//force curser to bigining of 1st row
delay(100);
//LCD_command(0x0f);//clear screen
LCD_command(0x0C); //disp on cursur off
delay(100);
}

void LCD_command(unsigned char command)
{
GPIOB->ODR &= 0xFF9F;//RS= 0;
GPIOB->ODR &= 0xFFBF;//R/W = 0;
GPIOC->ODR = command;
GPIOB->ODR |= 0x0080;//E = 1
delay(50);
GPIOB->ODR &= ~0x0080;//clear E
if(command<4)
delay(2);
else
delay(1);
}

void LCD_data(char data)
{
GPIOB->ODR |= 0x0020;//RS= 1;
GPIOB->ODR &= 0xFFBF;//R/W = 0;
GPIOC->ODR = data;//put data
GPIOB->ODR |= 0x0080;//E = 1
delay(50);
GPIOB->ODR &= ~0x0080;//clear E
delay(1);
}


void lcd_send_string (char *str)
{
int i;
for(i=0;*(str+i)!='\0';i++)
{
LCD_data(*(str+i));
delay(80);
}
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define IDC_A_5_Pin GPIO_PIN_13
#define IDC_A_5_GPIO_Port GPIOC
#define IDC_A_8_Pin GPIO_PIN_14
#define IDC_A_8_GPIO_Port GPIOC
#define IDC_A_7_Pin GPIO_PIN_15
#define IDC_A_7_GPIO_Port GPIOC
#define IDC_B_2__ADC1_IN10_Pin GPIO_PIN_0
#define IDC_B_2__ADC1_IN10_GPIO_Port GPIOC
#define IDC_B_1__ADC1_IN11_Pin GPIO_PIN_1
#define IDC_B_1__ADC1_IN11_GPIO_Port GPIOC
#define IDC_B_4__ADC2_IN12_Pin GPIO_PIN_2
#define IDC_B_4__ADC2_IN12_GPIO_Port GPIOC
#define IDC_B_3__ADC2_IN13_Pin GPIO_PIN_3
#define IDC_B_3__ADC2_IN13_GPIO_Port GPIOC
#define IDC_B_6_Pin GPIO_PIN_0
#define IDC_B_6_GPIO_Port GPIOA
#define IDC_B_5_Pin GPIO_PIN_1
#define IDC_B_5_GPIO_Port GPIOA
#define IDC_C_7_Pin GPIO_PIN_4
#define IDC_C_7_GPIO_Port GPIOA
#define IDC_C_8_Pin GPIO_PIN_5
#define IDC_C_8_GPIO_Port GPIOA
#define IDC_C_5_Pin GPIO_PIN_6
#define IDC_C_5_GPIO_Port GPIOA
#define IDC_C_6_Pin GPIO_PIN_7
#define IDC_C_6_GPIO_Port GPIOA
#define IDC_B_8_Pin GPIO_PIN_4
#define IDC_B_8_GPIO_Port GPIOC
#define IDC_B_7_Pin GPIO_PIN_5
#define IDC_B_7_GPIO_Port GPIOC
#define IDC_C_3_Pin GPIO_PIN_0
#define IDC_C_3_GPIO_Port GPIOB
#define IDC_C_4_Pin GPIO_PIN_1
#define IDC_C_4_GPIO_Port GPIOB
#define IDC_C_1_Pin GPIO_PIN_2
#define IDC_C_1_GPIO_Port GPIOB
#define IDC_C_2_Pin GPIO_PIN_6
#define IDC_C_2_GPIO_Port GPIOC
#define OUT_ex_JTDI__LED_RED_Pin GPIO_PIN_15
#define OUT_ex_JTDI__LED_RED_GPIO_Port GPIOA
#define IDC_A_2_Pin GPIO_PIN_10
#define IDC_A_2_GPIO_Port GPIOC
#define IDC_A_1_Pin GPIO_PIN_11
#define IDC_A_1_GPIO_Port GPIOC
#define IDC_A_4_Pin GPIO_PIN_12
#define IDC_A_4_GPIO_Port GPIOC
#define OUT__USB_DISCONNECT_Pin GPIO_PIN_2
#define OUT__USB_DISCONNECT_GPIO_Port GPIOD
#define OUT_ex_JTDO__LED_BLUE_Pin GPIO_PIN_3
#define OUT_ex_JTDO__LED_BLUE_GPIO_Port GPIOB
#define OUT_exNJTRST__LED_GREEN_Pin GPIO_PIN_4
#define OUT_exNJTRST__LED_GREEN_GPIO_Port GPIOB
#define IDC_A_3_Pin GPIO_PIN_5
#define IDC_A_3_GPIO_Port GPIOB
#define IDC_A_6_Pin GPIO_PIN_6
#define IDC_A_6_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

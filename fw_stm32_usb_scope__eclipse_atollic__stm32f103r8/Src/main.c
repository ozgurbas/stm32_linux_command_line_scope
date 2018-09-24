
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */

//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
//		eclipse setup:
//		please  add
//				"@@@mark:"
//				"@@@note:"
//				"@@@revision:"
//				"@@@trick:"
//		to "preferences > C/C++ > Editor > Task Tags"
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
//		hw summary:
//		IDC_A 	>>> digital inputs	>>> sch CNN1
//		IDC_B 	>>> analog inputs	>>> sch CNN3
//		IDC_C 	>>> digital outputs	>>> sch CNN4   >>> PA4 ve PA5 icin, R10 ve R12 takılı R9 ve R11 sokulu olmali. R17 ve R15 de sokulu olmalı
//					P3 de DAC yada usart3 secimi, CNN4 de usart3 yada DAC secimi caprazlama opsiyonu koymusum.
//		IDC_D 	>>> ?????????????	>>> sch CNN5
//
//		LAYOUT:
//			(IDC_B)			(IDC_A)
//						(IDC_JTAG)	(USB)
//			(IDC_C)			(IDC_D)
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


#include "sys_top_level_GLOBAL.h"


//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */


u8		u8_tmp_1;
u8		u8_tmp_2;
u8		u8_tmp_3;

u16		u16_tmp_1;
u16		u16_tmp_2;
u16		u16_tmp_3;

u32		u32_tmp_1;
u32		u32_tmp_2;
u32		u32_tmp_3;
u32		u32_tmp_4;


void f_GPIO_Init__set__IDC_C_as_full_output(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	//GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	GPIO_InitStruct.Pin = IDC_C_1_Pin;
	HAL_GPIO_Init(IDC_C_1_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_C_2_Pin;
	HAL_GPIO_Init(IDC_C_2_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_C_3_Pin;
	HAL_GPIO_Init(IDC_C_3_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_C_4_Pin;
	HAL_GPIO_Init(IDC_C_4_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_C_5_Pin;
	HAL_GPIO_Init(IDC_C_5_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_C_6_Pin;
	HAL_GPIO_Init(IDC_C_6_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_C_7_Pin;
	HAL_GPIO_Init(IDC_C_7_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_C_8_Pin;
	HAL_GPIO_Init(IDC_C_8_GPIO_Port, &GPIO_InitStruct);
}

void f_GPIO_Init__set__IDC_A_as_full_output(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	//GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	GPIO_InitStruct.Pin = IDC_A_1_Pin;
	HAL_GPIO_Init(IDC_A_1_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_A_2_Pin;
	HAL_GPIO_Init(IDC_A_2_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_A_3_Pin;
	HAL_GPIO_Init(IDC_A_3_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_A_4_Pin;
	HAL_GPIO_Init(IDC_A_4_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_A_5_Pin;
	HAL_GPIO_Init(IDC_A_5_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_A_6_Pin;
	HAL_GPIO_Init(IDC_A_6_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_A_7_Pin;
	HAL_GPIO_Init(IDC_A_7_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_A_8_Pin;
	HAL_GPIO_Init(IDC_A_8_GPIO_Port, &GPIO_InitStruct);
}

void f_GPIO_Init__set__IDC_A_as_full_input_pulled_up(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	//GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	GPIO_InitStruct.Pin = IDC_A_1_Pin;
	HAL_GPIO_Init(IDC_A_1_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_A_2_Pin;
	HAL_GPIO_Init(IDC_A_2_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_A_3_Pin;
	HAL_GPIO_Init(IDC_A_3_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_A_4_Pin;
	HAL_GPIO_Init(IDC_A_4_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_A_5_Pin;
	HAL_GPIO_Init(IDC_A_5_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_A_6_Pin;
	HAL_GPIO_Init(IDC_A_6_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_A_7_Pin;
	HAL_GPIO_Init(IDC_A_7_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = IDC_A_8_Pin;
	HAL_GPIO_Init(IDC_A_8_GPIO_Port, &GPIO_InitStruct);
}


//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{
//USB_HID variables & constants

u8 u8_array_sys_usbHID__RX[def_u8_USB_HID_LENGTH];
u8 u8_array_sys_usbHID__TX[def_u8_USB_HID_LENGTH];
u8 u8_sys_usbHID_i;

#include	"sys_usbHID__definitions__command_from_PC.h"
#include	"sys_usbHID__definitions__state.h"

u16 		u16_sys_usbHID__COMMAND_from_PC=def_u16_sys_usbHID__COMMAND_from_PC__NOP;

u16 		u16_sys_usbHID__COMMAND_TMP_1;
u16 		u16_sys_usbHID__PARAMETER_TMP_1;

u8 			u8_sys_usbHID__MAIN_STATE=def_u8_sys_usbHID__MAIN_STATE__READY;
u8 			u8_sys_usbHID__MAIN_STATE_NEXT=def_u8_sys_usbHID__MAIN_STATE__READY;
u16 		u16_sys_usbHID__time_down_counter_1=0;
u16 		u16_sys_usbHID__time_down_counter_2=0;

u8 			u8_sys_usbHID__SUB_STATE=0;

u16 		u16_sys_usbHID__in_ms_TIME_OF_RECORD_START;
u16 		u16_sys_usbHID__in_ms_TIME_OF_OUT_1_ON;
u16 		u16_sys_usbHID__in_ms_TIME_OF_OUT_2_ON;
u16 		u16_sys_usbHID__in_ms_TIME_OF_OUT_3_ON;
u16 		u16_sys_usbHID__in_ms_TIME_OF_OUT_4_ON;
u16 		u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD;
u16 		u16_sys_usbHID__in_ms_TIME_OF_OUT_1_OFF;
u16 		u16_sys_usbHID__in_ms_TIME_OF_OUT_2_OFF;
u16 		u16_sys_usbHID__in_ms_TIME_OF_OUT_3_OFF;
u16 		u16_sys_usbHID__in_ms_TIME_OF_OUT_4_OFF;

//}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}

//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{
//USB_HID__SCOPE variables & constants

//#define		def_u16_sys_usbHID__SCOPE__U32_DMA_BUFFER_LENGTH	4000	>>> region `RAM' overflowed by 68 bytes
#define		def_u16_sys_usbHID__SCOPE__U32_DMA_BUFFER_LENGTH		3800

uint32_t u32_array_ADC_1_2_DMA_COPY[def_u16_sys_usbHID__SCOPE__U32_DMA_BUFFER_LENGTH];
//}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}

//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{
//USB_HID__SCOPE functions
void	f_sys_usbHID__SCOPE__CLEAN__U32_DMA_BUFFER(void)
{
	u16	clean_index;
	for(clean_index=0;clean_index<def_u16_sys_usbHID__SCOPE__U32_DMA_BUFFER_LENGTH;clean_index++)
	{
		u32_array_ADC_1_2_DMA_COPY[clean_index]=0;
	}
}

//}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}

u8		u8_one_shot_forced_function_test_flag=0;
u8		u8_interrupt_tim3_flag=0;
u16		u16_interrupt_tim3_counter=0;
u16		u16_interrupt_adc_counter=0;
u16		i;

void	f__insert_indexed_u16_hid_parameter_to_TX_array(u8	u8_f_in_parameter_index, u16 u16_f_in_parameter_value)
{
	if(u8_f_in_parameter_index<32)
	{
		u8_f_in_parameter_index*=2;	//u16 icin
		u8_array_sys_usbHID__TX[u8_f_in_parameter_index]=(u8)u16_f_in_parameter_value;	//low
		u16_f_in_parameter_value>>=8;
		u8_f_in_parameter_index++;
		u8_array_sys_usbHID__TX[u8_f_in_parameter_index]=(u8)u16_f_in_parameter_value;	//high
	}
}

u16		f_u16__return_indexed_u16_hid_parameter_from_RX_array(u8	u8_f_in_parameter_index)
{
	u16 u16_tmp_1_in_f;
	u16_tmp_1_in_f=0;
	if(u8_f_in_parameter_index<32)
	{
		u8_f_in_parameter_index*=2;	//u16 icin
		u8_f_in_parameter_index++;
		u16_tmp_1_in_f=u8_array_sys_usbHID__RX[u8_f_in_parameter_index];
		u16_tmp_1_in_f<<=8;
		u8_f_in_parameter_index--;
		u16_tmp_1_in_f+=u8_array_sys_usbHID__RX[u8_f_in_parameter_index];
	}

	return u16_tmp_1_in_f;
}


void USB_HID_QUERY_read_ports_to_TX_ARRAY(void)
{
	  u8_array_sys_usbHID__TX[5]=0;
	  if(HAL_GPIO_ReadPin(IDC_A_1_GPIO_Port, IDC_A_1_Pin)==GPIO_PIN_SET)
	  {
		  u8_array_sys_usbHID__TX[5]+=1;
	  }
	  if(HAL_GPIO_ReadPin(IDC_A_2_GPIO_Port, IDC_A_2_Pin)==GPIO_PIN_SET)
	  {
		  u8_array_sys_usbHID__TX[5]+=2;
	  }
	  if(HAL_GPIO_ReadPin(IDC_A_3_GPIO_Port, IDC_A_3_Pin)==GPIO_PIN_SET)
	  {
		  u8_array_sys_usbHID__TX[5]+=4;
	  }
	  if(HAL_GPIO_ReadPin(IDC_A_4_GPIO_Port, IDC_A_4_Pin)==GPIO_PIN_SET)
	  {
		  u8_array_sys_usbHID__TX[5]+=8;
	  }
	  if(HAL_GPIO_ReadPin(IDC_A_5_GPIO_Port, IDC_A_5_Pin)==GPIO_PIN_SET)
	  {
		  u8_array_sys_usbHID__TX[5]+=16;
	  }
	  if(HAL_GPIO_ReadPin(IDC_A_6_GPIO_Port, IDC_A_6_Pin)==GPIO_PIN_SET)
	  {
		  u8_array_sys_usbHID__TX[5]+=32;
	  }
	  if(HAL_GPIO_ReadPin(IDC_A_7_GPIO_Port, IDC_A_7_Pin)==GPIO_PIN_SET)
	  {
		  u8_array_sys_usbHID__TX[5]+=64;
	  }
	  if(HAL_GPIO_ReadPin(IDC_A_8_GPIO_Port, IDC_A_8_Pin)==GPIO_PIN_SET)
	  {
		  u8_array_sys_usbHID__TX[5]+=128;
	  }
}

void f__start_record_with_TIMER_ADC_DMA(void)
{
	HAL_ADC_Start_DMA	(	(ADC_HandleTypeDef*)(&hadc1), (uint32_t*)(u32_array_ADC_1_2_DMA_COPY), def_u16_sys_usbHID__SCOPE__U32_DMA_BUFFER_LENGTH);
	HAL_ADC_Start		(	(ADC_HandleTypeDef*)(&hadc2));

	HAL_TIM_Base_Start(&htim3); 			//"HAL_ADC_Start_IT" ile tetikliyor
}

void USB_HID_QUERY_HANDLE(void)
{
		//  "ECxxxx..." echo not received:

		//PC is always master. slave can not respose without master query!!!

		//tx clean.
		for(u8_sys_usbHID_i=0;u8_sys_usbHID_i<def_u8_USB_HID_LENGTH;u8_sys_usbHID_i++)
		{
			u8_array_sys_usbHID__TX[u8_sys_usbHID_i]=0;
		}

		//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{
		//extract command: (little endian)
		u16_sys_usbHID__COMMAND_from_PC=f_u16__return_indexed_u16_hid_parameter_from_RX_array(0);
		//}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}

		//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{
		switch(u16_sys_usbHID__COMMAND_from_PC)
		{

			case(def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__CLEAN_REGISTERS):
			{

			} break;

			case(def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__GET_STATES):
			{
				u8_array_sys_usbHID__TX[0]=u8_array_sys_usbHID__RX[0];		//command echo!!!
				u8_array_sys_usbHID__TX[1]=u8_array_sys_usbHID__RX[1];

				u8_array_sys_usbHID__TX[2]=u8_sys_usbHID__MAIN_STATE;

				u8_array_sys_usbHID__TX[3]=u8_sys_usbHID__SUB_STATE;

			} break;

			case(def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__START_DMA_RECORD_w_PARAMETERS):
			{
				if(u8_sys_usbHID__MAIN_STATE==def_u8_sys_usbHID__MAIN_STATE__READY)
				{
					u8_array_sys_usbHID__TX[0]=u8_array_sys_usbHID__RX[0];		//command echo!!!
					u8_array_sys_usbHID__TX[1]=u8_array_sys_usbHID__RX[1];


					//HAL_ADC_Stop_DMA((ADC_HandleTypeDef*)(&hadc1));	//bu riskli calismazken sorun oluyormu dene!!!
					HAL_TIM_Base_Stop(&htim3);
					f_sys_usbHID__SCOPE__CLEAN__U32_DMA_BUFFER();

					//4 kanal ve ornek sayısı sabit, sadece zaman parametresi.
					//parametre mikro sn cinsinden olan timer3 periyot a basılacak, zaten 16 bit.
					TIM3->ARR=f_u16__return_indexed_u16_hid_parameter_from_RX_array(1);


	//				u16_sys_usbHID__COMMAND_TMP_1=def_u16_sys_usbHID__SCOPE__U32_DMA_BUFFER_LENGTH; // bu yanlis /2 olmicak, arrayin yarısını doldur olur ozaman!!!
	//				u16_sys_usbHID__COMMAND_TMP_1/=2;
	//				HAL_ADC_Start_DMA	(	(ADC_HandleTypeDef*)(&hadc1), (uint32_t*)(u32_array_ADC_1_2_DMA_COPY), u16_sys_usbHID__COMMAND_TMP_1);
					HAL_ADC_Start_DMA	(	(ADC_HandleTypeDef*)(&hadc1), (uint32_t*)(u32_array_ADC_1_2_DMA_COPY), def_u16_sys_usbHID__SCOPE__U32_DMA_BUFFER_LENGTH);
					HAL_ADC_Start		(	(ADC_HandleTypeDef*)(&hadc2));

					HAL_TIM_Base_Start(&htim3); 			//"HAL_ADC_Start_IT" ile tetikliyor

					u8_sys_usbHID__MAIN_STATE_NEXT=def_u8_sys_usbHID__MAIN_STATE__RECORD;
				}
				else
				{
					u8_array_sys_usbHID__TX[0]=255;		//error sign!!!
					u8_array_sys_usbHID__TX[1]=255;
				}

			} break;

			case(def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__START_DMA_RECORD_w_TRIGGER_IO):
			{
				if(u8_sys_usbHID__MAIN_STATE==def_u8_sys_usbHID__MAIN_STATE__READY)
				{
					u8_array_sys_usbHID__TX[0]=u8_array_sys_usbHID__RX[0];		//command echo!!!
					u8_array_sys_usbHID__TX[1]=u8_array_sys_usbHID__RX[1];


					//HAL_ADC_Stop_DMA((ADC_HandleTypeDef*)(&hadc1));	//bu riskli calismazken sorun oluyormu dene!!!
					HAL_TIM_Base_Stop(&htim3);
					f_sys_usbHID__SCOPE__CLEAN__U32_DMA_BUFFER();

					//4 kanal ve ornek sayısı sabit, sadece zaman parametresi.
					//parametre mikro sn cinsinden olan timer3 periyot a basılacak, zaten 16 bit.
					TIM3->ARR=f_u16__return_indexed_u16_hid_parameter_from_RX_array(1);


					u16_sys_usbHID__PARAMETER_TMP_1=f_u16__return_indexed_u16_hid_parameter_from_RX_array(2);	//parametre 2: trigger mode

					u8_sys_usbHID__SUB_STATE=def_u8_sys_usbHID__SUB_STATE_of_RECORD__NOT_DEFINED;
					u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD=0;
					u16_sys_usbHID__in_ms_TIME_OF_RECORD_START=0;
					u16_sys_usbHID__in_ms_TIME_OF_OUT_1_ON=0;
					u16_sys_usbHID__in_ms_TIME_OF_OUT_2_ON=0;
					u16_sys_usbHID__in_ms_TIME_OF_OUT_3_ON=0;
					u16_sys_usbHID__in_ms_TIME_OF_OUT_4_ON=0;

					u16_sys_usbHID__in_ms_TIME_OF_OUT_1_OFF=0;
					u16_sys_usbHID__in_ms_TIME_OF_OUT_2_OFF=0;
					u16_sys_usbHID__in_ms_TIME_OF_OUT_3_OFF=0;
					u16_sys_usbHID__in_ms_TIME_OF_OUT_4_OFF=0;

					switch(u16_sys_usbHID__PARAMETER_TMP_1)
					{
						case(def_u16_sys_usbHID__SCOPE__P2_TRIGGER_MODE__4_output):	//3 ise digital output tetikleme, 4 lu, birer zamanlı.
						case(def_u16_sys_usbHID__SCOPE__P2_TRIGGER_MODE__1_output):	//6 ise digital output tetikleme, 1 li dort zamanlı.
						{


							u16_sys_usbHID__in_ms_TIME_OF_RECORD_START=	f_u16__return_indexed_u16_hid_parameter_from_RX_array(5);		//parametre 5: "digital output tetikleme" de 0-10000. ms arasi kayitin baslama zamani.
							u16_sys_usbHID__in_ms_TIME_OF_OUT_1_ON=		f_u16__return_indexed_u16_hid_parameter_from_RX_array(6);		//parametre 6: "digital output tetikleme" de 0-10000. ms arasi output 1 on zamani.
							u16_sys_usbHID__in_ms_TIME_OF_OUT_2_ON=		f_u16__return_indexed_u16_hid_parameter_from_RX_array(7);		//parametre 7: "digital output tetikleme" de 0-10000. ms arasi output 2 on zamani.
							u16_sys_usbHID__in_ms_TIME_OF_OUT_3_ON=		f_u16__return_indexed_u16_hid_parameter_from_RX_array(8);		//parametre 8: "digital output tetikleme" de 0-10000. ms arasi output 3 on zamani.
							u16_sys_usbHID__in_ms_TIME_OF_OUT_4_ON=		f_u16__return_indexed_u16_hid_parameter_from_RX_array(9);		//parametre 9: "digital output tetikleme" de 0-10000. ms arasi output 4 on zamani.

							u16_sys_usbHID__in_ms_TIME_OF_OUT_1_OFF=	f_u16__return_indexed_u16_hid_parameter_from_RX_array(10);		//parametre 10: "digital output tetikleme" de 0-10000. ms arasi output 1 off zamani.
							u16_sys_usbHID__in_ms_TIME_OF_OUT_2_OFF=	f_u16__return_indexed_u16_hid_parameter_from_RX_array(11);		//parametre 11: "digital output tetikleme" de 0-10000. ms arasi output 2 off zamani.
							u16_sys_usbHID__in_ms_TIME_OF_OUT_3_OFF=	f_u16__return_indexed_u16_hid_parameter_from_RX_array(12);		//parametre 12: "digital output tetikleme" de 0-10000. ms arasi output 3 off zamani.
							u16_sys_usbHID__in_ms_TIME_OF_OUT_4_OFF=	f_u16__return_indexed_u16_hid_parameter_from_RX_array(13);		//parametre 13: "digital output tetikleme" de 0-10000. ms arasi output 4 off zamani.

							//@@@mark: 000_last_edit:
							HAL_GPIO_WritePin(IDC_C_1_GPIO_Port, IDC_C_1_Pin, GPIO_PIN_RESET);
							HAL_GPIO_WritePin(IDC_C_2_GPIO_Port, IDC_C_2_Pin, GPIO_PIN_RESET);
							HAL_GPIO_WritePin(IDC_C_3_GPIO_Port, IDC_C_3_Pin, GPIO_PIN_RESET);
							HAL_GPIO_WritePin(IDC_C_4_GPIO_Port, IDC_C_4_Pin, GPIO_PIN_RESET);

							if(u16_sys_usbHID__PARAMETER_TMP_1==def_u16_sys_usbHID__SCOPE__P2_TRIGGER_MODE__4_output)
							{
								u8_sys_usbHID__SUB_STATE=def_u8_sys_usbHID__SUB_STATE_of_RECORD__w_TRIGGER_4IO;
							}
							else
							{
								u8_sys_usbHID__SUB_STATE=def_u8_sys_usbHID__SUB_STATE_of_RECORD__w_TRIGGER_1IO;
							}

							u8_sys_usbHID__MAIN_STATE_NEXT=def_u8_sys_usbHID__MAIN_STATE__RECORD;

						} break;

						case(def_u16_sys_usbHID__SCOPE__P2_TRIGGER_MODE__w_waiting_input_1_RISE):
						case(def_u16_sys_usbHID__SCOPE__P2_TRIGGER_MODE__w_waiting_input_1_FALL):
						{

							u16_sys_usbHID__time_down_counter_2=f_u16__return_indexed_u16_hid_parameter_from_RX_array(3); 	//"u16_f_in__time_out_in_sec"
							u16_sys_usbHID__time_down_counter_2*=1000;	// convert to milli sec base.

							if(u16_sys_usbHID__PARAMETER_TMP_1==def_u16_sys_usbHID__SCOPE__P2_TRIGGER_MODE__w_waiting_input_1_RISE)
							{
								u8_sys_usbHID__SUB_STATE=def_u8_sys_usbHID__SUB_STATE_of_RECORD__w_waiting_input_1_RISE;
							}
							else
							{
								u8_sys_usbHID__SUB_STATE=def_u8_sys_usbHID__SUB_STATE_of_RECORD__w_waiting_input_1_FALL;
							}

							u8_sys_usbHID__MAIN_STATE_NEXT=def_u8_sys_usbHID__MAIN_STATE__RECORD;

						} break;

						default:
						{
							u8_array_sys_usbHID__TX[0]=255;		//error sign!!!
							u8_array_sys_usbHID__TX[1]=255;
						}
						break;
					}

				}
				else
				{
					u8_array_sys_usbHID__TX[0]=255;		//error sign!!!
					u8_array_sys_usbHID__TX[1]=255;
				}
			} break;

			case(def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__GET_INDEXED_RECORD_DATA):
			{
				if(u8_sys_usbHID__MAIN_STATE==def_u8_sys_usbHID__MAIN_STATE__READY)
				{
					u16_sys_usbHID__COMMAND_TMP_1=u8_array_sys_usbHID__RX[3];	//H
					u16_sys_usbHID__COMMAND_TMP_1<<=8;
					u16_sys_usbHID__COMMAND_TMP_1+=u8_array_sys_usbHID__RX[2];	//L


					//bu parametre kacinci ornek oldugu parametresidir.
					//4 kanal ornek arrayde iki 32 byte bir ornek oldugundan, index iki ile carpilir.
					u16_sys_usbHID__COMMAND_TMP_1*=2;

					//u32_array_ADC_1_2_DMA_COPY[] uzerinde 8byte lık bloklardan 12 bitlik adc sonucları bosluklari ayiklanip ziplenicek 60 byte icine
					u8_tmp_1=4;	//bu arraydeki datanin baslangic yeri, ilk dort byte cmd ve index sonrası
					u16_tmp_1=u16_sys_usbHID__COMMAND_TMP_1;	//bu dma arraydeki index yeri.

					u16_tmp_2=u16_tmp_1+20;

					if(u16_tmp_2<=def_u16_sys_usbHID__SCOPE__U32_DMA_BUFFER_LENGTH) 	//istek arrayden tasmiyorsa
					{
						for(i=0;i<10;i++)
						{
							u32_tmp_1=u32_array_ADC_1_2_DMA_COPY[u16_tmp_1];
							u16_tmp_1++;
							u32_tmp_2=u32_array_ADC_1_2_DMA_COPY[u16_tmp_1];
							u16_tmp_1++;

							u32_tmp_3=u32_tmp_1 & 0xfff;	//ch1, adc1_1
							u32_tmp_4=u32_tmp_2 & 0xfff;	//ch2, adc1_2
							u32_tmp_4<<=12;
							u32_tmp_4+=u32_tmp_3; //3 byte ch1 and ch2 ready.

							u8_array_sys_usbHID__TX[u8_tmp_1]=(u8)(u32_tmp_4);
							u32_tmp_4>>=8;
							u8_tmp_1++;
							u8_array_sys_usbHID__TX[u8_tmp_1]=(u8)(u32_tmp_4);
							u32_tmp_4>>=8;
							u8_tmp_1++;
							u8_array_sys_usbHID__TX[u8_tmp_1]=(u8)(u32_tmp_4);
							//u32_tmp_4>>=8;
							u8_tmp_1++;


							u32_tmp_3=u32_tmp_1 & 0xfff0000;	//ch3, adc2_1
							u32_tmp_4=u32_tmp_2 & 0xfff0000;	//ch4, adc2_2
							u32_tmp_3>>=16;
							u32_tmp_4>>=16;

							u32_tmp_4<<=12;
							u32_tmp_4+=u32_tmp_3; //3 byte ch1 and ch2 ready.

							u8_array_sys_usbHID__TX[u8_tmp_1]=(u8)(u32_tmp_4);
							u32_tmp_4>>=8;
							u8_tmp_1++;
							u8_array_sys_usbHID__TX[u8_tmp_1]=(u8)(u32_tmp_4);
							u32_tmp_4>>=8;
							u8_tmp_1++;
							u8_array_sys_usbHID__TX[u8_tmp_1]=(u8)(u32_tmp_4);
							//u32_tmp_4>>=8;
							u8_tmp_1++;

							//6 byte inserted!!! her adc ornek 1.5 byte!!!
							//60byte/1.5=40 adc ornek
							//40 ornek/ 4 kanal = 10 4lu adc ornek demek
							//10 ornek ilerleme 32bit arrayde index de 20 ilerleme demek!!!

						}


						u8_array_sys_usbHID__TX[0]=u8_array_sys_usbHID__RX[0];		//command echo!!!
						u8_array_sys_usbHID__TX[1]=u8_array_sys_usbHID__RX[1];

						u8_array_sys_usbHID__TX[2]=u8_array_sys_usbHID__RX[2];		//parameter 1 index echo!!!
						u8_array_sys_usbHID__TX[3]=u8_array_sys_usbHID__RX[3];
					}
					else
					{
						u8_array_sys_usbHID__TX[0]=255;		//error sign!!!
						u8_array_sys_usbHID__TX[1]=255;
					}


				}
				else
				{
					u8_array_sys_usbHID__TX[0]=255;		//error sign!!!
					u8_array_sys_usbHID__TX[1]=255;
				}
			} break;



		}
		//}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}

}	//end of 	"void USB_HID_QUERY_HANDLE(void)"




u32_u16_u8_u1 	u32_u16_u8_u1_SYSTICK__time_flags;
#define 	u1_flag_SYSTICK_1ms				u32_u16_u8_u1_SYSTICK__time_flags.u1.u1_8
#define 	u1_flag_SYSTICK_10ms			u32_u16_u8_u1_SYSTICK__time_flags.u1.u1_9
#define 	u1_flag_SYSTICK_100ms			u32_u16_u8_u1_SYSTICK__time_flags.u1.u1_10
#define 	u1_flag_SYSTICK_1000ms			u32_u16_u8_u1_SYSTICK__time_flags.u1.u1_11
#define 	u1_flag_SYSTICK_1HZ_TOGGLED		u32_u16_u8_u1_SYSTICK__time_flags.u1.u1_31

uint8_t 	u8_10_ms_counter;
uint8_t 	u8_100_ms_counter;
uint8_t 	u8_1000_ms_counter;

void f_SYSTICK__prepare_time_flags_at_out_of_INTERRUPT(void)
{
	u8_10_ms_counter++;
	if(u8_10_ms_counter>9)
	{
		u8_10_ms_counter=0;
		u1_flag_SYSTICK_10ms=1;
		u8_100_ms_counter++;
		if(u8_100_ms_counter>9)
		{
			u8_100_ms_counter=0;
			u1_flag_SYSTICK_100ms=1;
			u8_1000_ms_counter++;
			if(u8_1000_ms_counter>9)
			{
				u8_1000_ms_counter=0;
				u1_flag_SYSTICK_1000ms=1;

				if(u1_flag_SYSTICK_1HZ_TOGGLED==0)
				{
					u1_flag_SYSTICK_1HZ_TOGGLED=1;
				}
				else
				{
					u1_flag_SYSTICK_1HZ_TOGGLED=0;
				}
			}
		}
	}
}
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	if(htim->Instance==TIM4)
//	{
//		u1_flag_SYSTICK_1ms=1;
//	}
//}

//alttaki interrupt enable da calisiyor
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM4)
	{
		u1_flag_SYSTICK_1ms=1;
	}
}

//not in use!!! used in tests only!!!
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM3)
	{
		u8_interrupt_tim3_flag=1;
		u16_interrupt_tim3_counter++;
		if(u16_interrupt_tim3_counter>60)
		{
			HAL_ADC_Stop_DMA((ADC_HandleTypeDef*)(&hadc1));
			u16_interrupt_tim3_counter=0;
		}
	}
}

void	f__fill_adc_dma_buffer_with_test_values(void)
{
	u16 u16_fill_i;
	u16 u16_fill_j;
	u32 u32_fill_tmp;

//	u32_array_ADC_1_2_DMA_COPY[0]=0x03330111;
//	u32_array_ADC_1_2_DMA_COPY[1]=0x04440222;
//	u32_array_ADC_1_2_DMA_COPY[2]=0x03340112;
//	u32_array_ADC_1_2_DMA_COPY[3]=0x04450223;
//	u32_array_ADC_1_2_DMA_COPY[4]=0x03350113;
//	u32_array_ADC_1_2_DMA_COPY[5]=0x04460224;

	for(u16_fill_i=0;u16_fill_i<1900;u16_fill_i++)
	{

//		//ch1 test OK!!!
//		u16_fill_j=2*u16_fill_i;
//		u32_array_ADC_1_2_DMA_COPY[u16_fill_j]=u16_fill_i;
//		u16_fill_j++;
//		u32_array_ADC_1_2_DMA_COPY[u16_fill_j]=0;

//		//ch 2 test OK!!!
//		u16_fill_j=2*u16_fill_i;
//		u32_array_ADC_1_2_DMA_COPY[u16_fill_j]=0;
//		u16_fill_j++;
//		u32_array_ADC_1_2_DMA_COPY[u16_fill_j]=u16_fill_i;

//		//ch3 test OK!!!
//		u16_fill_j=2*u16_fill_i;
//		u32_array_ADC_1_2_DMA_COPY[u16_fill_j]=u16_fill_i<<16;
//		u16_fill_j++;
//		u32_array_ADC_1_2_DMA_COPY[u16_fill_j]=0;

//		//ch4 test OK!!!
//		u16_fill_j=2*u16_fill_i;
//		u32_array_ADC_1_2_DMA_COPY[u16_fill_j]=0;
//		u16_fill_j++;
//		u32_array_ADC_1_2_DMA_COPY[u16_fill_j]=u16_fill_i<<16;

	}


	for(u16_fill_i=0;u16_fill_i<1900;u16_fill_i++)
	{
		u16_fill_j=2*u16_fill_i;

		u32_fill_tmp=u16_fill_i+300;
		u32_fill_tmp<<=16;
		u32_array_ADC_1_2_DMA_COPY[u16_fill_j]=100+u16_fill_i+u32_fill_tmp;

		u16_fill_j++;
		u32_fill_tmp=u16_fill_i+400;
		u32_fill_tmp<<=16;
		u32_array_ADC_1_2_DMA_COPY[u16_fill_j]=200+u16_fill_i+u32_fill_tmp;
	}
}


void	f__END_OF_RECORD(void)
{
	u8_sys_usbHID__MAIN_STATE_NEXT=def_u8_sys_usbHID__MAIN_STATE__READY;
}

void	HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)		//onemli bu fonksiyon "ADC_DMAConvCplt" icinden cagiriliyor.
{
	 if (hadc->Instance == ADC1)
	 {
		 //test only:
//		 u16_interrupt_adc_counter++;
//		 if(u16_interrupt_adc_counter>300)
//		 {
//			 u16_interrupt_adc_counter=0;
//			 //HAL_TIM_OC_Stop_IT(&htim4, TIM_CHANNEL_4);
//		 }

		 //DMA buffer ready!!!
		 HAL_TIM_Base_Stop(&htim3);

		 f__END_OF_RECORD();

		 //f__fill_adc_dma_buffer_with_test_values();
	 }

	 UNUSED(hadc);
}
void                    HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{
	UNUSED(hadc);
}
void                    HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc)
{
	UNUSED(hadc);
}
void                    HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
	UNUSED(hadc);
}




extern 	ADC_HandleTypeDef hadc1;
extern 	ADC_HandleTypeDef hadc2;
extern 	DMA_HandleTypeDef hdma_adc1;

void	f__ligth_ON_LED__RED__RECORD(void)
{
	HAL_GPIO_WritePin(OUT_ex_JTDI__LED_RED_GPIO_Port, OUT_ex_JTDI__LED_RED_Pin, GPIO_PIN_SET);
}

void	f__ligth_OFF_LED__RED__RECORD(void)
{
	HAL_GPIO_WritePin(OUT_ex_JTDI__LED_RED_GPIO_Port, OUT_ex_JTDI__LED_RED_Pin, GPIO_PIN_RESET);
}

void	f__ligth_ON_LED__GREEN__READY(void)
{
	HAL_GPIO_WritePin(OUT_exNJTRST__LED_GREEN_GPIO_Port, OUT_exNJTRST__LED_GREEN_Pin, GPIO_PIN_SET);
}

void	f__ligth_OFF_LED__GREEN__READY(void)
{
	HAL_GPIO_WritePin(OUT_exNJTRST__LED_GREEN_GPIO_Port, OUT_exNJTRST__LED_GREEN_Pin, GPIO_PIN_RESET);
}

//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
void	f__1ms_base_main_state_machine(void)
{
	if(u16_sys_usbHID__time_down_counter_1>0)
	{
		u16_sys_usbHID__time_down_counter_1--;
	}

	if(u16_sys_usbHID__time_down_counter_2>0)
	{
		u16_sys_usbHID__time_down_counter_2--;
	}

	//detection of state change request :
	//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
	if(u8_sys_usbHID__MAIN_STATE_NEXT!=u8_sys_usbHID__MAIN_STATE)
	{
		u8_sys_usbHID__MAIN_STATE=u8_sys_usbHID__MAIN_STATE_NEXT;

		if(u8_sys_usbHID__MAIN_STATE==def_u8_sys_usbHID__MAIN_STATE__READY)
		{
			f__ligth_OFF_LED__RED__RECORD();
		}
		else if(u8_sys_usbHID__MAIN_STATE==def_u8_sys_usbHID__MAIN_STATE__RECORD)
		{
			f__ligth_OFF_LED__GREEN__READY();
		}
	}
	//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

	if(u8_sys_usbHID__MAIN_STATE==def_u8_sys_usbHID__MAIN_STATE__READY)
	{
		if(u16_sys_usbHID__time_down_counter_1==0)
		{
			u16_sys_usbHID__time_down_counter_1=1000;
			//every one second at ready state:
		}
	}
	else if(u8_sys_usbHID__MAIN_STATE==def_u8_sys_usbHID__MAIN_STATE__RECORD)
	{

		if(u8_sys_usbHID__SUB_STATE==def_u8_sys_usbHID__SUB_STATE_of_RECORD__w_TRIGGER_4IO)
		{
			u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD++;
			//[[[[[[[[[[[[[[[[[[[[[[[
			//trigger out:

				if(u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD==u16_sys_usbHID__in_ms_TIME_OF_OUT_1_ON)
				{
					HAL_GPIO_WritePin(IDC_C_1_GPIO_Port, IDC_C_1_Pin, GPIO_PIN_SET);
				}
				if(u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD==u16_sys_usbHID__in_ms_TIME_OF_OUT_1_OFF)
				{
					HAL_GPIO_WritePin(IDC_C_1_GPIO_Port, IDC_C_1_Pin, GPIO_PIN_RESET);
				}

				if(u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD==u16_sys_usbHID__in_ms_TIME_OF_OUT_2_ON)
				{
					HAL_GPIO_WritePin(IDC_C_2_GPIO_Port, IDC_C_2_Pin, GPIO_PIN_SET);
				}
				if(u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD==u16_sys_usbHID__in_ms_TIME_OF_OUT_2_OFF)
				{
					HAL_GPIO_WritePin(IDC_C_2_GPIO_Port, IDC_C_2_Pin, GPIO_PIN_RESET);
				}

				if(u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD==u16_sys_usbHID__in_ms_TIME_OF_OUT_3_ON)
				{
					HAL_GPIO_WritePin(IDC_C_3_GPIO_Port, IDC_C_3_Pin, GPIO_PIN_SET);
				}
				if(u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD==u16_sys_usbHID__in_ms_TIME_OF_OUT_3_OFF)
				{
					HAL_GPIO_WritePin(IDC_C_3_GPIO_Port, IDC_C_3_Pin, GPIO_PIN_RESET);
				}

				if(u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD==u16_sys_usbHID__in_ms_TIME_OF_OUT_4_ON)
				{
					HAL_GPIO_WritePin(IDC_C_4_GPIO_Port, IDC_C_4_Pin, GPIO_PIN_SET);
				}
				if(u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD==u16_sys_usbHID__in_ms_TIME_OF_OUT_4_OFF)
				{
					HAL_GPIO_WritePin(IDC_C_4_GPIO_Port, IDC_C_4_Pin, GPIO_PIN_RESET);
				}
			//]]]]]]]]]]]]]]]]]]]]]]]

			//[[[[[[[[[[[[[[[[[[[[[[[
			//sampling start:
				if(u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD==u16_sys_usbHID__in_ms_TIME_OF_RECORD_START)
				{
					f__start_record_with_TIMER_ADC_DMA();
				}
			//]]]]]]]]]]]]]]]]]]]]]]]
		}
		else if(u8_sys_usbHID__SUB_STATE==def_u8_sys_usbHID__SUB_STATE_of_RECORD__w_TRIGGER_1IO)
		{
			u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD++;
			//[[[[[[[[[[[[[[[[[[[[[[[
			//trigger out:

				if(u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD==u16_sys_usbHID__in_ms_TIME_OF_OUT_1_ON)
				{
					HAL_GPIO_WritePin(IDC_C_1_GPIO_Port, IDC_C_1_Pin, GPIO_PIN_SET);
				}
				if(u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD==u16_sys_usbHID__in_ms_TIME_OF_OUT_1_OFF)
				{
					HAL_GPIO_WritePin(IDC_C_1_GPIO_Port, IDC_C_1_Pin, GPIO_PIN_RESET);
				}

				if(u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD==u16_sys_usbHID__in_ms_TIME_OF_OUT_2_ON)
				{
					HAL_GPIO_WritePin(IDC_C_1_GPIO_Port, IDC_C_1_Pin, GPIO_PIN_SET);
				}
				if(u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD==u16_sys_usbHID__in_ms_TIME_OF_OUT_2_OFF)
				{
					HAL_GPIO_WritePin(IDC_C_1_GPIO_Port, IDC_C_1_Pin, GPIO_PIN_RESET);
				}

				if(u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD==u16_sys_usbHID__in_ms_TIME_OF_OUT_3_ON)
				{
					HAL_GPIO_WritePin(IDC_C_1_GPIO_Port, IDC_C_1_Pin, GPIO_PIN_SET);
				}
				if(u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD==u16_sys_usbHID__in_ms_TIME_OF_OUT_3_OFF)
				{
					HAL_GPIO_WritePin(IDC_C_1_GPIO_Port, IDC_C_1_Pin, GPIO_PIN_RESET);
				}

				if(u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD==u16_sys_usbHID__in_ms_TIME_OF_OUT_4_ON)
				{
					HAL_GPIO_WritePin(IDC_C_1_GPIO_Port, IDC_C_1_Pin, GPIO_PIN_SET);
				}
				if(u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD==u16_sys_usbHID__in_ms_TIME_OF_OUT_4_OFF)
				{
					HAL_GPIO_WritePin(IDC_C_1_GPIO_Port, IDC_C_1_Pin, GPIO_PIN_RESET);
				}
			//]]]]]]]]]]]]]]]]]]]]]]]

			//[[[[[[[[[[[[[[[[[[[[[[[
			//sampling start:
				if(u16_sys_usbHID__in_ms_TIME_UP_COUNTER_OF_RECORD==u16_sys_usbHID__in_ms_TIME_OF_RECORD_START)
				{
					f__start_record_with_TIMER_ADC_DMA();		//called once !!! because of incremented time counter!!!
				}
			//]]]]]]]]]]]]]]]]]]]]]]]
		}
		else if(u8_sys_usbHID__SUB_STATE==def_u8_sys_usbHID__SUB_STATE_of_RECORD__w_waiting_input_1_RISE)
		{
			if(HAL_GPIO_ReadPin(IDC_A_2_GPIO_Port, IDC_A_2_Pin) == GPIO_PIN_SET)
			{
				f__start_record_with_TIMER_ADC_DMA();
				u8_sys_usbHID__SUB_STATE=def_u8_sys_usbHID__SUB_STATE_of_RECORD__w_waiting_input_1_RISE_started;
			}
			else if(u16_sys_usbHID__time_down_counter_2==0)
			{
				u8_sys_usbHID__MAIN_STATE_NEXT=def_u8_sys_usbHID__MAIN_STATE__WAIT_AFTER_FAIL;
				u16_sys_usbHID__time_down_counter_2=3000;
			}
		}
		else if(u8_sys_usbHID__SUB_STATE==def_u8_sys_usbHID__SUB_STATE_of_RECORD__w_waiting_input_1_FALL)
		{
			if(HAL_GPIO_ReadPin(IDC_A_2_GPIO_Port, IDC_A_2_Pin) == GPIO_PIN_RESET)
			{
				f__start_record_with_TIMER_ADC_DMA();
				u8_sys_usbHID__SUB_STATE=def_u8_sys_usbHID__SUB_STATE_of_RECORD__w_waiting_input_1_FALL_started;
			}
			else if(u16_sys_usbHID__time_down_counter_2==0)
			{
				u8_sys_usbHID__MAIN_STATE_NEXT=def_u8_sys_usbHID__MAIN_STATE__WAIT_AFTER_FAIL;
				u16_sys_usbHID__time_down_counter_2=3000;
			}
		}
	}	//	end of "else if(u8_sys_usbHID__MAIN_STATE==def_u8_sys_usbHID__MAIN_STATE__RECORD)"
	else //if(u8_sys_usbHID__MAIN_STATE==def_u8_sys_usbHID__MAIN_STATE__WAIT_AFTER_FAIL)
	{
		if(u16_sys_usbHID__time_down_counter_2==0)
		{
			u8_sys_usbHID__MAIN_STATE_NEXT=def_u8_sys_usbHID__MAIN_STATE__READY;
		}
	}

}

//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
void	f__startup_IO_tests(void)
{
	//	HAL_GPIO_WritePin(IDC_C_1_GPIO_Port, IDC_C_1_Pin, GPIO_PIN_SET);
	//	HAL_GPIO_WritePin(IDC_C_2_GPIO_Port, IDC_C_2_Pin, GPIO_PIN_SET);
	//	HAL_GPIO_WritePin(IDC_C_3_GPIO_Port, IDC_C_3_Pin, GPIO_PIN_SET);
	//	HAL_GPIO_WritePin(IDC_C_4_GPIO_Port, IDC_C_4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(IDC_C_5_GPIO_Port, IDC_C_5_Pin, GPIO_PIN_SET);
	//	HAL_GPIO_WritePin(IDC_C_6_GPIO_Port, IDC_C_6_Pin, GPIO_PIN_SET);
	//	HAL_GPIO_WritePin(IDC_C_7_GPIO_Port, IDC_C_7_Pin, GPIO_PIN_SET);
	//	HAL_GPIO_WritePin(IDC_C_8_GPIO_Port, IDC_C_8_Pin, GPIO_PIN_SET);

		HAL_Delay(300);

	//	HAL_GPIO_WritePin(IDC_C_1_GPIO_Port, IDC_C_1_Pin, GPIO_PIN_RESET);
	//	HAL_GPIO_WritePin(IDC_C_2_GPIO_Port, IDC_C_2_Pin, GPIO_PIN_RESET);
	//	HAL_GPIO_WritePin(IDC_C_3_GPIO_Port, IDC_C_3_Pin, GPIO_PIN_RESET);
	//	HAL_GPIO_WritePin(IDC_C_4_GPIO_Port, IDC_C_4_Pin, GPIO_PIN_RESET);
	//	HAL_GPIO_WritePin(IDC_C_5_GPIO_Port, IDC_C_5_Pin, GPIO_PIN_RESET);
	//	HAL_GPIO_WritePin(IDC_C_6_GPIO_Port, IDC_C_6_Pin, GPIO_PIN_RESET);
		//HAL_GPIO_WritePin(IDC_C_7_GPIO_Port, IDC_C_7_Pin, GPIO_PIN_RESET);
		//HAL_GPIO_WritePin(IDC_C_8_GPIO_Port, IDC_C_8_Pin, GPIO_PIN_RESET);


		//port A test
	//	f_GPIO_Init__set__IDC_A_as_full_output();
	//
	//	HAL_GPIO_WritePin(IDC_A_1_GPIO_Port, IDC_A_1_Pin, GPIO_PIN_SET);
	//	HAL_GPIO_WritePin(IDC_A_1_GPIO_Port, IDC_A_1_Pin, GPIO_PIN_RESET);
	//
	//	HAL_GPIO_WritePin(IDC_A_2_GPIO_Port, IDC_A_2_Pin, GPIO_PIN_SET);
	//	HAL_GPIO_WritePin(IDC_A_2_GPIO_Port, IDC_A_2_Pin, GPIO_PIN_RESET);
	//
	//	HAL_GPIO_WritePin(IDC_A_3_GPIO_Port, IDC_A_3_Pin, GPIO_PIN_SET);
	//	HAL_GPIO_WritePin(IDC_A_3_GPIO_Port, IDC_A_3_Pin, GPIO_PIN_RESET);
	//
	//	HAL_GPIO_WritePin(IDC_A_4_GPIO_Port, IDC_A_4_Pin, GPIO_PIN_SET);
	//	HAL_GPIO_WritePin(IDC_A_4_GPIO_Port, IDC_A_4_Pin, GPIO_PIN_RESET);
	//
	//	HAL_GPIO_WritePin(IDC_A_5_GPIO_Port, IDC_A_5_Pin, GPIO_PIN_SET);
	//	HAL_GPIO_WritePin(IDC_A_5_GPIO_Port, IDC_A_5_Pin, GPIO_PIN_RESET);
	//
	//	HAL_GPIO_WritePin(IDC_A_6_GPIO_Port, IDC_A_6_Pin, GPIO_PIN_SET);
	//	HAL_GPIO_WritePin(IDC_A_6_GPIO_Port, IDC_A_6_Pin, GPIO_PIN_RESET);
	//
	//	HAL_GPIO_WritePin(IDC_A_7_GPIO_Port, IDC_A_7_Pin, GPIO_PIN_SET);
	//	HAL_GPIO_WritePin(IDC_A_7_GPIO_Port, IDC_A_7_Pin, GPIO_PIN_RESET);
	//
	//	HAL_GPIO_WritePin(IDC_A_8_GPIO_Port, IDC_A_8_Pin, GPIO_PIN_SET);
	//	HAL_GPIO_WritePin(IDC_A_8_GPIO_Port, IDC_A_8_Pin, GPIO_PIN_RESET);
}
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
void	f__1ms_base_function_test(void)
{

  if(u8_one_shot_forced_function_test_flag==1)
  {
	  u8_one_shot_forced_function_test_flag=0;

	  //[[[[[[[[[[[[[[[[[[[[[[[[[[[[
		u8_array_sys_usbHID__RX[0]=(u8)def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__START_DMA_RECORD_w_PARAMETERS;
		u8_array_sys_usbHID__RX[1]=(u8)(def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__START_DMA_RECORD_w_PARAMETERS>>8);

		u16_sys_usbHID__COMMAND_TMP_1=100;
		u8_array_sys_usbHID__RX[2]=u16_sys_usbHID__COMMAND_TMP_1;
		u16_sys_usbHID__COMMAND_TMP_1>>=8;
		u8_array_sys_usbHID__RX[3]=u16_sys_usbHID__COMMAND_TMP_1;

		USB_HID_QUERY_HANDLE();
	  //]]]]]]]]]]]]]]]]]]]]]]]]]]]]

  }

}
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
u16 u16_led_blink_control_counter=0;
void	f__1ms_base_led_blink_control(void)
{
	u16_led_blink_control_counter++;

	  if(u16_led_blink_control_counter>999)
	  {
		  u16_led_blink_control_counter=0;
	  }

		//[[[[[[[[[[[[[[[[[[[[[[[[[[[[
		if(u16_led_blink_control_counter==0)
		{
		  HAL_GPIO_WritePin(OUT_ex_JTDO__LED_BLUE_GPIO_Port, OUT_ex_JTDO__LED_BLUE_Pin, GPIO_PIN_SET);

			if(u8_sys_usbHID__MAIN_STATE==def_u8_sys_usbHID__MAIN_STATE__READY)
			{
				f__ligth_ON_LED__GREEN__READY();
			}
			else if(u8_sys_usbHID__MAIN_STATE==def_u8_sys_usbHID__MAIN_STATE__RECORD)
			{
				f__ligth_ON_LED__RED__RECORD();
			}
		}
		else if(u16_led_blink_control_counter==10)
		{
			HAL_GPIO_WritePin(OUT_ex_JTDO__LED_BLUE_GPIO_Port, OUT_ex_JTDO__LED_BLUE_Pin, GPIO_PIN_RESET);
		}
		else if(u16_led_blink_control_counter==200)
		{
			HAL_GPIO_WritePin(OUT_ex_JTDO__LED_BLUE_GPIO_Port, OUT_ex_JTDO__LED_BLUE_Pin, GPIO_PIN_SET);
		}
		else if(u16_led_blink_control_counter==210)
		{
			HAL_GPIO_WritePin(OUT_ex_JTDO__LED_BLUE_GPIO_Port, OUT_ex_JTDO__LED_BLUE_Pin, GPIO_PIN_RESET);
		}
		else if(u16_led_blink_control_counter==500)
		{
			if(u8_sys_usbHID__MAIN_STATE==def_u8_sys_usbHID__MAIN_STATE__READY)
			{
				f__ligth_OFF_LED__GREEN__READY();
			}
			else if(u8_sys_usbHID__MAIN_STATE==def_u8_sys_usbHID__MAIN_STATE__RECORD)
			{
				f__ligth_OFF_LED__RED__RECORD();
			}
		}
		//]]]]]]]]]]]]]]]]]]]]]]]]]]]]

}
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_DMA_Init();
  MX_USB_DEVICE_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_TIM4_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

	//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
	//startup hw init
	HAL_Delay(300);
	HAL_GPIO_WritePin(OUT__USB_DISCONNECT_GPIO_Port, OUT__USB_DISCONNECT_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(OUT_ex_JTDI__LED_RED_GPIO_Port, OUT_ex_JTDI__LED_RED_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(OUT_ex_JTDO__LED_BLUE_GPIO_Port, OUT_ex_JTDO__LED_BLUE_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(OUT_exNJTRST__LED_GREEN_GPIO_Port, OUT_exNJTRST__LED_GREEN_Pin, GPIO_PIN_SET);

	f_sys_usbHID__SCOPE__CLEAN__U32_DMA_BUFFER();

	HAL_TIM_OC_Start_IT(&htim4, TIM_CHANNEL_4); 	//1ms time base source.

	f_GPIO_Init__set__IDC_C_as_full_output();
	f_GPIO_Init__set__IDC_A_as_full_input_pulled_up();

	f__startup_IO_tests();

	HAL_Delay(300);
	//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

	  //[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
	  if(u1_flag_SYSTICK_1ms==1)
	  {
		  u1_flag_SYSTICK_1ms=0;
		  f_SYSTICK__prepare_time_flags_at_out_of_INTERRUPT();

		  //1ms base tasks:
		  //{{{{{{{{{{{{{{{{{{{{{{{{{{{{
		  f__1ms_base_main_state_machine();
		  f__1ms_base_function_test();
		  f__1ms_base_led_blink_control();
		  //}}}}}}}}}}}}}}}}}}}}}}}}}}}}

	  }	//end of "if(u1_flag_SYSTICK_1ms==1)"
	  //]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

	  //[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
	  if(u1_flag_SYSTICK_10ms==1)
	  {
		  u1_flag_SYSTICK_10ms=0;

		  //10ms base tasks:
		  //{{{{{{{{{{{{{{{{{{{{{{{{{{{{

		  //}}}}}}}}}}}}}}}}}}}}}}}}}}}}
	  }
	  //]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

	  //[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
	  if(u1_flag_SYSTICK_100ms==1)
	  {
		  u1_flag_SYSTICK_100ms=0;

		  //100ms base tasks:
		  //{{{{{{{{{{{{{{{{{{{{{{{{{{{{

		  //}}}}}}}}}}}}}}}}}}}}}}}}}}}}
	  }
	  //]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

	  //[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
	  if(u1_flag_SYSTICK_1000ms==1)
	  {
		  u1_flag_SYSTICK_1000ms=0;

		  //1sec base tasks:
		  //{{{{{{{{{{{{{{{{{{{{{{{{{{{{

		  //}}}}}}}}}}}}}}}}}}}}}}}}}}}}
	  }
	  //]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

  }	//end of "while (1)"
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC|RCC_PERIPHCLK_USB;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

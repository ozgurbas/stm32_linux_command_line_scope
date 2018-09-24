/*
 * adc_hw_init_tests.c
 *
 *  Created on: Jul 26, 2018
 *      Author: ozgurbas
 */


void	adc__timer_trigger_dma_hw_init_test(void)
{

	  //{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{
	  //adc tests:

	  	  //[[[[[[[[[[[[[[
	      //test 1:
	  	  //HAL_ADC_Start_IT(&hadc1);		//HAL_ADC_ConvCpltCallback e sokuyor bir kez!!! continuous enable degilken!!!
	  	  //]]]]]]]]]]]]]]

	  	  //[[[[[[[[[[[[[[
	      //test 2:
	  	  //HAL_ADC_Start_IT(&hadc1);		//HAL_ADC_ConvCpltCallback e sokuyor sonsuz kez!!! continuous enable iken!!!
	  	  //]]]]]]]]]]]]]]

		  //[[[[[[[[[[[[[[
	  	  //test 3:
	  	  //HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length)
	  	  //HAL_ADC_Start_DMA(&hdma_adc1, (uint32_t*)(u32_array_ADC_1_2_DMA_COPY), 300);		>>> hw fault!!!
		  //]]]]]]]]]]]]]]

	//	  //[[[[[[[[[[[[[[
	//	  //test 3:
	//	  //HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length)
	//	  //HAL_ADC_Start_DMA(	(ADC_HandleTypeDef*)(&hdma_adc1), (uint32_t*)(u32_array_ADC_1_2_DMA_COPY), 300);	//hw fault verir cunku "ADC_HandleTypeDef" istiyor, "DMA_HandleTypeDef" gonderiyorum!!!
	//	  HAL_ADC_Start_DMA(	(ADC_HandleTypeDef*)(&hadc1), (uint32_t*)(u32_array_ADC_1_2_DMA_COPY), 300);
	//	  HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_4); //adc de trigger tim4 ch 4 secili degilken girmedi interrupta, seciliykende girmedi ,mode: active level on match, ch polarity: polarity low
	//	  //HAL_TIM_OC_Start_IT(&htim4, TIM_CHANNEL_4);
	//
	//	  //]]]]]]]]]]]]]]

		  //[[[[[[[[[[[[[[
		  //test 3:



		  //HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length)
		  //HAL_ADC_Start_DMA(	(ADC_HandleTypeDef*)(&hdma_adc1), (uint32_t*)(u32_array_ADC_1_2_DMA_COPY), 300);	//hw fault verir cunku "ADC_HandleTypeDef" istiyor, "DMA_HandleTypeDef" gonderiyorum!!!
	//	  HAL_ADC_Start_DMA(	(ADC_HandleTypeDef*)(&hadc1), (uint32_t*)(u32_array_ADC_1_2_DMA_COPY), 300);
		  //HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_4); //usttekine gore sadece "mode: toggle on match, ch polarity: polarity low" yapıldı. yine sonuc yok
		  //HAL_TIM_OC_Start_IT(&htim4, TIM_CHANNEL_4); //interrupt cube den enable olunca calisiyor, ama adc tetiklemiyor, cube de trigger out secildi reset de idi, OC4 e alındı, sonuc yok!!!

		  //HAL_ADC_Start_IT(&hadc1);
		  HAL_ADC_Start_DMA(	(ADC_HandleTypeDef*)(&hadc1), (uint32_t*)(u32_array_ADC_1_2_DMA_COPY), 300);
		  HAL_ADC_Start((ADC_HandleTypeDef*)(&hadc2));

		  HAL_TIM_OC_Start_IT(&htim4, TIM_CHANNEL_4); //su anda led blink icin calisiyor!!!


		  //HAL_TIM_Base_Start(&htim3); 			//"HAL_ADC_Start_IT" ile tetikliyor
		  HAL_TIM_Base_Start_IT(&htim3); 		//"HAL_ADC_Start_IT" ile tetikliyor //interruptlı test icin gereken bu fonksiyon, cube dede interrupt enable yapılmalı


	//	  eski yazılımları inceleme:
	//
	//	  "f_sys_adc_set_8_channel_for_dma_record"
	//	  da
	//
	//	    ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;    >>> suan da aynı secili
	//	    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	//	    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	//	  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; >>> demekki adc nin zamanlaması kullanılmis!!! iki adc de aynı atarlanmis
	//
	//
	//	  "f_sys_adc_set_tim4_for_auto_trigger" da ise:
	//	  tim4 cc1 kullanılmıs, interrupttan olsa gerek.
	//	  evet "TIM4_IRQHandler" icinde "ADC_SoftwareStartInjectedConvCmd" lar var.
	//
	//
	//	  dunyanın en iyi yazılımı da "ADC_ExternalTrigConv_None" kullanılmıs.





	//	  ONEMLI:
	//	  adc external trigger conversion sources da
	//	  * software
	//	  * timerların capture compare leri
	//	  ve
	//	  * timer 3 un trigger out event
	//	  i var.
	//
	//	  trigger out event secildi!!!
	//
	//	  timer 3 de sadece clock source internal secildi,
	//	  sonra prescaler 76 ve arr 1000 secildi.
	//	  timer 3 TRGO parameters de "trigger event selection" "update event olarak secildi.




	//	  su anda adc1 ve 2 de ikiser regular kanal ayarlı,
	//	  external trgiger sources lar : timer 3 trigger out event secili,
	//	  scan mode enable,
	//	  continuous ve discontinuous disable,
	//	  son yapılan degisiklik ise,
	//	  adc mode u independent a almak, daha once "dual regular simultaneous mode" seciliydi.
	//	  ve dma fonlsiyonu 400 luk arrayn 300 unu doldurmus,
	//
	//	  "dual regular simultaneous mode" a geri alındı test icin.
	// ONEMLI !!!!!!!!! evet, cevap calismiyor dual modda!!! independent de OK!!!
	//geri independent e alındı sadece(adc 2 trigger secimi resetlendi, yeniden secildi sadece) ve
	//"HAL_ADC_ConvCpltCallback" e bir kez girdi, dma 300 transferi yapınca!!! yani interrupt ı ??? su anda dma da adc interrupt da acik!!!
	//sonraki testler independent modda olucak!!!
	//ilk test adc ornegi tetiklemesi scande 2 ser dort kanal conversion mu calisiyor tek tekmi calisiyor?
	//yeni her timer tetiginde 1 dma transferi mi yoksa ikimi oluyor?
	//bunun icin adc int kapatılıcak.
	//timer 3 in acilacak, 10 kez sayıcak. arraye bakılacak kac doldurulmus diye. dma fonksiyonu yine 300 e ayarlı kalabilir.
	//timer3 interrupt acildi, adc 1 2 interrupt kapatıldı.


	//
	//
	//		u16_interrupt_tim3_counter++;
	//		if(u16_interrupt_tim3_counter>20)
	//		{
	//			HAL_ADC_Stop_DMA((ADC_HandleTypeDef*)(&hadc1));
	//			u16_interrupt_tim3_counter=0;
	//		}
	//
	//de break point de
	//
	//u32_array_ADC_1_2_DMA_COPY[0]	uint32_t	4092
	//u32_array_ADC_1_2_DMA_COPY[1]	uint32_t	0
	//u32_array_ADC_1_2_DMA_COPY[2]	uint32_t	4093
	//u32_array_ADC_1_2_DMA_COPY[3]	uint32_t	0
	//u32_array_ADC_1_2_DMA_COPY[4]	uint32_t	4091
	//u32_array_ADC_1_2_DMA_COPY[5]	uint32_t	0
	//u32_array_ADC_1_2_DMA_COPY[6]	uint32_t	4092
	//u32_array_ADC_1_2_DMA_COPY[7]	uint32_t	183
	//u32_array_ADC_1_2_DMA_COPY[8]	uint32_t	4093
	//u32_array_ADC_1_2_DMA_COPY[9]	uint32_t	645
	//u32_array_ADC_1_2_DMA_COPY[10]	uint32_t	4092
	//u32_array_ADC_1_2_DMA_COPY[11]	uint32_t	1051
	//u32_array_ADC_1_2_DMA_COPY[12]	uint32_t	4092
	//u32_array_ADC_1_2_DMA_COPY[13]	uint32_t	1333
	//u32_array_ADC_1_2_DMA_COPY[14]	uint32_t	4091
	//u32_array_ADC_1_2_DMA_COPY[15]	uint32_t	1403
	//u32_array_ADC_1_2_DMA_COPY[16]	uint32_t	4092
	//u32_array_ADC_1_2_DMA_COPY[17]	uint32_t	1276
	//u32_array_ADC_1_2_DMA_COPY[18]	uint32_t	4091
	//u32_array_ADC_1_2_DMA_COPY[19]	uint32_t	837
	//u32_array_ADC_1_2_DMA_COPY[20]	uint32_t	4091
	//u32_array_ADC_1_2_DMA_COPY[21]	uint32_t	260
	//u32_array_ADC_1_2_DMA_COPY[22]	uint32_t	4091
	//u32_array_ADC_1_2_DMA_COPY[23]	uint32_t	0
	//u32_array_ADC_1_2_DMA_COPY[24]	uint32_t	4092
	//u32_array_ADC_1_2_DMA_COPY[25]	uint32_t	0
	//u32_array_ADC_1_2_DMA_COPY[26]	uint32_t	4091
	//u32_array_ADC_1_2_DMA_COPY[27]	uint32_t	0
	//u32_array_ADC_1_2_DMA_COPY[28]	uint32_t	4092
	//u32_array_ADC_1_2_DMA_COPY[29]	uint32_t	0
	//u32_array_ADC_1_2_DMA_COPY[30]	uint32_t	4092
	//u32_array_ADC_1_2_DMA_COPY[31]	uint32_t	0
	//u32_array_ADC_1_2_DMA_COPY[32]	uint32_t	4092
	//u32_array_ADC_1_2_DMA_COPY[33]	uint32_t	0
	//u32_array_ADC_1_2_DMA_COPY[34]	uint32_t	4092
	//u32_array_ADC_1_2_DMA_COPY[35]	uint32_t	0
	//u32_array_ADC_1_2_DMA_COPY[36]	uint32_t	4092
	//u32_array_ADC_1_2_DMA_COPY[37]	uint32_t	0
	//u32_array_ADC_1_2_DMA_COPY[38]	uint32_t	4092
	//u32_array_ADC_1_2_DMA_COPY[39]	uint32_t	0
	//u32_array_ADC_1_2_DMA_COPY[40]	uint32_t	0
	//
	//geldi,
	//IDC pin 1 e sinus yarım dalga veriliyor,
	//diğer 3 u kısadevre ve 3.3 de,
	//neden 4092,
	//hımm ad2 acilmadı!!!
	//
	//	  HAL_ADC_Start_DMA(	(ADC_HandleTypeDef*)(&hadc1), (uint32_t*)(u32_array_ADC_1_2_DMA_COPY), 300);
	//	  HAL_ADC_Start((ADC_HandleTypeDef*)(&hadc2));
	//
	//hadc2 satırıda eklendi!!!
	//
	//
	//u32_array_ADC_1_2_DMA_COPY	uint32_t [400]	0x20000238 <u32_array_ADC_1_2_DMA_COPY>
	//	[0...99]	uint32_t [100]	0x20000238 <u32_array_ADC_1_2_DMA_COPY>
	//		u32_array_ADC_1_2_DMA_COPY[0]	uint32_t	268308478
	//		u32_array_ADC_1_2_DMA_COPY[1]	uint32_t	268304384
	//		u32_array_ADC_1_2_DMA_COPY[2]	uint32_t	268308476
	//		u32_array_ADC_1_2_DMA_COPY[3]	uint32_t	268238848
	//		u32_array_ADC_1_2_DMA_COPY[4]	uint32_t	268177404
	//		u32_array_ADC_1_2_DMA_COPY[5]	uint32_t	268173312
	//		u32_array_ADC_1_2_DMA_COPY[6]	uint32_t	268242939
	//		u32_array_ADC_1_2_DMA_COPY[7]	uint32_t	268173312
	//		u32_array_ADC_1_2_DMA_COPY[8]	uint32_t	268242940
	//
	//halini aldı,
	//sinus okunamaz oldu!!!
	//if(u16_interrupt_tim3_counter>60)
	//icin
	//u32_array_ADC_1_2_DMA_COPY[118]	uint32_t	268242940
	//u32_array_ADC_1_2_DMA_COPY[119]	uint32_t	0
	//u32_array_ADC_1_2_DMA_COPY[120]	uint32_t	0
	//
	//119 adet doldurmus!!!
	//
	//simdi, 2,3,4 kanalları gnd ye!!!
	//adcler ters olmus!!! pin sırasında 2,1,4,3. cube de degistir rank i!!!
	//
	//IDC1 3.3, digerleri gnd
	//u32_array_ADC_1_2_DMA_COPY	uint32_t [400]	0x20000238 <u32_array_ADC_1_2_DMA_COPY>
	//	[0...99]	uint32_t [100]	0x20000238 <u32_array_ADC_1_2_DMA_COPY>
	//		u32_array_ADC_1_2_DMA_COPY[0]	uint32_t	4095
	//		u32_array_ADC_1_2_DMA_COPY[1]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[2]	uint32_t	4094
	//		u32_array_ADC_1_2_DMA_COPY[3]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[4]	uint32_t	4094
	//		u32_array_ADC_1_2_DMA_COPY[5]	uint32_t	0
	//
	//IDC2 3.3, digerleri gnd
	//u32_array_ADC_1_2_DMA_COPY	uint32_t [400]	0x20000238 <u32_array_ADC_1_2_DMA_COPY>
	//	[0...99]	uint32_t [100]	0x20000238 <u32_array_ADC_1_2_DMA_COPY>
	//		u32_array_ADC_1_2_DMA_COPY[0]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[1]	uint32_t	4095
	//		u32_array_ADC_1_2_DMA_COPY[2]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[3]	uint32_t	4094
	//		u32_array_ADC_1_2_DMA_COPY[4]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[5]	uint32_t	4093
	//
	//IDC3 3.3
	//u32_array_ADC_1_2_DMA_COPY	uint32_t [400]	0x20000238 <u32_array_ADC_1_2_DMA_COPY>
	//	[0...99]	uint32_t [100]	0x20000238 <u32_array_ADC_1_2_DMA_COPY>
	//		u32_array_ADC_1_2_DMA_COPY[0]	uint32_t	268304384
	//		u32_array_ADC_1_2_DMA_COPY[1]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[2]	uint32_t	268238848
	//		u32_array_ADC_1_2_DMA_COPY[3]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[4]	uint32_t	268238848	     >>> Hex:0xffd0000
	//		u32_array_ADC_1_2_DMA_COPY[5]	uint32_t	0
	//
	//IDC4 3.3
	//u32_array_ADC_1_2_DMA_COPY	uint32_t [400]	0x20000238 <u32_array_ADC_1_2_DMA_COPY>
	//	[0...99]	uint32_t [100]	0x20000238 <u32_array_ADC_1_2_DMA_COPY>
	//		u32_array_ADC_1_2_DMA_COPY[0]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[1]	uint32_t	268304384
	//		u32_array_ADC_1_2_DMA_COPY[2]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[3]	uint32_t	268238848
	//		u32_array_ADC_1_2_DMA_COPY[4]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[5]	uint32_t	268238848
	//		u32_array_ADC_1_2_DMA_COPY[6]	uint32_t	0
	//
	//
	//miss gibi,
	//bu gosteriyorki her timer tetigi, 4 kanal olutuyor!!! dma iki ilerliyor!!!
	//
	//simdi periyot dogrulama
	//
	//u32_array_ADC_1_2_DMA_COPY	uint32_t [400]	0x20000238 <u32_array_ADC_1_2_DMA_COPY>
	//	[0...99]	uint32_t [100]	0x20000238 <u32_array_ADC_1_2_DMA_COPY>
	//		u32_array_ADC_1_2_DMA_COPY[0]	uint32_t	517
	//		u32_array_ADC_1_2_DMA_COPY[1]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[2]	uint32_t	946
	//		u32_array_ADC_1_2_DMA_COPY[3]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[4]	uint32_t	1259
	//		u32_array_ADC_1_2_DMA_COPY[5]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[6]	uint32_t	1399
	//		u32_array_ADC_1_2_DMA_COPY[7]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[8]	uint32_t	1365
	//		u32_array_ADC_1_2_DMA_COPY[9]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[10]	uint32_t	994
	//		u32_array_ADC_1_2_DMA_COPY[11]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[12]	uint32_t	430
	//		u32_array_ADC_1_2_DMA_COPY[13]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[14]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[15]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[16]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[17]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[18]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[19]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[20]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[21]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[22]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[23]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[24]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[25]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[26]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[27]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[28]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[29]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[30]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[31]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[32]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[33]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[34]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[35]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[36]	uint32_t	188
	//		u32_array_ADC_1_2_DMA_COPY[37]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[38]	uint32_t	647
	//		u32_array_ADC_1_2_DMA_COPY[39]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[40]	uint32_t	1055
	//		u32_array_ADC_1_2_DMA_COPY[41]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[42]	uint32_t	1325
	//		u32_array_ADC_1_2_DMA_COPY[43]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[44]	uint32_t	1406
	//		u32_array_ADC_1_2_DMA_COPY[45]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[46]	uint32_t	1271
	//		u32_array_ADC_1_2_DMA_COPY[47]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[48]	uint32_t	827
	//		u32_array_ADC_1_2_DMA_COPY[49]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[50]	uint32_t	254
	//		u32_array_ADC_1_2_DMA_COPY[51]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[52]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[53]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[54]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[55]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[56]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[57]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[58]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[59]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[60]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[61]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[62]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[63]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[64]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[65]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[66]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[67]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[68]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[69]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[70]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[71]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[72]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[73]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[74]	uint32_t	345
	//		u32_array_ADC_1_2_DMA_COPY[75]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[76]	uint32_t	776
	//		u32_array_ADC_1_2_DMA_COPY[77]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[78]	uint32_t	1153
	//		u32_array_ADC_1_2_DMA_COPY[79]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[80]	uint32_t	1376
	//		u32_array_ADC_1_2_DMA_COPY[81]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[82]	uint32_t	1399
	//		u32_array_ADC_1_2_DMA_COPY[83]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[84]	uint32_t	1158
	//		u32_array_ADC_1_2_DMA_COPY[85]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[86]	uint32_t	654
	//		u32_array_ADC_1_2_DMA_COPY[87]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[88]	uint32_t	74
	//		u32_array_ADC_1_2_DMA_COPY[89]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[90]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[91]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[92]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[93]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[94]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[95]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[96]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[97]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[98]	uint32_t	0
	//		u32_array_ADC_1_2_DMA_COPY[99]	uint32_t	0
	//
	//42 ile 82 iki tepe arası,
	//yani ornek aralıgı tam 40 tane 32 bit, /2 20 ms, = 50 hz :)
	//mutlu son!!!
	//
	//sıra usb_hid_cmd lere geldi.

		  //bu haliyle "timer3_adc12_dma__TEST_OK_REFERENCE" yedegi al

		  //]]]]]]]]]]]]]]

	  //}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}

}


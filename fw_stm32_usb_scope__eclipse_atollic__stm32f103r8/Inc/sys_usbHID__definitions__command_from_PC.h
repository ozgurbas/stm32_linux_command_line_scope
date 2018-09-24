/*
 * sys_usbHID__definitions__command_from_PC.h
 *
 *  Created on: Jul 27, 2018
 *      Author: ozgurbas
 */

#ifndef SYS_USBHID__DEFINITIONS__COMMAND_FROM_PC_H_
#define SYS_USBHID__DEFINITIONS__COMMAND_FROM_PC_H_


	#define		def_u16_sys_usbHID__COMMAND_from_PC__NOP									0
	#define		def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__CLEAN_REGISTERS					1
	#define		def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__START_DMA_RECORD_w_PARAMETERS	2
	#define		def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__GET_STATES						3
	#define		def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__GET_INDEXED_RECORD_DATA			4
	#define		def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__START_DMA_RECORD_w_TRIGGER_IO	5



					//parametre yerleri fix olacak!!! kullanılmasa bile reserve kalıcak!!!
					//parametre 0: COMMAND =
					//parametre 1: sample interval in us
					//parametre 2: trigger mode
						//0 ise direkt yakalama		>>> onceki ile ayni,  "def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__START_DMA_RECORD_w_PARAMETERS" deki.
						//1 ise adc watchdog lu tetikleme (adc int teikleyecek) 	>>> adc bekler
						//2 ise dijital input tetikleme		>>> input bekler, output vermez.
						//3 ise digital output tetikleme	>>> (pc den komutla surec baslar) zamanlarda negatif varsa bunları bekler, yani kayıtı maximum - zaman kadar sonra baslatir
								//baska deyisle disarida bir olay tetikleyip sayac sıfır oldugunda kayıt baslatır, kayit ilerlerken bir sayac degerine ulasilirsa ilgili cikis verilir
								//bu durumda 4 cikistan ilkine kayittan 100 ms once cikis verilmesi icin -100 verilir,
								//diger cikislar 100, 200 ve 300 ise, kayıt basladiktan 100, 200 ve 300 ms sonralarında ilgili cikislar verilecektir.
								//yani 4 adet zamanlamanın icinde kayıt istenilen yerde baslatilabilir.
								//toplam zamanlamayi negatiften kurtarmak da mumkun, 5. parametre olarak ornek baslama zamanı verilebilir.
								//bu daha iyi, 5 parametre olucak, ms cinsinden hepsi!!!
								//maximum 10000 olucak, 10 sn max!!!
								//0-10000 arasi kimin sirasi geldiyse onula ilgili islem yapilir.
								//daha anlasilir!!!
						//4 ise mode 1 ve ardindan mode 3 calisir, yani adc tetiklenmesi beklenip outputlu kayit yapilir.		>>> acil degil, komplex is, gerektiginde yapilacak
						//5 ise mode 2 ve ardindan mode 3 calisir, yani input tetiklemesi beklenip outputlu kayit yapilir.		>>> acil degil, komplex is, gerektiginde yapilacak
						//6 ise digital output tetikleme, fakat tek cikisli, ardisik sinyal icin.
					//parametre 3: "adc watchdog lu tetikleme" parametresi  REZERVE.
								//ilk iki bit hangi kanal, sonraki iki bit rise fall secimi, son 12 bit adc degeri
					//parametre 4: "dijital input tetikleme" parametresi  REZERVE.
								//input kanallari icin andlenicekmi or lanicakmi vs.

					//time parameters of trigger mode 3: output triggering	( 0 to 10000 in ms)
					//[[[[[[[[[[[[[[[[[
						//parameter 5: start of record
						//parameter 6: output 1 ON tıme
						//parameter 7: output 2 ON tıme
						//parameter 8: output 3 ON tıme
						//parameter 9: output 4 ON tıme

						//parameter 10: output 1 OFF tıme
						//parameter 11: output 2 OFF tıme
						//parameter 12: output 3 OFF tıme
						//parameter 13: output 4 OFF tıme
					//]]]]]]]]]]]]]]]]]

	#define		def_u16_sys_usbHID__SCOPE__P2_TRIGGER_MODE__direct					0
	#define		def_u16_sys_usbHID__SCOPE__P2_TRIGGER_MODE__4_output				3
	#define		def_u16_sys_usbHID__SCOPE__P2_TRIGGER_MODE__1_output				6
	#define		def_u16_sys_usbHID__SCOPE__P2_TRIGGER_MODE__w_waiting_input_1_RISE	7
	#define		def_u16_sys_usbHID__SCOPE__P2_TRIGGER_MODE__w_waiting_input_1_FALL	8

#endif /* SYS_USBHID__DEFINITIONS__COMMAND_FROM_PC_H_ */

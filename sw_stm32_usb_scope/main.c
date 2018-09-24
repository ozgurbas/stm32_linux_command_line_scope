/* COPYRIGHT --
 * This file is part of libhid, a user-space HID access library.
 * libhid is (c) 2003-2005
 *   Martin F. Krafft <libhid@pobox.madduck.net>
 *   Charles Lepple <clepple@ghz.cc>
 *   Arnaud Quette <arnaud.quette@free.fr> && <arnaud.quette@mgeups.com>
 * and distributed under the terms of the GNU General Public License.
 * See the file ./COPYING in the source distribution for more information.
 *
 * THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES
 * OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * note: edited by ozgur bas to use with stm32 usb hid scope.
 */

#include <hid.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 	/* for getopt() */
#include <stdlib.h>

# include "gnuplot_i.h"

#include	"sys_usbHID__definitions__command_from_PC.h"
#include	"sys_usbHID__definitions__state.h"

#define 	def_u8_YES			1
#define 	def_u8_NO			0
#define 	def_u8_UNKNOWN		255

#define 	def_max_number_of_samples			1900

#define def_u8_USB_HID_LENGTH  		64

dpoint gnu_plot_i__double_xy_data_points[def_max_number_of_samples];
gnuplot_ctrl *ptr_to_gnu_plot_i__ctrl_1;

//typedef uint32_t  u32;
//typedef uint16_t u16;
//typedef uint8_t  u8;

//@ linux:
typedef __uint32_t  u32;
typedef __uint16_t u16;
typedef __uint8_t  u8;

char char_from_scanf=0;

u8		u8_tmp_1;
u8		u8_tmp_2;
u8		u8_tmp_3;

u16		u16_tmp_1;
u16		u16_tmp_2;
u16		u16_tmp_3;
u16		u16_tmp_4;
u16		u16_tmp_5;

u32		u32_tmp_1;
u32		u32_tmp_2;
u32		u32_tmp_3;

//terminal interface parameters:
u8		u8_terminal_interface_status;
char 	string__terminal__line_in[1000];
u16		u16__terminal__line_in_size=0;
char 	string__terminal__command__test[]="exit";


unsigned char u8_array_sys_usbHID__RX[def_u8_USB_HID_LENGTH];
unsigned char u8_array_sys_usbHID__TX[def_u8_USB_HID_LENGTH];

int i,i_190, j, k, p;


HIDInterface* hid;
int iface_num = 0;
hid_return ret;

//Bus 002 Device 005: ID 0483:5750 STMicroelectronics
unsigned short vendor_id  = 0x0483;
unsigned short product_id = 0x5750;
char *vendor, *product;

int flag;

u16		u16_array__ADC_channel_1[10000];
u16		u16_array__ADC_channel_2[10000];
u16		u16_array__ADC_channel_3[10000];
u16		u16_array__ADC_channel_4[10000];


void	clean_hid_tx_array(void)
{
	  for (i = 0; i < def_u8_USB_HID_LENGTH; i++)
	  {
		  u8_array_sys_usbHID__TX[i] = 0;
	  }
}

void	clean_hid_rx_array(void)
{
	  for (i = 0; i < def_u8_USB_HID_LENGTH; i++)
	  {
		  u8_array_sys_usbHID__RX[i] = 0;
	  }
}

 
bool match_serial_number(struct usb_dev_handle* usbdev, void* custom, unsigned int len)
{
  bool ret;
  char* buffer = (char*)malloc(len);
  usb_get_string_simple(usbdev, usb_device(usbdev)->descriptor.iSerialNumber,
      buffer, len);
  ret = strncmp(buffer, (char*)custom, len) == 0;
  free(buffer);
  return ret;
}

void	f__hid_write_Rx_and_read_to_RX(void)
{
	  ret = hid_interrupt_write(hid, 0x81, u8_array_sys_usbHID__TX, def_u8_USB_HID_LENGTH, 1000);
	  if (ret != HID_RET_SUCCESS)
	  {
		  printf("hid_interrupt_write failed with code %d\n", ret);
		  //return 1;
	  }

	  clean_hid_rx_array();
	  ret = hid_interrupt_read(hid, 0x1, u8_array_sys_usbHID__RX, def_u8_USB_HID_LENGTH, 1000);
	  if (ret != HID_RET_SUCCESS)
	  {
		  printf("hid_interrupt_read failed with code %d\n", ret);
		  //return 1;
	  }
}


void	f__insert_u16_hid_command_to_TX_array(u16 u16_f_in_COMMAND)
{
	u16 u16_tmp_1_in_f;
	  u16_tmp_1_in_f=u16_f_in_COMMAND;
	  u8_array_sys_usbHID__TX[0]=(u8)u16_tmp_1_in_f;
	  u16_tmp_1_in_f>>=8;
	  u8_array_sys_usbHID__TX[1]=(u8)u16_tmp_1_in_f;
}

void	f__insert_u16_hid_parameter_1_to_TX_array(u16 u16_f_in_COMMAND)
{
	u16 u16_tmp_1_in_f;
	  u16_tmp_1_in_f=u16_f_in_COMMAND;
	  u8_array_sys_usbHID__TX[2]=(u8)u16_tmp_1_in_f;
	  u16_tmp_1_in_f>>=8;
	  u8_array_sys_usbHID__TX[3]=(u8)u16_tmp_1_in_f;
}

u16		f_u16__return_hid_command_from_RX_array(void)
{
		u16 u16_tmp_1_in_f;
		u16_tmp_1_in_f=u8_array_sys_usbHID__RX[1];
		u16_tmp_1_in_f<<=8;
		u16_tmp_1_in_f+=u8_array_sys_usbHID__RX[0];
		return u16_tmp_1_in_f;
}

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

void	f_echo_test(void)
{

	  for (i = 0; i < def_u8_USB_HID_LENGTH; i++)
	  {
		  u8_array_sys_usbHID__TX[i] = i;// * i;
		  //printf("%d ", buf[i]);
	  }

	  //echo command:
	  u8_array_sys_usbHID__TX[0]='E';
	  u8_array_sys_usbHID__TX[1]='C';
	  u8_array_sys_usbHID__TX[2]='H';

	  for (i = 3; i < def_u8_USB_HID_LENGTH; i++)
	  {
		  u8_array_sys_usbHID__TX[i]=i;
	  }

	  printf("txbuf: ");
	  for (i = 0; i < def_u8_USB_HID_LENGTH; i++) {
	      printf("%d ", u8_array_sys_usbHID__TX[i]);
	  }
	  printf("\n");

	  //receive & send 3 packets.
	  for (p = 0; p < 3; p++)
	  {

		  sleep(1);

	      //write
	      //{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{
	      printf("send: ");
	      for (i = 0; i < def_u8_USB_HID_LENGTH; i++) {
	      printf("%d ", u8_array_sys_usbHID__TX[i]);
	      }
	      printf("\n");
	      ret = hid_interrupt_write(hid, 0x81, u8_array_sys_usbHID__TX, def_u8_USB_HID_LENGTH, 1000);
	      if (ret != HID_RET_SUCCESS) {
	      fprintf(stderr, "hid_interrupt_write failed with code %d\n", ret);
	      }
	      //}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}

	      //read
	      //{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{
	      ret = hid_interrupt_read(hid, 0x1, u8_array_sys_usbHID__RX, def_u8_USB_HID_LENGTH, 1000);
	      if (ret == HID_RET_SUCCESS) {
	      printf("recv: ");
	      for (i = 0; i < def_u8_USB_HID_LENGTH; i++) {
	          printf("%d ", u8_array_sys_usbHID__RX[i]);
	      }
	      printf ("\n");
	      } else {
	      fprintf(stderr, "hid_interrupt_read failed with code %d\n", ret);
	      }
	      //}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}

	      for (i = 3; i < def_u8_USB_HID_LENGTH; i++)
	      {
	    	  u8_array_sys_usbHID__TX[i]=i+p+1;
	      }

	  }
}


void f_redraw_gnuplot(void)
{
	char     str_channel_no_and_name[100] ;
	double x_[def_max_number_of_samples];
	double y_[def_max_number_of_samples];

	u_int32_t ch,i,j,u32_start,u32_end,u32_length;// i,j;

	gnuplot_resetplot(ptr_to_gnu_plot_i__ctrl_1);
	//gnuplot_setstyle(ptr_to_gnu_plot_i__ctrl_1, "points");
	gnuplot_setstyle(ptr_to_gnu_plot_i__ctrl_1, "lines");

	u32_end=1900;
	u32_start=0;

	if(u32_start>=u32_end)
	{
		return;
	}

	u32_length=u32_end-u32_start;

	i=0;
	for(j=u32_start;j<u32_end;j++)
	{
		//gnu_plot_i__double_xy_data_points[i].x=j;
		x_[i]=j;  //Warning: empty x range [0:0], adjusting to [-1:1]
		//x_[i]=i; 	//Warning: empty x range [0:0], adjusting to [-1:1]
		i++;
	}

	gnuplot_cmd(ptr_to_gnu_plot_i__ctrl_1, "set grid ytics lt 0 lw 1 lc rgb \"#bbbbbb\"");
	gnuplot_cmd(ptr_to_gnu_plot_i__ctrl_1, "set grid xtics lt 0 lw 1 lc rgb \"#bbbbbb\"");

#if defined eski_calisan_gnplot
	for(ch=0;ch<struct_record_header_and_view_preferences__active.u8_number_of_channels;ch++)
	{
			i=0;
			for(j=u32_start;j<u32_end;j++)
			{
				//gnu_plot_i__double_xy_data_points[i].y=float_dual_array_RECORD_SAMPLES__l_16X100K[j][ch];

				if(u8_flag_array__channel_draw_enable[ch]==1)
				{
					y_[i]=float_dual_array_RECORD_SAMPLES__l_16X100K[j][ch];
				}
				else
				{
					//renklerin sırası degismesin diye boyle yapıldı, enable olmayan sıfır olarak ciziliyor!!!
					y_[i]=0;
				}

				i++;
			}

			sprintf ( str_channel_no_and_name, "%d:%s", (ch+1),struct_record_header_and_view_preferences__active.char_array__channel_names_l16x6[ch] );

			//gnuplot_plot1d_var2(ptr_to_gnu_plot_i__ctrl_1, gnu_plot_i__double_xy_data_points, u32_length, "ch1");
			//x ekseni hep sıfırdan basliyor, bug var!!!

			gnuplot_plot1d_var2v(ptr_to_gnu_plot_i__ctrl_1, x_, y_, u32_length, str_channel_no_and_name);  //CALISTI !!!
			//bu hic basmıyor duzgun,>>> i++; yapmamisim!!!
	}
#else
	//yerine

	//CH 1
	i=0;
	for(j=u32_start;j<u32_end;j++)
	{
		y_[i]=u16_array__ADC_channel_1[j];
		i++;
	}
	sprintf ( str_channel_no_and_name, "%d:%s", 1,"ch1" );
	gnuplot_plot1d_var2v(ptr_to_gnu_plot_i__ctrl_1, x_, y_, u32_length, str_channel_no_and_name);

	//CH 2
	i=0;
	for(j=u32_start;j<u32_end;j++)
	{
		y_[i]=u16_array__ADC_channel_2[j];
		i++;
	}
	sprintf ( str_channel_no_and_name, "%d:%s", 2,"ch2" );
	gnuplot_plot1d_var2v(ptr_to_gnu_plot_i__ctrl_1, x_, y_, u32_length, str_channel_no_and_name);

	//CH 3
	i=0;
	for(j=u32_start;j<u32_end;j++)
	{
		y_[i]=u16_array__ADC_channel_3[j];
		i++;
	}
	sprintf ( str_channel_no_and_name, "%d:%s", 3,"ch3" );
	gnuplot_plot1d_var2v(ptr_to_gnu_plot_i__ctrl_1, x_, y_, u32_length, str_channel_no_and_name);

	//CH 4
	i=0;
	for(j=u32_start;j<u32_end;j++)
	{
		y_[i]=u16_array__ADC_channel_4[j];
		i++;
	}
	sprintf ( str_channel_no_and_name, "%d:%s", 4,"ch4" );
	gnuplot_plot1d_var2v(ptr_to_gnu_plot_i__ctrl_1, x_, y_, u32_length, str_channel_no_and_name);

#endif

}

u8		f__u8_is_device_in_ready_state(void)
{
	u8	u8_f_out_return_value=0;
	  clean_hid_tx_array();
	  f__insert_u16_hid_command_to_TX_array(def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__GET_STATES);
	  f__hid_write_Rx_and_read_to_RX();

	  if(	f_u16__return_hid_command_from_RX_array()==def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__GET_STATES)
	  {
		  if(u8_array_sys_usbHID__RX[2]==def_u8_sys_usbHID__MAIN_STATE__READY)
		  {
			  u8_f_out_return_value=def_u8_YES;
		  }
		  else
		  {
			  u8_f_out_return_value=def_u8_NO;
		  }
	  }
	  else
	  {
		  u8_f_out_return_value=def_u8_UNKNOWN;
	  }

	  return u8_f_out_return_value;
}

void	f__transfer_record_array_to_pc(void)
{
	  //her 60 lık pakette 32bit DMA arrayde index 20 ilerler
	  //3800 u32 arrayde /20=190 paket istenmesi gerekir, index ise her seferinde 20 ilerletilir
	  u16_tmp_1=0;
	  u16_tmp_2=0;
	  for (i_190 = 0; i_190 < 190; i_190++)
	  {
		  u16_tmp_1=i_190*10;
		  clean_hid_tx_array();
		  f__insert_u16_hid_command_to_TX_array(def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__GET_INDEXED_RECORD_DATA);
		  f__insert_u16_hid_parameter_1_to_TX_array(u16_tmp_1);
		  f__hid_write_Rx_and_read_to_RX();

		  if(	f_u16__return_hid_command_from_RX_array()!=def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__GET_INDEXED_RECORD_DATA)
		  {
			  //command echo means accepted!!!
			  printf("unexpected protocol response\n");
			  //f__close_usb_hid_and_terminate_program(); todo test icin kapatıldı, acilacak!!!!!!!!
		  }
		  else
		  {
			  //unzip 60 byte 4 channel ADC data to PC ram arrays:
			  //arrayde her ornek 6 byte, 1.5 byte ilerlenerek alınacak!!!
			  //u16_tmp_1 dma arrayde 10 10 ilerler, 190 kez,
			  //u16_tmp_2 de ise x10 + buradaki index yuruyecek!!!

			  //dikkat yukarıda command eko kontrol edildi, index de eko oluyor ama kontrole gerek duyulmadı.
			  //index mcu sorgusuz DMA arrayi ardisik gonderirse kullanılacak.

			  u16_tmp_2=u16_tmp_1;
			  u16_tmp_3=4;	//usb pakette data baslangic index.
			  for (j = 0; j < 10; j++)
			  {
				  //6 byte= 4 * 1.5 byte ayıklama!!!

				  //            ^ ^
				  //0x0000 0000 0fff
				  u16_tmp_4=u8_array_sys_usbHID__RX[u16_tmp_3];
				  u16_tmp_5=u8_array_sys_usbHID__RX[u16_tmp_3+1];
				  u16_tmp_5&=0x000f;
				  u16_tmp_5<<=8;	//sag 8 bit dolu, yanina gelecek sola dogru.
				  u16_tmp_4+=u16_tmp_5;
				  u16_array__ADC_channel_1[u16_tmp_2]=u16_tmp_4;

				  //         ^  ^
				  //0x0000 00ff f000
				  u16_tmp_3++;
				  u16_tmp_4=u8_array_sys_usbHID__RX[u16_tmp_3];
				  u16_tmp_4>>=4;
				  u16_tmp_5=u8_array_sys_usbHID__RX[u16_tmp_3+1];
				  u16_tmp_5<<=4;	//sag 4 bit dolu, yanina gelecek sola dogru.
				  u16_tmp_4+=u16_tmp_5;
				  u16_array__ADC_channel_2[u16_tmp_2]=u16_tmp_4;

				  //    ^  ^
				  //0x000f ff00 0000
				  u16_tmp_3++;
				  u16_tmp_3++;	//!!! son 3 byte icin iki ilerler
				  u16_tmp_4=u8_array_sys_usbHID__RX[u16_tmp_3];
				  u16_tmp_5=u8_array_sys_usbHID__RX[u16_tmp_3+1];
				  u16_tmp_5&=0x000f;
				  u16_tmp_5<<=8;	//sag 4 bit dolu, yanina gelecek sola dogru.
				  u16_tmp_4+=u16_tmp_5;
				  u16_array__ADC_channel_3[u16_tmp_2]=u16_tmp_4;

				  //  ^ ^
				  //0xfff0 0000 0000
				  u16_tmp_3++;
				  u16_tmp_4=u8_array_sys_usbHID__RX[u16_tmp_3];
				  u16_tmp_4>>=4;
				  u16_tmp_5=u8_array_sys_usbHID__RX[u16_tmp_3+1];
				  u16_tmp_5<<=4;	//sag 4 bit dolu, yanina gelecek sola dogru.
				  u16_tmp_4+=u16_tmp_5;
				  u16_array__ADC_channel_4[u16_tmp_2]=u16_tmp_4;

				  u16_tmp_3++;
				  u16_tmp_3++;	//bir sonraki icin iki ilerler.

				  u16_tmp_2++;
			  }
		  }

		  //sonraki 10 ornek!!!

	  }

	  printf("adc record data transfered from mcu to pc!!!\n");
}

void	f__run_direct_or_input_waiting_record(
		u16 u16_f_in__command,
		u16 u16_f_in__trigger_mode,
		u16 u16_f_in__sample_interval,
		u16 u16_f_in__estimated_record_time_in_sec,
		u16 u16_f_in__time_out_in_sec)
{

	u8	u8_sleep_timeout_counter;

	u8	u8_temp_1;
	u8_temp_1=f__u8_is_device_in_ready_state();

	if(u8_temp_1==def_u8_YES)
	{
		printf("record will be started...\n");
	}
	else if(u8_temp_1==def_u8_NO)
	{
		printf("device is not in expected state, program will be terminated.\n");
	}
	else //if(u8_temp_1==def_u8_UNKNOWN)
	{
		printf("bad device response, program will be terminated.\n");
	}

	  clean_hid_tx_array();
	  f__insert_indexed_u16_hid_parameter_to_TX_array(0, u16_f_in__command);				//>>> p0
	  f__insert_indexed_u16_hid_parameter_to_TX_array(1, u16_f_in__sample_interval);		//>>> p1
	  f__insert_indexed_u16_hid_parameter_to_TX_array(2, u16_f_in__trigger_mode);			//>>> p2
	  f__insert_indexed_u16_hid_parameter_to_TX_array(3, u16_f_in__time_out_in_sec);		//>>> p2

	  f__hid_write_Rx_and_read_to_RX();

	  if(	f_u16__return_hid_command_from_RX_array()!=u16_f_in__command)	//def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__START_DMA_RECORD_w_PARAMETERS)
	  {
		  //command echo means accepted!!!
		  printf("unexpected protocol response\n");
		  return;
	  }

	  //>>> record started!!!

	  if(u16_f_in__command==def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__START_DMA_RECORD_w_PARAMETERS)
	  {
		  sleep(u16_f_in__estimated_record_time_in_sec);
	  }
	  else if(u16_f_in__command==def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__START_DMA_RECORD_w_TRIGGER_IO)
	  {
		  //u16_f_in__time_out_in_sec 	>>> 1 to 10
		  u8_sleep_timeout_counter=u16_f_in__time_out_in_sec;

		  sleep(1);

		  while(u8_sleep_timeout_counter>0)
		  {
			  u8_sleep_timeout_counter--;

			  clean_hid_tx_array();
			  f__insert_u16_hid_command_to_TX_array(def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__GET_STATES);
			  f__hid_write_Rx_and_read_to_RX();

			  if(	f_u16__return_hid_command_from_RX_array()==def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__GET_STATES)
			  {
				  if(
						  (u8_array_sys_usbHID__RX[2]==def_u8_sys_usbHID__MAIN_STATE__RECORD) &&
						  	  (
						  			(u8_array_sys_usbHID__RX[3]==def_u8_sys_usbHID__SUB_STATE_of_RECORD__w_waiting_input_1_RISE) ||
									(u8_array_sys_usbHID__RX[3]==def_u8_sys_usbHID__SUB_STATE_of_RECORD__w_waiting_input_1_FALL)

						  	  )

					)
				  {
					  printf("waiting for trigger input edge. down counter=%d\n",u8_sleep_timeout_counter);
				  }
				  else if(
						  (u8_array_sys_usbHID__RX[2]==def_u8_sys_usbHID__MAIN_STATE__RECORD) &&
						  	  (
						  			(u8_array_sys_usbHID__RX[3]==def_u8_sys_usbHID__SUB_STATE_of_RECORD__w_waiting_input_1_RISE) ||
									(u8_array_sys_usbHID__RX[3]==def_u8_sys_usbHID__SUB_STATE_of_RECORD__w_waiting_input_1_FALL)

						  	  )

					)
				  {
					  printf("trigger received, record started.\n");
					  u8_sleep_timeout_counter=0;
				  }
				  else if(u8_array_sys_usbHID__RX[2]==def_u8_sys_usbHID__MAIN_STATE__READY)
				  {
					  //record triggered at ready signal level right away!!!
					  printf("trigger received, record started.\n");
					  u8_sleep_timeout_counter=0;
				  }
				  else if(u8_array_sys_usbHID__RX[2]==def_u8_sys_usbHID__MAIN_STATE__WAIT_AFTER_FAIL)
				  {
					  printf("trigger time out...\n");
					  return;
				  }
				  else
				  {
					  printf("unexpected state progress.\n");
					  return;
				  }

			  }
			  else
			  {
				  printf("unexpected protocol response.\n");
				  return;
			  }

			  sleep(1);

		  }		//end of "while(u8_sleep_timeout_counter>0)"

		  //after "printf("trigger received, record started.\n");"
		  sleep(u16_f_in__estimated_record_time_in_sec);

	  }

	  f__transfer_record_array_to_pc();
	  f_redraw_gnuplot();
//	  printf("\nPress Any Key to Exit\n");
//	  scanf("%c",&char_from_scanf);
}


void	f__run_direct_w_n_outputs(
		u16 u16_f_in__trigger_mode,
		u16 u16_f_in__sample_interval,
		u16 u16_f_in__estimated_record_time_in_sec,
		u16 u16_f_in__time_record_start,
		u16 u16_f_in__time_ON_out_1,
		u16 u16_f_in__time_ON_out_2,
		u16 u16_f_in__time_ON_out_3,
		u16 u16_f_in__time_ON_out_4,
		u16 u16_f_in__time_OFF_out_1,
		u16 u16_f_in__time_OFF_out_2,
		u16 u16_f_in__time_OFF_out_3,
		u16 u16_f_in__time_OFF_out_4
		)
{

	u8	u8_temp_1;
	u8_temp_1=f__u8_is_device_in_ready_state();

	if(u8_temp_1==def_u8_YES)
	{
		printf("record will be started...\n");
	}
	else if(u8_temp_1==def_u8_NO)
	{
		printf("device is not in expected state, program will be terminated.\n");
	}
	else //if(u8_temp_1==def_u8_UNKNOWN)
	{
		printf("bad device response, program will be terminated.\n");
	}

	  clean_hid_tx_array();

	  f__insert_indexed_u16_hid_parameter_to_TX_array(0, def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__START_DMA_RECORD_w_TRIGGER_IO);	//>>> p0
	  f__insert_indexed_u16_hid_parameter_to_TX_array(1, u16_f_in__sample_interval);													//>>> p1
	  f__insert_indexed_u16_hid_parameter_to_TX_array(2, u16_f_in__trigger_mode);														//>>> p2: trigger mode

	  //parameter 3: "adc watchdog lu tetikleme" parametresi  	RESERVED.
	  //parameter 4: "dijital input tetikleme" parametresi  	RESERVED.

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

		f__insert_indexed_u16_hid_parameter_to_TX_array(5, u16_f_in__time_record_start);
		f__insert_indexed_u16_hid_parameter_to_TX_array(6, u16_f_in__time_ON_out_1);
		f__insert_indexed_u16_hid_parameter_to_TX_array(7, u16_f_in__time_ON_out_2);
		f__insert_indexed_u16_hid_parameter_to_TX_array(8, u16_f_in__time_ON_out_3);
		f__insert_indexed_u16_hid_parameter_to_TX_array(9, u16_f_in__time_ON_out_4);
		f__insert_indexed_u16_hid_parameter_to_TX_array(10, u16_f_in__time_OFF_out_1);
		f__insert_indexed_u16_hid_parameter_to_TX_array(11, u16_f_in__time_OFF_out_2);
		f__insert_indexed_u16_hid_parameter_to_TX_array(12, u16_f_in__time_OFF_out_3);
		f__insert_indexed_u16_hid_parameter_to_TX_array(13, u16_f_in__time_OFF_out_4);
		//]]]]]]]]]]]]]]]]]

	  f__hid_write_Rx_and_read_to_RX();

	  if(	f_u16__return_hid_command_from_RX_array()!=def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__START_DMA_RECORD_w_TRIGGER_IO)
	  {
		  //command echo means accepted!!!
		  printf("unexpected protocol response\n");
		  return;
	  }

	  //>>> record started!!!

	  //todo: state cekip progress gosterilecek, simdilik 3 sn sleep!!!

	  u16_f_in__time_record_start/=1000; 	//converted to sec base
	  sleep(u16_f_in__estimated_record_time_in_sec+u16_f_in__time_record_start);

	  f__transfer_record_array_to_pc();
	  f_redraw_gnuplot();
//	  printf("\nPress Any Key to Exit\n");
//	  scanf("%c",&char_from_scanf);
}


FILE* 	ptr_bin_log_record__file_w = NULL;
char 	gchar_array__temp[200];

#define 	def_string__path_to_folder__BINARY_RECORDS			"/home/ozgurbas/out_bin/"
#define 	def_string__FILE_NAME_SUFFIX						"data_16bit_x_1900sample_x_4channel.bin"

void	f__write_signal_data_to_binary_file(void)
{

	strcpy( (char *)(gchar_array__temp), (char *) (def_string__path_to_folder__BINARY_RECORDS) );
	//strcat( (char *)(gchar_array__temp), (char *) (dt_format) );
	strcat( (char *)(gchar_array__temp), (char *) (def_string__FILE_NAME_SUFFIX) );

	//w = O_WRONLY | O_CREAT | O_TRUNC
	ptr_bin_log_record__file_w= fopen(gchar_array__temp,"w");

	if(ptr_bin_log_record__file_w==NULL)
	{
		printf("ERROR: file open failed for w mode for the path %s\n",gchar_array__temp);
	}
	else
	{
		fwrite(&u16_array__ADC_channel_1, 3800, 1, ptr_bin_log_record__file_w);
		fwrite(&u16_array__ADC_channel_2, 3800, 1, ptr_bin_log_record__file_w);
		fwrite(&u16_array__ADC_channel_3, 3800, 1, ptr_bin_log_record__file_w);
		fwrite(&u16_array__ADC_channel_4, 3800, 1, ptr_bin_log_record__file_w);
	}

	fclose(ptr_bin_log_record__file_w);
}

void	f__read_signal_data_from_binary_file(void)
{

	strcpy( (char *)(gchar_array__temp), (char *) (def_string__path_to_folder__BINARY_RECORDS) );
	//strcat( (char *)(gchar_array__temp), (char *) (dt_format) );
	strcat( (char *)(gchar_array__temp), (char *) (def_string__FILE_NAME_SUFFIX) );

	//w = O_WRONLY | O_CREAT | O_TRUNC
	ptr_bin_log_record__file_w= fopen(gchar_array__temp,"r");

	if(ptr_bin_log_record__file_w==NULL)
	{
		printf("ERROR: file open failed for r mode for the path %s\n",gchar_array__temp);
	}
	else
	{
		fread(&u16_array__ADC_channel_1, 3800, 1, ptr_bin_log_record__file_w);
		fread(&u16_array__ADC_channel_2, 3800, 1, ptr_bin_log_record__file_w);
		fread(&u16_array__ADC_channel_3, 3800, 1, ptr_bin_log_record__file_w);
		fread(&u16_array__ADC_channel_4, 3800, 1, ptr_bin_log_record__file_w);
	}

	fclose(ptr_bin_log_record__file_w);
}

void	f__command_line_interface(void)
{
	char *buffer = NULL;
	size_t len = 0;

	int	int_CLI__STATUS_RUN=1;

	printf("qt to Exit\n");
	printf(">>> waiting for command: \n");


	while(int_CLI__STATUS_RUN==1)
	{
		ssize_t read = getline(&buffer, &len, stdin);
		if(read!=-1)
		{

			if(strcmp(buffer,"qt\n")==0)
			{
				printf("program will terminate...\n");
				int_CLI__STATUS_RUN=0;
			}
			else if(strcmp(buffer,"echo\n")==0)
			{
				printf("echo test started...\n");
				f_echo_test();
				printf("echo test ended...\n");
				printf(">>> waiting for command: \n");
			}
			else if(strcmp(buffer,"out_bin\n")==0)
			{
				printf("out_bin started...\n");
				f__write_signal_data_to_binary_file();
				printf("out_bin ended...\n");

				printf(">>> waiting for command: \n");
			}
			else if(strcmp(buffer,"in_bin\n")==0)
			{
				printf("in_bin started...\n");
				f__read_signal_data_from_binary_file();
				printf("in_bin ended...\n");

				printf(">>> waiting for command: \n");
			}
			else if(strcmp(buffer,"out_pdf\n")==0)
			{
				printf("out_pdf started...\n");
				//...
				printf("out_pdf ended...\n");

				printf(">>> waiting for command: \n");
			}
			else if(strcmp(buffer,"draw\n")==0)
			{
				printf("draw started...\n");
				f_redraw_gnuplot();
				printf("draw ended...\n");

				printf(">>> waiting for command: \n");
			}
			else
			{
				printf(">>> waiting for command: \n");
			}
		}

	}

	printf("\n");

	free(buffer);
}


int main(int argc, char *argv[])
{
	//possible command examples: "000__sw_stm32_usb_scope__terminal_command__examples.txt"

	//@@@mark: 000: GNU_PLOT codes:
	//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
	//gnu_plot__pipe = popen("gnuplot -persist","w");
	ptr_to_gnu_plot_i__ctrl_1=gnuplot_init();

	  if ( ptr_to_gnu_plot_i__ctrl_1 == NULL )
	  {
	    printf ( "\n" );
	    printf ( "EXAMPLE - Fatal error!\n" );
	    printf ( "  GNUPLOT is not available in your path.\n" );
	    exit ( 1 );
	  }
	  //]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

 
  /* Parse command-line options.
   *
   * Currently, we only accept the "-d" flag, which works like "lsusb", and the
   * "-i" flag to select the interface (default 0). The syntax is one of the
   * following:
   * 
   * $ test_libhid -d 1234:
   * $ test_libhid -d :5678
   * $ test_libhid -d 1234:5678
   *
   * Product and vendor IDs are assumed to be in hexadecimal.
   *
   * TODO: error checking and reporting.
   */

//  while((flag = getopt(argc, argv, "d:i:")) != -1) {
//    switch (flag) {
//      case 'd':
//           product = optarg;
//           vendor = strsep(&product, ":");
//           if(vendor && *vendor) {
//               vendor_id = strtol(vendor, NULL, 16);
//           }
//           if(product && *product) {
//               product_id = strtol(product, NULL, 16);
//           }
//           break;
//      case 'i':
//           iface_num = atoi(optarg);
//           break;
//    }
//  }
 
  /* How to use a custom matcher function:
   * 
   * The third member of the HIDInterfaceMatcher is a function pointer, and
   * the forth member will be passed to it on invocation, together with the
   * USB device handle. The fifth member holds the length of the buffer
   * passed. See above. This can be used to do custom selection e.g. if you
   * have multiple identical devices which differ in the serial number.
   *
   *   char const* const serial = "01518";
   *   HIDInterfaceMatcher matcher = {
   *     0x06c2,                      // vendor ID
   *     0x0038,                      // product ID
   *     match_serial_number,         // custom matcher function pointer
   *     (void*)serial,               // custom matching data
   *     strlen(serial)+1             // length of custom data
   *   };
   *
   * If you do not want to use this, set the third member to NULL.
   * Then the match will only be on vendor and product ID.
   */
 
  // HIDInterfaceMatcher matcher = { 0x0925, 0x1237, NULL, NULL, 0 };
  HIDInterfaceMatcher matcher = { vendor_id, product_id, NULL, NULL, 0 };
 
  /* see include/debug.h for possible values */
  //hid_set_debug(HID_DEBUG_ALL);
  hid_set_debug_stream(stderr);
  /* passed directly to libusb */
  hid_set_usb_debug(0);
  
  ret = hid_init();
  if (ret != HID_RET_SUCCESS)
  {
    fprintf(stderr, "hid_init failed with return code %d\n", ret);
    return 1;
  }
 
  hid = hid_new_HIDInterface();
  if (hid == 0)
  {
    fprintf(stderr, "hid_new_HIDInterface() failed, out of memory?\n");
    return 1;
  }
 
  /* How to detach a device from the kernel HID driver:
   * 
   * The hid.o or usbhid.ko kernel modules claim a HID device on insertion,
   * usually. To be able to use it with libhid, you need to blacklist the
   * device (which requires a kernel recompilation), or simply tell libhid to
   * detach it for you. hid_open just opens the device, hid_force_open will
   * try n times to detach the device before failing.
   * In the following, n == 3.
   *
   * To open the HID, you need permission to the file in the /proc usbfs
   * (which must be mounted -- most distros do that by default):
   *   mount -t usbfs none /proc/bus/usb
   * You can use hotplug to automatically give permissions to the device on
   * connection. Please see
   *   http://cvs.ailab.ch/cgi-bin/viewcvs.cgi/external/libphidgets/hotplug/
   * for an example. Try NOT to work as root!
   */
 
  ret = hid_force_open(hid, iface_num, &matcher, 3);
  if (ret != HID_RET_SUCCESS)
  {
    fprintf(stderr, "hid_force_open failed with return code %d\n", ret);
    return 1;
  }
 
  ret = hid_write_identification(stdout, hid);
  if (ret != HID_RET_SUCCESS)
  {
    fprintf(stderr, "hid_write_identification failed with return code %d\n", ret);
    return 1;
  }
 
  ret = hid_dump_tree(stdout, hid);
  if (ret != HID_RET_SUCCESS)
  {
    fprintf(stderr, "hid_dump_tree failed with return code %d\n", ret);
    return 1;
  }
 
  /* How to write to and read from a device:
   *
   * The original code uses a HID usage path, whereas I use interrupt
   * endpoints, since that was what I could get working.
   * Feel free to take a look at the original code for the alternative
   * way of reading/writing:
   * http://anonscm.debian.org/viewvc/libhid/trunk/test/test_libhid.c?view=markup
   *
   *
   * My approach was to essentially execute
   * lsusb -vvv -d 1234:0006
   * where the last argument consists of <vendor ID>:<product ID>
   * Now, look under "Endpoint Descriptor:" for:
   *         bEndpointAddress     0x81  EP 1 IN
   *         bEndpointAddress     0x01  EP 1 OUT
   * if the hexadecimal values of yours are different to mine,
   * edit the 0x1 and 0x81 in hid_interrupt_read and _hid_interrupt_write,
   * respectively to match your values.
   *
   * The following API doc might be helpful:
   * http://libhid.alioth.debian.org/doc/hid_8h.html
   */

//  if(argc>1)
//  {
//	  printf(">>> argv[1]: %s \n",argv[1]);
//  }
//  if(argc>2)
//  {
//	  printf(">>> argv[2]: %s \n",argv[2]);
//  }
//  if(argc>3)
//  {
//	  printf(">>> argv[3]: %s \n",argv[3]);
//  }

  if( (argc==2) && (strcmp(argv[1],"cli")==0) )
  {
	  //f__command_line_interface();	//appended to the end of program!!!
  }
  else if( (argc==3) && (strcmp(argv[1],"direct")==0) )
  {
	  u16_tmp_1=strtoul(argv[2], NULL, 10);

	  //if(u16_tmp_1==0)
	  if(u16_tmp_1<20)		//adc interval 7 us x2 = 14 us min time
	  {
		  printf("\nbad parameter.");
	  }
	  else 	  if(u16_tmp_1>10000)	//max record time limit = 19 sec
	  {
		  printf("\nbad parameter.");
	  }
	  else
	  {
		  //TOD O: calculate record time to determine sleep time and send to function below!!!

		  u32_tmp_1=u16_tmp_1*1900;
		  u32_tmp_1/=1000; //in ms estimation of record time.
		  u32_tmp_1/=1000; //in sec estimation of record time.
		  u32_tmp_1++;
		  u16_tmp_2=u32_tmp_1;

		  //void	f__run_direct_or_input_waiting_record(u16 u16_f_in__command,u16 u16_f_in__trigger_mode,u16 u16_f_in__sample_interval, u16 u16_f_in__estimated_record_time_in_sec,u16 u16_f_in__time_out_in_sec)
		  f__run_direct_or_input_waiting_record(
				  def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__START_DMA_RECORD_w_PARAMETERS,	//direct capture will work!!!
				  def_u16_sys_usbHID__SCOPE__P2_TRIGGER_MODE__direct,u16_tmp_1,
				  u16_tmp_2,		//mode is redundant!!!
		  	  	  10);				//timeout is redundant!!!
	  }

  }
  else if( (argc==12) && ((strcmp(argv[1],"direct_w_4_outputs")==0) || (strcmp(argv[1],"direct_w_1_output")==0) ) )
  {
	  u16_tmp_1=strtoul(argv[2], NULL, 10);

	  // 1 record start time parameter.
	  // 4 on time parameter, 4 off time parameter,

	  //if(u16_tmp_1==0)
	  if(u16_tmp_1<20)		//adc interval 7 us x2 = 14 us min time
	  {
		  printf("\nbad parameter.");
	  }
	  else 	  if(u16_tmp_1>10000)	//max record time limit = 19 sec
	  {
		  printf("\nbad parameter.");
	  }
	  else
	  {
		  //TODO: calculate record time to determine sleep time and send to function below!!!


		  u32_tmp_1=u16_tmp_1*1900;
		  u32_tmp_1/=1000; //in ms estimation of record time.
		  u32_tmp_1/=1000; //in sec estimation of record time.
		  u32_tmp_1++;
		  u16_tmp_2=u32_tmp_1;


		  if(strcmp(argv[1],"direct_w_4_outputs")==0)
		  {
			  u16_tmp_3=def_u16_sys_usbHID__SCOPE__P2_TRIGGER_MODE__4_output;
		  }
		  else
		  {
			  u16_tmp_3=def_u16_sys_usbHID__SCOPE__P2_TRIGGER_MODE__1_output;
		  }


		  f__run_direct_w_n_outputs(
				  	  u16_tmp_3,					//u16 u16_f_in__trigger_mode,
				  	  u16_tmp_1,					//u16 u16_f_in__sample_interval,
					  u16_tmp_2,					//u16 u16_f_in__estimated_record_time_in_sec,
					  strtoul(argv[3], NULL, 10),	//u16 u16_f_in__time_record_start,
					  strtoul(argv[4], NULL, 10),	//u16 u16_f_in__time_ON_out_1,
					  strtoul(argv[5], NULL, 10),	//u16 u16_f_in__time_ON_out_2,
					  strtoul(argv[6], NULL, 10),	//u16 u16_f_in__time_ON_out_3,
					  strtoul(argv[7], NULL, 10),	//u16 u16_f_in__time_ON_out_4,
					  strtoul(argv[8], NULL, 10),	//u16 u16_f_in__time_OFF_out_1,
					  strtoul(argv[9], NULL, 10),	//u16 u16_f_in__time_OFF_out_2,
					  strtoul(argv[10], NULL, 10),	//u16 u16_f_in__time_OFF_out_3,
					  strtoul(argv[11], NULL, 10)	//u16 u16_f_in__time_OFF_out_4,
				  );
	  }
  }
  else if( (argc==4) && ( (strcmp(argv[1],"waiting_d_in_1_rise")==0) || (strcmp(argv[1],"waiting_d_in_1_fall")==0) ) )
  {
	  u16_tmp_1=strtoul(argv[2], NULL, 10);		//sample interval in micro sec
	  u16_tmp_3=strtoul(argv[3], NULL, 10);		//trigger timeout in sec, max 10, min 1


	  //if(u16_tmp_1==0)
	  if(u16_tmp_1<20)		//adc interval 7 us x2 = 14 us min time
	  {
		  printf("\nbad parameter.");
	  }
	  else 	  if(u16_tmp_1>10000)	//max record time limit = 19 sec
	  {
		  printf("\nbad parameter.");
	  }
	  else 	  if( (u16_tmp_3<1) || (u16_tmp_3>10) )
	  {
		  printf("\nbad parameter.");
	  }
	  else
	  {
		  //TOD O: calculate record time to determine sleep time and send to function below!!!

		  u32_tmp_1=u16_tmp_1*1900;
		  u32_tmp_1/=1000; //in ms estimation of record time.
		  u32_tmp_1/=1000; //in sec estimation of record time.
		  u32_tmp_1++;
		  u16_tmp_2=u32_tmp_1;


		  //void	f__run_direct_or_input_waiting_record(u16 u16_f_in__command,u16 u16_f_in__trigger_mode,u16 u16_f_in__sample_interval, u16 u16_f_in__estimated_record_time_in_sec,u16 u16_f_in__time_out_in_sec)
		  if(strcmp(argv[1],"waiting_d_in_1_rise")==0)
		  {
			  f__run_direct_or_input_waiting_record(
					  def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__START_DMA_RECORD_w_TRIGGER_IO,
					  def_u16_sys_usbHID__SCOPE__P2_TRIGGER_MODE__w_waiting_input_1_RISE,u16_tmp_1,u16_tmp_2,u16_tmp_3);
		  }
		  else
		  {
			  f__run_direct_or_input_waiting_record(
					  def_u16_sys_usbHID__COMMAND_from_PC__SCOPE__START_DMA_RECORD_w_TRIGGER_IO,
					  def_u16_sys_usbHID__SCOPE__P2_TRIGGER_MODE__w_waiting_input_1_FALL,u16_tmp_1,u16_tmp_2,u16_tmp_3);
		  }

	  }

  }
  else
  {
	  printf("\nUNDEFINED COMMAND AND ARGUMENT COMBINATION...");
  }


  //f_echo_test();

  //asking tasks before close, like save to bin, save to pdf, analyse signals etc.
  f__command_line_interface();

  //close
  ret = hid_close(hid);
  if (ret != HID_RET_SUCCESS) {
    fprintf(stderr, "hid_close failed with return code %d\n", ret);
    return 1;
  }

  hid_delete_HIDInterface(&hid);

  ret = hid_cleanup();
  if (ret != HID_RET_SUCCESS) {
    fprintf(stderr, "hid_cleanup failed with return code %d\n", ret);
    return 1;
  }

  return 0;
}
 

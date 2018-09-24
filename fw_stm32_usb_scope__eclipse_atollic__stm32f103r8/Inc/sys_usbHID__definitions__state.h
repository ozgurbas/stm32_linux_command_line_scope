/*
 * sys_usbHID__definitions__state.h
 *
 *  Created on: Jul 27, 2018
 *      Author: ozgurbas
 */

#ifndef SYS_USBHID__DEFINITIONS__STATE_H_
#define SYS_USBHID__DEFINITIONS__STATE_H_

#define		def_u8_sys_usbHID__MAIN_STATE__DEAD										0
#define		def_u8_sys_usbHID__MAIN_STATE__READY									200
#define		def_u8_sys_usbHID__MAIN_STATE__RECORD									201
#define		def_u8_sys_usbHID__MAIN_STATE__WAIT_AFTER_FAIL							250



#define		def_u8_sys_usbHID__SUB_STATE_of_RECORD__NOT_DEFINED						0
#define		def_u8_sys_usbHID__SUB_STATE_of_RECORD__w_TRIGGER_4IO					100
#define		def_u8_sys_usbHID__SUB_STATE_of_RECORD__w_TRIGGER_1IO					110
#define		def_u8_sys_usbHID__SUB_STATE_of_RECORD__w_waiting_input_1_RISE			120
#define		def_u8_sys_usbHID__SUB_STATE_of_RECORD__w_waiting_input_1_FALL			121
#define		def_u8_sys_usbHID__SUB_STATE_of_RECORD__w_waiting_input_1_RISE_started	122
#define		def_u8_sys_usbHID__SUB_STATE_of_RECORD__w_waiting_input_1_FALL_started	123

#endif /* SYS_USBHID__DEFINITIONS__STATE_H_ */

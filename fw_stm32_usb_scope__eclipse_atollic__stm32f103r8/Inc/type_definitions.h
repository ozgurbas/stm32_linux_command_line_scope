/*
 * type_definitions.h
 *
 *  Created on: Feb 1, 2017
 *      Author: ozgurbas
 */

#ifndef TYPE_DEFINITIONS_H_
#define TYPE_DEFINITIONS_H_

#define def_u8_SUCCESS   	0
#define def_u8_FAIL			1

#define	READY				1
#define WAIT				0

#define		def_u8__LOCKED			1
#define		def_u8__UNLOCKED		0

#define		def_u8__REFUSED			1
#define		def_u8__ACCEPTED		0

//#define FALSE		0
//#define TRUE		1

#define		def_u8__POSITIVE			0
#define		def_u8__NEGATIVE			1

#define		def_u8__f_return__OK		0
#define		def_u8__f_return__WAIT		1


#define  u8		uint8_t
#define  u16	uint16_t



typedef union
{
	uint8_t byte;

	struct B_X
	{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	} bits;


}  u8_byte;


typedef union
{
	uint8_t byte;

	struct C_X
	{
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	} bits;


}  u8_u1_union;

typedef union
{
	uint32_t u32;

	struct A
	{
		uint16_t u16_0;
		uint16_t u16_1;
	} u16;

	struct B
	{
		uint8_t u8_0;
		uint8_t u8_1;
		uint8_t u8_2;
		uint8_t u8_3;
	} u8;

	struct C
	{
		uint8_t u1_0:1;
		uint8_t u1_1:1;
		uint8_t u1_2:1;
		uint8_t u1_3:1;
		uint8_t u1_4:1;
		uint8_t u1_5:1;
		uint8_t u1_6:1;
		uint8_t u1_7:1;
		uint8_t u1_8:1;
		uint8_t u1_9:1;
		uint8_t u1_10:1;
		uint8_t u1_11:1;
		uint8_t u1_12:1;
		uint8_t u1_13:1;
		uint8_t u1_14:1;
		uint8_t u1_15:1;
		uint8_t u1_16:1;
		uint8_t u1_17:1;
		uint8_t u1_18:1;
		uint8_t u1_19:1;
		uint8_t u1_20:1;
		uint8_t u1_21:1;
		uint8_t u1_22:1;
		uint8_t u1_23:1;
		uint8_t u1_24:1;
		uint8_t u1_25:1;
		uint8_t u1_26:1;
		uint8_t u1_27:1;
		uint8_t u1_28:1;
		uint8_t u1_29:1;
		uint8_t u1_30:1;
		uint8_t u1_31:1;
	} u1;
}  u32_u16_u8_u1;


typedef union
{
	struct
	{
		u8 L;
		u8 H;
	} bytes;


	struct
	{
		u8 HiZ:1;
		u8 BUSY:1;
		u8 SW_F:1;
		u8 SW_EVN:1;
		u8 DIR:1;
		u8 MOT_STATUS_0:1;
		u8 MOT_STATUS_1:1;
		u8 NOTPERF_CMD:1;

		u8 WRONG_CMD:1;
		u8 UVLO:1;
		u8 TH_WRN:1;
		u8 TH_SD:1;
		u8 OCD:1;
		u8 x_2:1;
		u8 x_1:1;
		u8 SCK_MOD:1;  //msb
	} bits;


}  sys_ui_type_u16__L64_STATUS;






typedef struct
{
	uint8_t u1_0_ENABLE_BACKLASH:1;
	uint8_t u1_1_ENABLE_AUTO_BREAK_CONTROL:1;
	uint8_t u1_2_RELEASE_MOTOR_at_EMERGENCY_or_SW_STOP:1;
	uint8_t u1_3_KEEP_BREAK_HIGH_at_EMERGENCY_or_SW_STOP:1;
	uint8_t u1_4_ENABLE_REMOTE_INPUT_CONTROL_at_POINT_MODE:1;
	uint8_t u1_5:1;
	uint8_t u1_6:1;
	uint8_t u1_7:1;
} u8_u1_PREFERENCES_1;

typedef struct
{
	uint8_t u1_0:1;
	uint8_t u1_1:1;
	uint8_t u1_2:1;
	uint8_t u1_3:1;
	uint8_t u1_4:1;
	uint8_t u1_5:1;
	uint8_t u1_6:1;
	uint8_t u1_7:1;
} u8_u1_PREFERENCES_2;

typedef struct
{
	uint8_t u1_0:1;
	uint8_t u1_1:1;
	uint8_t u1_2:1;
	uint8_t u1_3:1;
	uint8_t u1_4:1;
	uint8_t u1_5:1;
	uint8_t u1_6:1;
	uint8_t u1_7:1;
} u8_u1_PREFERENCES_3;

typedef struct
{
	uint8_t u1_0:1;
	uint8_t u1_1:1;
	uint8_t u1_2:1;
	uint8_t u1_3:1;
	uint8_t u1_4:1;
	uint8_t u1_5:1;
	uint8_t u1_6:1;
	uint8_t u1_7:1;
} u8_u1_PREFERENCES_4;


typedef union
{
	uint32_t u32;

//#define	def_u8_INPUT_ACTION__NOP						0
//#define	def_u8_INPUT_ACTION__INCREMENT_INDEX			1
//#define	def_u8_INPUT_ACTION__DECREMENT_INDEX			2
//#define	def_u8_INPUT_ACTION__GO							3
//#define	def_u8_INPUT_ACTION__GOTO_START_INDEX_POS		4
//#define	def_u8_INPUT_ACTION__GOTO_END_INDEX_POS			5
//#define	def_u8_INPUT_ACTION__RESET_POS					6
//#define	def_u8_INPUT_ACTION__RUN_FORWARD				7
//#define	def_u8_INPUT_ACTION__RUN_REWERSE				8
//#define	def_u8_INPUT_ACTION__STOP						9
//#define	def_u8_INPUT_ACTION__STEP_FORWARD				10
//#define	def_u8_INPUT_ACTION__STEP_REWERSE				11

	struct
	{
		uint8_t u1_0__NOP:1;
		uint8_t u1_1__INCREMENT_INDEX:1;
		uint8_t u1_2__DECREMENT_INDEX:1;
		uint8_t u1_3__GO:1;
		uint8_t u1_4__GOTO_START_INDEX_POS:1;
		uint8_t u1_5__GOTO_END_INDEX_POS:1;
		uint8_t u1_6__RESET_POS:1;
		uint8_t u1_7__RUN_FORWARD:1;
		uint8_t u1_8__RUN_REWERSE:1;
		uint8_t u1_9__STOP:1;
		uint8_t u1_10__STEP_FORWARD:1;
		uint8_t u1_11__STEP_REWERSE:1;
		uint8_t u1_12__NOP:1;
		uint8_t u1_13__NOP:1;
		uint8_t u1_14__NOP:1;
		uint8_t u1_15__NOP:1;
		uint8_t u1_16__NOP:1;
		uint8_t u1_17__NOP:1;
		uint8_t u1_18__NOP:1;
		uint8_t u1_19__NOP:1;
		uint8_t u1_20__NOP:1;
		uint8_t u1_21__NOP:1;
		uint8_t u1_22__NOP:1;
		uint8_t u1_23__NOP:1;
		uint8_t u1_24__NOP:1;
		uint8_t u1_25__NOP:1;
		uint8_t u1_26__NOP:1;
		uint8_t u1_27__NOP:1;
		uint8_t u1_28__NOP:1;
		uint8_t u1_29__NOP:1;
		uint8_t u1_30__NOP:1;
		uint8_t u1_31__NOP:1;
	}bits;
} type_struct_u32_u1_sys_ui__IN_X_ACTIONS;

#endif /* TYPE_DEFINITIONS_H_ */

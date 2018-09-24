/*
 * sys_top_level_GLOBAL.h
 *
 *  Created on: Mar 7, 2016
 *      Author: ozgurbas
 */

#ifndef SYS_TOP_LEVEL_GLOBAL_H_
#define SYS_TOP_LEVEL_GLOBAL_H_


//#define def_u8_USB_HID_LENGTH  		32
#define def_u8_USB_HID_LENGTH  		64

#define def_u32_MCU_RAM_ORIGIN	0x20000000
#define def_u32_MCU_RAM_END		0x20002000

#define def_u8_DEVICE_ADDR_H	(u8)(0x05)
#define def_u8_DEVICE_ADDR_L	(u8)(0x55)



/*
 * bu ipne burada bi sürü hataya sebep oluyor
 * gidip stm32f0xx_spi.h de alakasız yerde hata verdiriyor???
 * İNCELE hatayı sonra aç!!!
 *
 *
//pA 765 mosi miso sck

// Communication boards SPIx Interface
#define SPIx                             SPI1
#define SPIx_CLK                         RCC_APB2Periph_SPI1
//#define SPIx_IRQn                        SPI1_IRQn
//#define SPIx_IRQHandler                  SPI1_IRQHandler

#define L64_RST_PIN                     GPIO_Pin_1
#define L64_RST_GPIO_PORT               GPIOB

#define SPIx_NSS_PIN                     GPIO_Pin_4
#define SPIx_NSS_GPIO_PORT               GPIOA

#define SPIx_SCK_PIN                     GPIO_Pin_5
#define SPIx_SCK_GPIO_PORT               GPIOA
#define SPIx_SCK_GPIO_CLK                RCC_AHBPeriph_GPIOA
#define SPIx_SCK_SOURCE                  GPIO_PinSource5
#define SPIx_SCK_AF                      GPIO_AF_0

#define SPIx_MISO_PIN                    GPIO_Pin_6
#define SPIx_MISO_GPIO_PORT              GPIOA
#define SPIx_MISO_GPIO_CLK               RCC_AHBPeriph_GPIOA
#define SPIx_MISO_SOURCE                 GPIO_PinSource6
#define SPIx_MISO_AF                     GPIO_AF_0

#define SPIx_MOSI_PIN                    GPIO_Pin_7
#define SPIx_MOSI_GPIO_PORT              GPIOA
#define SPIx_MOSI_GPIO_CLK               RCC_AHBPeriph_GPIOA
#define SPIx_MOSI_SOURCE                 GPIO_PinSource7
#define SPIx_MOSI_AF                     GPIO_AF_0


*/


















//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{

#define def_u8_success   	1
#define def_u8_fail			0

#define	READY				1
#define WAIT				0

#define def_u8_READY	(u8)(1)
#define def_u8_WAIT		(u8)(0)


#define def_enable_sys_usart_1
#define def_enable_sys_usart_1_startup_on_reset




//#include "stm32f0xx.h"

/*!< STM32F10x Standard Peripheral Library old types (maintained for legacy purpose) */
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  /*!< Read Only */
typedef const int16_t sc16;  /*!< Read Only */
typedef const int8_t sc8;   /*!< Read Only */

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  /*!< Read Only */
typedef __I int16_t vsc16;  /*!< Read Only */
typedef __I int8_t vsc8;   /*!< Read Only */

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  /*!< Read Only */
typedef const uint16_t uc16;  /*!< Read Only */
typedef const uint8_t uc8;   /*!< Read Only */

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  /*!< Read Only */
typedef __I uint16_t vuc16;  /*!< Read Only */
typedef __I uint8_t vuc8;   /*!< Read Only */



#include	"type_definitions.h"


#endif /* 003_SYS_TOP_LEVEL_INC_SYS_TOP_LEVEL_GLOBAL_H_ */

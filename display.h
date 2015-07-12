
#ifndef __TB_DISPLAY_H__
#define __TB_DISPLAY_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "registers.h"
#include "rom_map.h"

// display resolutions
#define TFT_WIDTH 320
#define TFT_HEIGHT 480

// Package pins to GPIO ports
#define CC_PIN_01 	10
#define CC_PIN_02 	11
#define CC_PIN_03 	12
#define CC_PIN_04 	13
#define CC_PIN_05 	14
#define CC_PIN_06 	15
#define CC_PIN_07 	16
#define CC_PIN_08 	17
#define CC_PIN_15 	22
#define CC_PIN_16 	23
#define CC_PIN_17 	24
#define CC_PIN_18 	28
#define CC_PIN_20 	29
#define CC_PIN_21 	25
#define CC_PIN_45 	31
#define CC_PIN_50 	0
#define CC_PIN_52 	32
#define CC_PIN_53 	30
#define CC_PIN_55 	1
#define CC_PIN_57 	2
#define CC_PIN_58 	3
#define CC_PIN_59 	4
#define CC_PIN_60 	5
#define CC_PIN_61 	6
#define CC_PIN_62 	7
#define CC_PIN_63 	8
#define CC_PIN_64 	9

// data pins for display
#define CS_PIN 		CC_PIN_58
#define CD_PIN		CC_PIN_59
#define WR_PIN		CC_PIN_60
#define RD_PIN		CC_PIN_61

#define DP_00		CC_PIN_63
#define DP_01		CC_PIN_64
#define DP_02		CC_PIN_01
#define DP_03		CC_PIN_02
#define DP_04		CC_PIN_03
#define DP_05		CC_PIN_04
#define DP_06		CC_PIN_05
#define DP_07		CC_PIN_06


#define DATA_PORT   GPIOA1_BASE

//#define HI(x)		HWREG(x)=1
//#define LO(x)		HWREG(x)=0

#define MOD_SHIFT(x)	1 << (x % 8)

#define CMD_PIN_LO(x)	HWREG(GPIOA0_BASE + (GPIO_O_GPIO_DATA + (MOD_SHIFT(x) << 2))) = 0
#define CMD_PIN_HI(x)	HWREG(GPIOA0_BASE + (GPIO_O_GPIO_DATA + (MOD_SHIFT(x) << 2))) = MOD_SHIFT(x)

//#define RD_REG		GPIOA0_BASE + (GPIO_O_GPIO_DATA + (PORT_PIN(RD_PIN) << 2))
#define RD_ACTIVE 	CMD_PIN_LO(RD_PIN)
#define RD_IDLE	 	CMD_PIN_HI(RD_PIN)

//#define WR_ACTIVE 	GPIO_IF_Set(WR_PIN, GPIOA0_BASE, PORT_PIN(WR_PIN), 0)
//#define WR_IDLE	 	GPIO_IF_Set(WR_PIN, GPIOA0_BASE, PORT_PIN(WR_PIN), 1)

#define CS_ACTIVE 	CMD_PIN_LO(CS_PIN)
#define CS_IDLE	 	CMD_PIN_HI(CS_PIN)

#define CD_COMMAND 	CMD_PIN_LO(CD_PIN)
#define CD_DATA	 	CMD_PIN_HI(CD_PIN)

//#define RD_ACTIVE	HWREG(GPIOA0_BASE + (GPIO_O_GPIO_DATA + (PORT_PIN(RD_PIN) << 2)))=0
//#define RD_IDLE		HWREG(GPIOA0_BASE + (GPIO_O_GPIO_DATA + (PORT_PIN(RD_PIN) << 2)))=1

//#define WR_REG		GPIOA0_BASE + (GPIO_O_GPIO_DATA + (PORT_PIN(WR_PIN) << 2))
#define WR_ACTIVE	CMD_PIN_LO(WR_PIN)
#define WR_IDLE		CMD_PIN_HI(WR_PIN)

//#define CS_REG		GPIOA0_BASE + (GPIO_O_GPIO_DATA + (PORT_PIN(CS_PIN) << 2))
/*#define CS_ACTIVE	HWREG(GPIOA0_BASE + (GPIO_O_GPIO_DATA + (PORT_PIN(CS_PIN) << 2)))=0
#define CS_IDLE		HWREG(GPIOA0_BASE + (GPIO_O_GPIO_DATA + (PORT_PIN(CS_PIN) << 2)))=1

//#define CD_REG		GPIOA0_BASE + (GPIO_O_GPIO_DATA + (PORT_PIN(CD_PIN) << 2))
#define CD_COMMAND 	HWREG(GPIOA0_BASE + (GPIO_O_GPIO_DATA + (PORT_PIN(CD_PIN) << 2)))=0
#define CD_DATA 	HWREG(GPIOA0_BASE + (GPIO_O_GPIO_DATA + (PORT_PIN(CD_PIN) << 2)))=1
*/

// send 2 commands
#define WR_STROBE { WR_ACTIVE; WR_IDLE; }

#define Write8Inline(x)		 { HWREG(DATA_PORT + (GPIO_O_GPIO_DATA + 0x3FC))=(x); WR_STROBE; }

#define writeRegisterPairInline(aH, aL, d) { \
  uint8_t hi = (d) >> 8, lo = (d); \
  CD_COMMAND; Write8Inline(aH); CD_DATA; Write8Inline(hi); \
  CD_COMMAND; Write8Inline(aL); CD_DATA; Write8Inline(lo); }

#define RGB(r,g,b)			((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
//#define RGB(r,g,b)			(r >> 3) & ((g >> 2 & 0x3F) << 6) & ((b >> 3 & 0x1F) << 11)

void InitDisplay();
//void SendData(unsigned char command, int length, unsigned char *values);
//void DigitalWrite(uint8_t pinNum, uint8_t value);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif

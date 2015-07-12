
#include <stdint.h>
#include <stdio.h>

#include "registers.h"
#include "display.h"
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_gpio.h"
#include "pin.h"
#include "gpio.h"
#include "utils.h"
#include "rom_map.h"
#include "gpio_if.h"
#include "uart_if.h"


#define _width 		TFT_WIDTH
#define _height 	TFT_HEIGHT

#define TFTLCD_DELAY 0xFF


static const uint8_t HX8357D_initProcess[] = {
  HX8357_SWRESET, 0,
  HX8357D_SETC, 3, 0xFF, 0x83, 0x57,
  TFTLCD_DELAY, 250,
  HX8357_SETRGB, 4, 0x00, 0x00, 0x06, 0x06,
  HX8357D_SETCOM, 1, 0x25,  // -1.52V
  HX8357_SETOSC, 1, 0x68,  // Normal mode 70Hz, Idle mode 55 Hz
  HX8357_SETPANEL, 1, 0x05,  // BGR, Gate direction swapped
  HX8357_SETPWR1, 6, 0x00, 0x15, 0x1C, 0x1C, 0x83, 0xAA,
  HX8357D_SETSTBA, 6, 0x50, 0x50, 0x01, 0x3C, 0x1E, 0x08,
  // MEME GAMMA HERE
  HX8357D_SETCYC, 7, 0x02, 0x40, 0x00, 0x2A, 0x2A, 0x0D, 0x78,
  HX8357_COLMOD, 1, 0x55,
  HX8357_MADCTL, 1, 0xC0,
  HX8357_TEON, 1, 0x00,
  HX8357_TEARLINE, 2, 0x00, 0x02,
  HX8357_SLPOUT, 0,
  TFTLCD_DELAY, 150,
  HX8357_DISPON, 0,
  //HX8357_DISPOFF, 0,
  TFTLCD_DELAY, 50,
};

void
Debug(char *format, ...)
{
#ifndef NOTERM
    char  cBuf[256];
    va_list list;
    va_start(list,format);
    vsnprintf(cBuf,256,format,list);
    Message(cBuf);
#endif
}

void WriteRegister32(uint8_t r, uint32_t d)
{
	  CS_ACTIVE;
	  CD_COMMAND;
	  Write8Inline(r);
	  CD_DATA;
	  MAP_UtilsDelay(100);
	  Write8Inline(d >> 24);
	  MAP_UtilsDelay(100);
	  Write8Inline(d >> 16);
	  MAP_UtilsDelay(100);
	  Write8Inline(d >> 8);
	  MAP_UtilsDelay(100);
	  Write8Inline(d);
	  CS_IDLE;
}

void Reset() {
	int i = 0;

	CS_IDLE;
	WR_IDLE;
	RD_IDLE;

	// Data transfer sync
	CS_ACTIVE;
	CD_COMMAND;
	Write8Inline(0x00);
	for(i=0; i<3; i++)
		WR_STROBE; // Three extra 0x00s

	CS_IDLE;
}

void setLR() {
	CS_ACTIVE;
	writeRegisterPairInline(HX8347G_COLADDREND_HI, HX8347G_COLADDREND_LO, _width  - 1);
	writeRegisterPairInline(HX8347G_ROWADDREND_HI, HX8347G_ROWADDREND_LO, _height - 1);
	CS_IDLE;
}

void setAddrWindow(int x1, int y1, int x2, int y2) {
	CS_ACTIVE;

    uint32_t t;

    t = x1;
    t <<= 16;
    t |= x2;
    WriteRegister32(ILI9341_COLADDRSET, t);  // HX8357D uses same registers!
    t = y1;
    t <<= 16;
    t |= y2;
    WriteRegister32(ILI9341_PAGEADDRSET, t); // HX8357D uses same registers!

    CS_IDLE;
}

void DrawPixel(int16_t x, int16_t y, uint16_t color) {

	if((x < 0) || (y < 0) || (x >= _width) || (y >= _height)) return;

	setAddrWindow(x, y, (long)_width-1, (long)_height-1);

	CS_ACTIVE;
	CD_COMMAND;
	Write8Inline(HX8357_RAMWR);
	CD_DATA;
	MAP_UtilsDelay(100);
	Write8Inline(color >> 8);
	MAP_UtilsDelay(100);
	Write8Inline(color);
	CS_IDLE;

	//Debug("%d, %d: %x|%x\r\n", x, y, color >> 8, color & 0xFF);
}

// Fast block fill operation for fillScreen, fillRect, H/V line, etc.
// Requires setAddrWindow() has previously been called to set the fill
// bounds.  'len' is inclusive, MUST be >= 1.
void Flood(uint16_t color, uint32_t len) {
  uint16_t blocks;
  uint8_t  i, hi = color >> 8,
              lo = color;

  CS_ACTIVE;
  CD_COMMAND;

  Write8Inline(HX8357_RAMWR);

  // Write first pixel normally, decrement counter by 1
  CD_DATA;
  Write8Inline(hi);
  Write8Inline(lo);
  len--;

  blocks = (uint16_t)(len / 64); // 64 pixels/block
  if(hi == lo) {
    // High and low bytes are identical.  Leave prior data
    // on the port(s) and just toggle the write strobe.
    while(blocks--) {
      i = 16; // 64 pixels/block / 4 pixels/pass
      do {
        WR_STROBE; WR_STROBE; WR_STROBE; WR_STROBE; // 2 bytes/pixel
        WR_STROBE; WR_STROBE; WR_STROBE; WR_STROBE; // x 4 pixels
      } while(--i);
    }
    // Fill any remaining pixels (1 to 64)
    for(i = (uint8_t)len & 63; i--; ) {
      WR_STROBE;
      WR_STROBE;
    }
  } else {
    while(blocks--) {
      i = 16; // 64 pixels/block / 4 pixels/pass
      do {
    	  Write8Inline(hi); Write8Inline(lo); Write8Inline(hi); Write8Inline(lo);
    	  Write8Inline(hi); Write8Inline(lo); Write8Inline(hi); Write8Inline(lo);
      } while(--i);
    }
    for(i = (uint8_t)len & 63; i--; ) {
    	Write8Inline(hi);
    	Write8Inline(lo);
    }
  }
  CS_IDLE;

  setLR();
}

// Initialize the display
void InitDisplay() {

	uint8_t command, length, cmdLength, index, i, d;

	//initPinMapping();

	//Message("Resetting Display...\n");
	Reset();


	//Debug("test here %x", 0x10);

	length = sizeof(HX8357D_initProcess) / sizeof(HX8357D_initProcess[0]);

	index = 0;

	while (index < length) {

		command = HX8357D_initProcess[index++];
		cmdLength = HX8357D_initProcess[index++];

		Debug("Command: 0x%x\n\r", command);

		if (command == TFTLCD_DELAY)
			MAP_UtilsDelay(cmdLength * 100);
		else
		{
			CS_ACTIVE;
			CD_COMMAND;
			Write8Inline(command);

			if (cmdLength > 0) {
				CD_DATA;
				for (i=0; i < cmdLength; i++) {
					d = HX8357D_initProcess[index + i];
					Write8Inline(d);
				}
				index += cmdLength;
			}
			CS_IDLE;
		}
	}

	setAddrWindow(0, 0, _width - 1, _height - 1);
	Flood(RGB(0xff,0xff,0x00), (long)_width * (long)_height);

	MAP_UtilsDelay(1000);

	DrawPixel(10, 10, RGB(0xff,0x00,0x00));
	DrawPixel(10, 100, 0);
	DrawPixel(100, 10, 0);
	DrawPixel(100, 100, 0);
	DrawPixel(11, 10, RGB(0xff,0x00,0x00));
	DrawPixel(10, 11, RGB(0xff,0x00,0x00));
	DrawPixel(11, 11, RGB(0xff,0x00,0x00));

}

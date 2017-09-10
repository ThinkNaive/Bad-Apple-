#ifndef _MAIN_H
#define _MAIN_H

#include <hpconio.h>
#include <stdint.h>
#include <hpstdio.h>

#define delay(t) { volatile int i = (t); while (i--); }
#define GPFDAT ((unsigned *)0x07A00054)
#define GPGCON ((unsigned *)0x07A00060)
#define GPGDAT ((unsigned *)0x07A00064)
#define on_pressed (*GPFDAT & 1)

#define WTCON   (*(volatile unsigned *)0x07800000) //Watch-dog timer mode
#define WTDAT   (*(volatile unsigned *)0x07800004) //Watch-dog timer data
#define WTCNT   (*(volatile unsigned *)0x07800008) //Eatch-dog timer count

#define SCREEN_WIDTH    131
#define SCREEN_HEIGHT   64
#define WIDTH_IN_BYTES  (96 / 8)
#define LEFT_MARGIN     (16 / 8)
#define BYTES_PER_ROW   20
#define FRAME_IN_BYTES	0x300

extern uint8_t *__display_buf;

#endif

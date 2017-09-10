#include "main.h"

uint8_t frame[SCREEN_HEIGHT][WIDTH_IN_BYTES];

void display(uint8_t data)
{
	static int row = -1;
	static int col = -1;
	if (col >= 0)
	{
		frame[row][col] = data;
		col = -1;
		return;
	}
	
	if (data != 0xFF)
	{
		col = data & 0x7F;
	}
	
	if (data & 0x80)
	{
		memcpy(	&__display_buf[row * BYTES_PER_ROW + LEFT_MARGIN],
					frame[row],
					WIDTH_IN_BYTES);
		row++;
		
		if (row & SCREEN_HEIGHT)
		{
			row = 0;
			delay(0x96420);
		}
	}
}

int main(void)
{
	clear_screen();
	uint32_t *badapple = (void *)0x133000;
	uint32_t *len = (void *)0x133004;
	uint8_t *video = (void *)0x133008;	// compressed using github.com/Arnie97/neko-notepad/tree/video delta_compress function
	uint32_t eof = video + *len;
		
	if (*badapple != 0xbada991e) return;
	
	while (video != eof)
	{
		display(*(video++));
		if (on_pressed) break;
	}
}

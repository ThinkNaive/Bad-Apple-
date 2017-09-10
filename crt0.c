#include <hpsys.h>
#include <saturn.h>

extern int *__exit_stk_state;
extern int _exit_save(unsigned int *ptr);
extern void __exit_cleanup();
int main(void);

// default monochrome display buffer
unsigned __display_buf;


void
_start(void)
{
	// read in the video buffer address
	// it assumes that the MMU mappings haven't changed
	// and the buffer is in the 4kb SRAM
	volatile unsigned *LCDSADDR1 = (unsigned *)0x7300014;
	__display_buf = (*LCDSADDR1 & 0xffff) * 2 + 0x7f00000;

	// declare locally to reduce executable size
	int state_buffer[4], lcd_buffer[17];
	__exit_stk_state = state_buffer;

	// turn interrupts off so we can use the screen
	sys_intOff();

	// save current hardware state
	sys_lcdsave(lcd_buffer);

	// initialize RPL stack access
	unsigned rpl_stack_bias = sat_stack_init();

	// will return 0 when exitting
	if (_exit_save((unsigned *)state_buffer)) {
		main();
		__exit_cleanup();
	}

	// finalize RPL stack access
	sat_stack_exit(rpl_stack_bias);

	// restore original hardware values
	sys_lcdrestore(lcd_buffer);

	// turn interrupts on for the OS
	sys_intOn();
}

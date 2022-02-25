#ifndef __FUN_MAIN_H__
#define __FUN_MAIN_H__


struct pico_fun_t {
	const char		*build_date;
	const char		*build_time;
	char			str_build[32];
	datetime_t		t;

	uint			pin_led;

	char			str_boardid[PICO_UNIQUE_BOARD_ID_SIZE_BYTES*2+1];
	

	struct fun_led_t	led;
	struct fun_button_t	btn;
	struct fun_oled_t	oled;
	struct fun_tick_t	tick;

	struct fun_screen_t	scr;
};


extern struct pico_fun_t gFUN;


#endif


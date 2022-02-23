#ifndef __COMMON_H__
#define __COMMON_H__


struct pico_fun_t {
	const char		*build_date;
	const char		*build_time;
	datetime_t		t;

	uint			pin_led;

	char			str_boardid[PICO_UNIQUE_BOARD_ID_SIZE_BYTES*2+1];
	

};



#endif


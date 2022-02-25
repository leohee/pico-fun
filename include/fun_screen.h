#ifndef __FUN_SCREEN_H__
#define __FUN_SCREEN_H__

enum {
	PAGE_ABOUT			= (0),
	PAGE_HELP			= (1),
	PAGE_CLOCK			= (2),
	PAGE_TEST1			= (3),
	PAGE_TEST2			= (4),

	PAGE_TOTAL
};


struct fun_screen_t {
	uint8_t			CurrentPageNo;
	uint16_t		PageChange;
	
};

extern void fun_screen_flush (uint8_t number);

extern void fun_screen_init (void);


#endif



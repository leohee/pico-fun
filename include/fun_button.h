#ifndef __BUTTON_H__
#define __BUTTON_H__


struct fun_button_t {
	bool			last_state;

	bool			press_on;		/* true when hold press on */
	bool			press_off;		/* true when hold press off */

	uint			count_kick;		/* count on-off */
	uint			count_double_kick;

	uint64_t		last_us;		/* last button event timestamp */
	bool			quick_press;	/* quick than 300ms */

	struct repeating_timer tmr;

};



bool board_button_read (void);

extern void fun_button_init (void);


#endif


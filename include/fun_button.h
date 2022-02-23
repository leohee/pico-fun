#ifndef __BUTTON_H__
#define __BUTTON_H__


struct fun_button_t {
	bool			last_state;

	bool			press_on;		/* true when hold press on */
	bool			press_off;		/* true when hold press off */

	uint			count;			/* count on-off */
	struct repeating_timer tmr;

};



bool board_button_read (void);

extern void fun_button_init (void);


#endif


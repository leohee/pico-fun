#ifndef __FUN_TICK_H__
#define __FUN_TICK_H__

#define SIZE_TIMESTAMP		(32)

struct fun_tick_t {

	char					str_clock[SIZE_TIMESTAMP];
	struct repeating_timer tmr;

};

extern void fun_tick_init (void);


#endif



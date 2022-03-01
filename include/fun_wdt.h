#ifndef __FUN_WATCHDOG_H__
#define __FUN_WATCHDOG_H__

struct fun_wdt_t {
	bool			enable;
	uint			period;
};


extern void fun_wdt_feed (void);

extern void fun_wdt_init (void);


#endif




#include "inc_file.h"


void fun_wdt_feed (void)
{
	watchdog_update();
}


void fun_wdt_init (void)
{
    if (watchdog_caused_reboot()) {
        printf("Rebooted by Watchdog!\n");
    } else {
        printf("Clean boot\n");
    }

	// 2s
	watchdog_enable(2000, 1);

}




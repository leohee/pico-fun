
#include "inc_file.h"


void fun_wdt_feed (void)
{
	if (gFUN.wdt.enable) {
		watchdog_update();
	}
}


void fun_wdt_init (void)
{
	struct fun_wdt_t *pWDT = &gFUN.wdt;

	pWDT->enable = true;
	pWDT->period = 2000;

    if (watchdog_caused_reboot()) {
        LOG_INF("====Rebooted by Watchdog!====");
    }

	if (pWDT->enable) {
		watchdog_enable(pWDT->period, 1);
	}
}




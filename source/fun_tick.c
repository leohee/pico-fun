
#include "inc_file.h"

static void datetime_format (char *buf, uint buf_size, const datetime_t *t)
{
    snprintf(buf, buf_size,
        "%04d-%02d-%02d %02d:%02d:%02d",
        t->year, t->month, t->day, t->hour, t->min, t->sec);
}

bool fun_tick_timer_cb (struct repeating_timer *t)
{
	struct fun_tick_t *pTICK = &gFUN.tick;

	gFUN.led.toggle();

	fun_wdt_feed();

	if (PAGE_CLOCK == gFUN.scr.CurrentPageNo) {
		memset(pTICK->str_clock, 0x00, SIZE_TIMESTAMP);

		rtc_get_datetime(&gFUN.t);
		datetime_format(pTICK->str_clock, SIZE_TIMESTAMP, &gFUN.t);

		fun_oled_flush_clock(pTICK->str_clock);
	}
}


void fun_tick_init (void)
{
	struct fun_tick_t *pTICK = &gFUN.tick;

	add_repeating_timer_ms(-1000, fun_tick_timer_cb, NULL, &pTICK->tmr);


}





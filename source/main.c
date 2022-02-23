#include <stdio.h>
#include <string.h>
#include "hardware/rtc.h"
#include "pico/stdlib.h"
#include "pico/unique_id.h"
#include "pico/util/datetime.h"

#include "build_ver.h"
#include "common.h"
#include "button.h"

struct pico_fun_t gFUN;

void datetime_format(char *buf, uint buf_size, const datetime_t *t)
{
    snprintf(buf, buf_size,
        "%04d-%02d-%02d %02d:%02d:%02d",
        t->year, t->month, t->day,
        t->hour, t->min, t->sec);
}

const char str_date[] = DATE_BUILD;
int firmware_info (void)
{
	gFUN.pin_led = PICO_DEFAULT_LED_PIN;

	gFUN.build_date = str_date;
	gFUN.build_time = TIME_BUILD;

	int y = 0, m = 0, d = 0;
	int h = 0, min = 0, s = 0;

	sscanf(gFUN.build_date, "%d-%d-%d", &y, &m, &d);
	sscanf(gFUN.build_time, "%d:%d:%d", &h, &min, &s);

    gFUN.t.year = y;
    gFUN.t.month = m;
    gFUN.t.day = d;
    gFUN.t.hour = h;
    gFUN.t.min = min;
    gFUN.t.sec = s;

	pico_unique_board_id_t board_id;
    pico_get_unique_board_id(&board_id);

	sprintf(gFUN.str_boardid, "%02X%02X%02X%02X%02X%02X%02X%02X",
		board_id.id[0], board_id.id[1], board_id.id[2], board_id.id[3],
		board_id.id[4], board_id.id[5], board_id.id[6], board_id.id[7]);


	return 0;
}

struct repeating_timer timer;

bool repeating_timer_callback (struct repeating_timer *t)
{
	static int cnt = 0;

    printf("%d : %lld\n", cnt, time_us_64());

	++cnt;

	gpio_put(gFUN.pin_led, cnt%2);

/*
	if (cnt >= 30) {
    	bool cancelled = cancel_repeating_timer(&timer);
    	printf("cancelled... %d\n", cancelled);
	}
*/
    return true;
}

int main (void)
{
    stdio_init_all();


    char buf_datetime[256] = {0};
    char *str_datetime = &buf_datetime[0];

	firmware_info();

    rtc_init();
    rtc_set_datetime(&gFUN.t);

    gpio_init(gFUN.pin_led);
    gpio_set_dir(gFUN.pin_led, GPIO_OUT);


	add_repeating_timer_ms(-1000, repeating_timer_callback, NULL, &timer);

    while (true) {
        if (board_button_read()) {
			printf("BoardID : %s\n", gFUN.str_boardid);
			printf("Pico %s built @ %s %s\n", PICO_SDK_VERSION_STRING, gFUN.build_date, gFUN.build_time);
            rtc_get_datetime(&gFUN.t);
            datetime_format(str_datetime, sizeof(buf_datetime), &gFUN.t);
            printf("%s\n", str_datetime);

			sleep_ms(10);
        } else {
			sleep_ms(10);
		}
    }


    return 0;
}




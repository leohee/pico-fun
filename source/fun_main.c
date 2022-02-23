
#include "inc_file.h"

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

static int fun_pico_init (void)
{


	fun_led_init();
	fun_button_init();



	return 0;
}

int main (void)
{
    char buf_datetime[256] = {0};
    char *str_datetime = &buf_datetime[0];
	int i_cnt = 0;

    stdio_init_all();

	firmware_info();

    rtc_init();
    rtc_set_datetime(&gFUN.t);

	fun_pico_init();

    while (true) {
        /*if (board_button_read()) {
			printf("BoardID : %s\n", gFUN.str_boardid);
			printf("Pico %s built @ %s %s\n", PICO_SDK_VERSION_STRING, gFUN.build_date, gFUN.build_time);
            rtc_get_datetime(&gFUN.t);
            datetime_format(str_datetime, sizeof(buf_datetime), &gFUN.t);
            printf("%s\n", str_datetime);

			sleep_ms(10);

			gFUN.led.toggle();
        } else {
			sleep_ms(10);
		}*/

		gFUN.led.toggle();
		sleep_ms(1000);

		++i_cnt;

		if (i_cnt % 30 == 10 ) {
			printf("led toggle 500ms\n");
			fun_led_show(true, 10, 500, 500);
		}

		if (i_cnt % 30 == 20 ) {
			printf("led toggle 250ms\n");
			fun_led_show(true, 20, 250, 250);
		}

		if (i_cnt % 30 == 0 ) {
			printf("led toggle 1000ms\n");
		}

    }

    return 0;
}




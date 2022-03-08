
#include "inc_file.h"

struct pico_fun_t gFUN;



const char str_date[] = DATE_BUILD;
int firmware_info (void)
{
	int y = 0, m = 0, d = 0;
	int h = 0, min = 0, s = 0;


	gFUN.build_date = str_date;
	gFUN.build_time = TIME_BUILD;

	memset(gFUN.str_build, 0x00, 32);
	snprintf(gFUN.str_build, 32, "%s %s", gFUN.build_date, gFUN.build_time);

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

	memset(gFUN.str_boardid, 0x00, PICO_UNIQUE_BOARD_ID_SIZE_BYTES*2+1);
	sprintf(gFUN.str_boardid, "%02X%02X%02X%02X%02X%02X%02X%02X",
		board_id.id[0], board_id.id[1], board_id.id[2], board_id.id[3],
		board_id.id[4], board_id.id[5], board_id.id[6], board_id.id[7]);


	return 0;
}

static int fun_pico_init (void)
{
	fun_led_init();
	fun_button_init();
	fun_oled_init();
	fun_tick_init();
	fun_screen_init();

	fun_nrf24_init();

	fun_wdt_init();

	fun_cli_init();

	fun_esp_init();

	return 0;
}

int main (void)
{
    stdio_init_all();

	sleep_ms(5000);

	fun_log_init();

	firmware_info();
	sleep_ms(500);

	printf("\n");
	LOG_INF("BoardID : %s", gFUN.str_boardid);
	LOG_INF("Pico %s built @ %s %s", PICO_SDK_VERSION_STRING, 
		gFUN.build_date, gFUN.build_time);

    rtc_init();
    rtc_set_datetime(&gFUN.t);

	fun_pico_init();

    while (1) {
		cli_catch_input();
		sleep_ms(1);
    }

    return 0;
}




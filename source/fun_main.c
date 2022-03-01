
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

	return 0;
}

int main (void)
{
	uint64_t us = 0;
	char cur_us[21] = {0x00};

    stdio_init_all();

	firmware_info();
	sleep_ms(100);

	printf("\nBoardID : %s\n", gFUN.str_boardid);
	printf("Pico %s built @ %s %s\n", PICO_SDK_VERSION_STRING, 
		gFUN.build_date, gFUN.build_time);

    rtc_init();
    rtc_set_datetime(&gFUN.t);

	fun_pico_init();

    while (1) {
/*
		if (PAGE_CLOCK == gFUN.scr.CurrentPageNo) {
			us = time_us_64();
			snprintf(cur_us, 21, "%lld.%06llds", us/1000000, us%1000000);
			fun_oled_flush_area_string(0, 125, 0, 0, cur_us);
		}
		sleep_ms(100);
*/
/*
		if (true == gFUN.nrf.ready) {
			if (RX_MODE == gFUN.nrf.mode) {
				fun_nrf24_rcv_loop();
			} else {
				fun_nrf24_snd_loop();
			}
		}
*/
		cli_parser_proc();
		sleep_ms(1);
    }

    return 0;
}




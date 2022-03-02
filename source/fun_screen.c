
#include "inc_file.h"


#define AlphabetUpper	"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"
#define AlphabetLower	"abcdefghijklmnopqrstuvwxyz1234567890"


void fun_screen_flush (uint8_t number)
{
	fun_oled_clear_screen();
	LOG_INF("page %d", number);

	switch (number) {
	case PAGE_ABOUT:
		fun_oled_flush_area_string(0, OLED_WIDTH-3, 0, 0, "Pico Board ID :");
		fun_oled_flush_area_string(0, OLED_WIDTH-3, 1, 1, gFUN.str_boardid);
		fun_oled_flush_area_string(0, OLED_WIDTH-3, 2, 2, "V1.0 built @");
		fun_oled_flush_area_string(0, OLED_WIDTH-3, 3, 3, gFUN.str_build);
		break;
	case PAGE_HELP:
		fun_oled_flush_area_string(0, OLED_WIDTH-3, 0, 3, "Raspberry Pi Pico is a low-cost, "\
			"high-performance microcontroller board with flexible digital interfaces.");
		break;
	case PAGE_CLOCK:
		fun_oled_flush_area_string(0, OLED_WIDTH-3, 1, 1, "Current clock :");
		break;
	case PAGE_NRF24:
		fun_oled_flush_area_string(0, OLED_WIDTH-3, 0, 0, "nRF24 mode :");
		fun_oled_flush_area_string(0, OLED_WIDTH-3, 1, 1, 
			gFUN.nrf.mode==RX_MODE?"Rx":"Tx");
		break;
/*	case PAGE_TEST1:
		fun_oled_flush_area_string(0, 59, 0, 3, AlphabetUpper);

		fun_oled_flush_area_string(64, 123, 0, 3, AlphabetLower);
		break;
	case PAGE_TEST2:
		fun_oled_flush_area_string(0, OLED_WIDTH-3, 0, 1, AlphabetUpper);

		fun_oled_flush_area_string(0, OLED_WIDTH-3, 2, 3, AlphabetLower);
		break;
*/
	}


	gFUN.scr.CurrentPageNo = number%PAGE_TOTAL;
}



void fun_screen_init (void)
{
	struct fun_screen_t *pSCR = &gFUN.scr;

	pSCR->CurrentPageNo = PAGE_ABOUT;

	fun_screen_flush(pSCR->CurrentPageNo);
}




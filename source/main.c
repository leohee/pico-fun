#include <stdio.h>
#include <string.h>
#include "hardware/rtc.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"

#define BUILD_CLOCK     __DATE__", "__TIME__

void datetime_format(char *buf, uint buf_size, const datetime_t *t)
{
    snprintf(buf, buf_size,
        "%04d-%02d-%02d %02d:%02d:%02d",
        t->year, t->month, t->day,
        t->hour, t->min, t->sec);
}

static uint8_t utility_conv_month (char *month)
{
	uint8_t m = 1;
	if (strcasecmp("Jan", month) == 0) {
		m = 1;
	} else if (strcasecmp("Feb", month) == 0) {
		m = 2;
	} else if (strcasecmp("Mar", month) == 0) {
		m = 3;
	} else if (strcasecmp("Apr", month) == 0) {
		m = 4;
	} else if (strcasecmp("May", month) == 0) {
		m = 5;
	} else if (strcasecmp("Jun", month) == 0) {
		m = 6;
	} else if (strcasecmp("Jul", month) == 0) {
		m = 7;
	} else if (strcasecmp("Aug", month) == 0) {
		m = 8;
	} else if (strcasecmp("Sep", month) == 0) {
		m = 9;
	} else if (strcasecmp("Oct", month) == 0) {
		m = 10;
	} else if (strcasecmp("Nov", month) == 0) {
		m = 11;
	} else if (strcasecmp("Dec", month) == 0) {
		m = 12;
	}

	return m;
}

int convert_buildtime(datetime_t *t)
{
    char str[32] = {0};
    char month[6] = {0};
    int y = 0, d = 0, h = 0, min = 0, s = 0;

    strcpy(str, BUILD_CLOCK);
    sscanf(str, "%s %d %d, %d:%d:%d", month, &d, &y, &h, &min, &s);

    t->year = y;
    t->month = utility_conv_month(month);
    t->day = d;
    t->dotw = 4;
    t->hour = h;
    t->min = min;
    t->sec = s;

    return 0;
}

int main() {
    int cnt = 0;
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;

    stdio_init_all();
    printf("Pico built (%s).\n", BUILD_CLOCK);

    char buf_datetime[256] = {0};
    char *str_datetime = &buf_datetime[0];

    datetime_t t;

    convert_buildtime(&t);

    rtc_init();
    rtc_set_datetime(&t);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        if (cnt++ % 10 == 2) {
            rtc_get_datetime(&t);
            datetime_format(str_datetime, sizeof(buf_datetime), &t);
            printf("\rPico : %s", str_datetime);
        }

        gpio_put(LED_PIN, 1);
        sleep_ms(500);
        gpio_put(LED_PIN, 0);
        sleep_ms(500);
    }
    return 0;
}

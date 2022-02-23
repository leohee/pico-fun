
#include "inc_file.h"

bool fun_led_on_timer_cb (struct repeating_timer *t);
bool fun_led_off_timer_cb (struct repeating_timer *t);


static void fun_led_toggle (void)
{
	struct fun_led_t *pLED = &gFUN.led;
	static bool led_state = LED_ON;

	if (!pLED->tmr_ctrl) {
		pLED->put(pLED->pin, led_state);

		led_state = 1 - led_state;
	}
}

bool fun_led_on_timer_cb (struct repeating_timer *t)
{
	struct fun_led_t *pLED = &gFUN.led;

	cancel_repeating_timer(&pLED->tmr);

	if (pLED->circle) {
		pLED->stage = LED_STAGE_OFF;
		pLED->put(pLED->pin, LED_OFF);
		pLED->tmr_ctrl = true;
		add_repeating_timer_ms(pLED->milli_off, fun_led_off_timer_cb, NULL, &pLED->tmr);
	} else {
		pLED->stage = LED_STAGE_IDLE;
		pLED->tmr_ctrl = false;
	}

    return true;
}

bool fun_led_off_timer_cb (struct repeating_timer *t)
{
	struct fun_led_t *pLED = &gFUN.led;

	cancel_repeating_timer(&pLED->tmr);

	pLED->stage = LED_STAGE_IDLE;

	if (pLED->circle) {
		if (TIMES_ALWAYS == pLED->times) {
			pLED->stage = LED_STAGE_ON;
			pLED->put(pLED->pin, LED_ON);
			pLED->tmr_ctrl = true;
			add_repeating_timer_ms(pLED->milli_on, fun_led_on_timer_cb, NULL, &pLED->tmr);
		} else {
			if (++pLED->cnt >= pLED->times) {
				pLED->circle = false;
				pLED->cnt = 0;
				pLED->tmr_ctrl = false;
			} else {
				pLED->stage = LED_STAGE_ON;
				pLED->put(pLED->pin, LED_ON);
				pLED->tmr_ctrl = true;
				add_repeating_timer_ms(pLED->milli_on, fun_led_on_timer_cb, NULL, &pLED->tmr);
			}
		}
	} else {
		pLED->tmr_ctrl = false;
	}

    return true;
}

void fun_led_show (uint8_t circle, uint times, uint on, uint off)
{
	struct fun_led_t *pLED = &gFUN.led;
	cancel_repeating_timer(&pLED->tmr);

	pLED->milli_on = -on;
	pLED->milli_off = -off;
	pLED->circle = circle;
	pLED->times = times;
	pLED->cnt = 0;

	pLED->stage = LED_STAGE_ON;

	pLED->tmr_ctrl = true;
	if (on == HOLD_ZERO) {
		pLED->put(pLED->pin, LED_OFF);
	} else {
		pLED->put(pLED->pin, LED_ON);
		if (off != HOLD_ZERO) {
			add_repeating_timer_ms(pLED->milli_on, fun_led_on_timer_cb, NULL, &pLED->tmr);
		}
	}
}

void fun_led_init (void)
{
	struct fun_led_t *pLED = &gFUN.led;

	pLED->pin = PICO_DEFAULT_LED_PIN;

	pLED->tmr_ctrl = false;
	pLED->milli_on = -1000;
	pLED->milli_off = -1000;
	pLED->circle = true;
	pLED->stage = LED_STAGE_IDLE;
	pLED->times = TIMES_ALWAYS;
	pLED->cnt = 0;

    gpio_init(pLED->pin);
    gpio_set_dir(pLED->pin, GPIO_OUT);

	pLED->put = gpio_put;
	pLED->toggle = fun_led_toggle;

	//fun_led_show(true, TIMES_ALWAYS, 1000, 1000);


}




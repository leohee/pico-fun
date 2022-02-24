
#include "inc_file.h"

// This example blinks the Pico LED when the BOOTSEL button is pressed.
//
// Picoboard has a button attached to the flash CS pin, which the bootrom
// checks, and jumps straight to the USB bootcode if the button is pressed
// (pulling flash CS low). We can check this pin in by jumping to some code in
// SRAM (so that the XIP interface is not required), floating the flash CS
// pin, and observing whether it is pulled low.
//
// This doesn't work if others are trying to access flash at the same time,
// e.g. XIP streamer, or the other core.
bool __no_inline_not_in_flash_func(get_bootsel_button)()
{
    const uint CS_PIN_INDEX = 1;

    // Must disable interrupts, as interrupt handlers may be in flash, and we
    // are about to temporarily disable flash access!
    uint32_t flags = save_and_disable_interrupts();

    // Set chip select to Hi-Z
    hw_write_masked(&ioqspi_hw->io[CS_PIN_INDEX].ctrl,
                    GPIO_OVERRIDE_LOW << IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_LSB,
                    IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_BITS);

    // Note we can't call into any sleep functions in flash right now
    for (volatile int i = 0; i < 1000; ++i);

    // The HI GPIO registers in SIO can observe and control the 6 QSPI pins.
    // Note the button pulls the pin *low* when pressed.
    bool button_state = !(sio_hw->gpio_hi_in & (1u << CS_PIN_INDEX));

    // Need to restore the state of chip select, else we are going to have a
    // bad time when we return to code in flash!
    hw_write_masked(&ioqspi_hw->io[CS_PIN_INDEX].ctrl,
                    GPIO_OVERRIDE_NORMAL << IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_LSB,
                    IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_BITS);

    restore_interrupts(flags);

    return button_state;
}

bool board_button_read (void)
{
	return (1 == get_bootsel_button());
}


bool fun_button_timer_cb (struct repeating_timer *t)
{
	struct fun_button_t *pBTN = &gFUN.btn;
	uint64_t now_us = 0;

	bool state_new = board_button_read();

	if (state_new != pBTN->last_state) {
		if (true == state_new) {
			pBTN->press_on = true;
		} else {
			pBTN->press_off = true;
		}

		if (pBTN->press_on && pBTN->press_off) {
			now_us = time_us_64();
			printf("click @ %lld us\n", now_us);

			if (now_us - pBTN->last_us <= 300000) { // 300ms
				pBTN->quick_press = true;
				pBTN->count_double_kick++;
			} else {
				pBTN->quick_press = false;
			}

			pBTN->last_us = now_us;

			if (pBTN->quick_press) {
				printf("Double clicked.\n");
				fun_led_show(true, TIMES_ALWAYS, (pBTN->count_double_kick%5+1)*100, 
					(pBTN->count_double_kick%5+1)*100);
			}

			pBTN->count_kick++;
			pBTN->press_on = false;
			pBTN->press_off = false;

			oled_ori_scroll(pBTN->count_kick%4, pBTN->count_double_kick%10);
		}

		pBTN->last_state = state_new;
	}

    return true;
}

void fun_button_init (void)
{
	struct fun_button_t *pBTN = &gFUN.btn;

	pBTN->last_state = board_button_read();

	pBTN->press_on = false;
	pBTN->press_off = false;
	pBTN->count_kick = 0;
	pBTN->count_double_kick = 0;
	pBTN->last_us = time_us_64();
	pBTN->quick_press = false;

	add_repeating_timer_ms(-20, fun_button_timer_cb, NULL, &pBTN->tmr);

}




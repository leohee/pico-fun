#ifndef __INC_FILE_H__
#define __INC_FILE_H__

#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "pico/binary_info.h"
#include "pico/stdlib.h"
#include "pico/unique_id.h"
#include "pico/util/datetime.h"
#include "pico/util/queue.h"

#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "hardware/rtc.h"
#include "hardware/spi.h"
#include "hardware/sync.h"
#include "hardware/structs/ioqspi.h"
#include "hardware/structs/sio.h"
#include "hardware/watchdog.h"


#include "build_ver.h"
#include "fun_button.h"
#include "fun_led.h"
#include "fun_tick.h"
#include "fun_oled.h"
#include "fun_screen.h"
#include "fun_wdt.h"
#include "fun_cli.h"

#include "nRF24L01_regs.h"
#include "fun_nrf24.h"


#include "fun_main.h"




#endif /* __INC_FILE_H__ */



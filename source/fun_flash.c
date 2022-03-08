
#include "inc_file.h"

const uint8_t *flash_target_contents = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);


void fun_flash_test (void)
{
	srand(time_us_32());

    uint8_t random_data[FLASH_PAGE_SIZE];
    for (int i = 0; i < FLASH_PAGE_SIZE; ++i) {
        random_data[i] = rand() >> 16;
	}

	LOG_ERR("somethin critical error bug when flash");

	LOG_DBG_HEX("Read target region", flash_target_contents, FLASH_PAGE_SIZE);
	LOG_DBG_HEX("Generated random data", random_data, FLASH_PAGE_SIZE);
sleep_ms(1000);
    LOG_WRN("Erasing target region...");
//    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
    LOG_WRN("Erase Done.");
sleep_ms(1000);
	LOG_DBG_HEX("Read back target region", flash_target_contents, FLASH_PAGE_SIZE);

	LOG_INF("Programming target region...");
sleep_ms(1000);
	flash_range_program(FLASH_TARGET_OFFSET, random_data, FLASH_PAGE_SIZE);
sleep_ms(1000);
	LOG_DBG_HEX("Read back target region again", flash_target_contents, FLASH_PAGE_SIZE);
sleep_ms(1000);

    bool mismatch = false;
    for (int i = 0; i < FLASH_PAGE_SIZE; ++i) {
        if (random_data[i] != flash_target_contents[i])
            mismatch = true;
    }

    if (mismatch) {
        LOG_ERR("Programming failed!");
    } else {
        LOG_INF("Programming successful!");
    }
}

void fun_flash_read (void)
{
	LOG_DBG_HEX("Read target region", flash_target_contents, FLASH_PAGE_SIZE);

}



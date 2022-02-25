#ifndef __FUN_OLED_H__
#define __FUN_OLED_H__

/*
   GPIO PICO_DEFAULT_I2C_SDA_PIN (on Pico this is GP4 (pin 6)) -> SDA on display
   board
   GPIO PICO_DEFAULT_I2C_SCK_PIN (on Pico this is GP5 (pin 7)) -> SCL on
   display board
   3.3v (pin 36) -> VCC on display board
   GND (pin 38)  -> GND on display board
*/

// commands (see datasheet)
#define OLED_SET_CONTRAST				(0x81)
#define OLED_SET_ENTIRE_ON				(0xA4)
#define OLED_SET_NORM_INV				(0xA6)
#define OLED_SET_DISP					(0xAE)
#define OLED_SET_MEM_ADDR				(0x20)
#define OLED_SET_COL_ADDR				(0x21)
#define OLED_SET_PAGE_ADDR				(0x22)
#define OLED_SET_DISP_START_LINE		(0x40)
#define OLED_SET_SEG_REMAP				(0xA0)
#define OLED_SET_MUX_RATIO				(0xA8)
#define OLED_SET_COM_OUT_DIR			(0xC0)
#define OLED_SET_DISP_OFFSET			(0xD3)
#define OLED_SET_COM_PIN_CFG			(0xDA)
#define OLED_SET_DISP_CLK_DIV			(0xD5)
#define OLED_SET_PRECHARGE				(0xD9)
#define OLED_SET_VCOM_DESEL				(0xDB)
#define OLED_SET_CHARGE_PUMP			(0x8D)
#define OLED_SET_HORIZ_SCROLL			(0x26)
#define OLED_SET_SCROLL					(0x2E)

#define OLED_ADDR						(0x3C)
#define OLED_HEIGHT						(32)
#define OLED_WIDTH						(128)
#define OLED_PAGE_HEIGHT				(8)
#define OLED_NUM_PAGES					(OLED_HEIGHT / OLED_PAGE_HEIGHT)
#define OLED_BUF_LEN					(OLED_NUM_PAGES * OLED_WIDTH)

#define OLED_WRITE_MODE					(0xFE)
#define OLED_READ_MODE					(0xFF)

#define IMG_WIDTH						(26)
#define IMG_HEIGHT						(32)


struct render_area {
    uint8_t start_col;
    uint8_t end_col;
    uint8_t start_page;
    uint8_t end_page;

    int buflen;
};

#define PICO_SPINLOCK_ID_OLED		(5)

struct fun_oled_t {
	
	spin_lock_t		*lock;

};


extern int fun_oled_init (void);

extern void oled_horiz_scroll (uint8_t page, uint8_t speed);

extern int fun_oled_flush_area_string (
	uint8_t start_col, uint8_t end_col, uint8_t start_page, uint8_t end_page,
	char *str);

extern void fun_oled_flush_clock (char *clock);

extern void fun_oled_clear_screen (void);

#endif



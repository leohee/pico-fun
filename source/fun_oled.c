
#include "inc_file.h"


#define DEV_I2C_OLED		(&i2c0_inst)
#define PIN_OLED_SCL		(21)
#define PIN_OLED_SDA		(20)

#define WIDTH_FONT_8x6		(6)

const uint8_t font_8x6[][WIDTH_FONT_8x6] = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// sp
	{0x00, 0x00, 0x00, 0x2f, 0x00, 0x00},	// !
	{0x00, 0x00, 0x07, 0x00, 0x07, 0x00},	// "
	{0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14},	// #
	{0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12},	// $
	{0x00, 0x62, 0x64, 0x08, 0x13, 0x23},	// %
	{0x00, 0x36, 0x49, 0x55, 0x22, 0x50},	// &
	{0x00, 0x00, 0x05, 0x03, 0x00, 0x00},	// '
	{0x00, 0x00, 0x1c, 0x22, 0x41, 0x00},	// (
	{0x00, 0x00, 0x41, 0x22, 0x1c, 0x00},	// )
	{0x00, 0x14, 0x08, 0x3E, 0x08, 0x14},	// *
	{0x00, 0x08, 0x08, 0x3E, 0x08, 0x08},	// +
	{0x00, 0x00, 0x00, 0xA0, 0x60, 0x00},	// ,
	{0x00, 0x08, 0x08, 0x08, 0x08, 0x08},	// -
	{0x00, 0x00, 0x60, 0x60, 0x00, 0x00},	// .
	{0x00, 0x20, 0x10, 0x08, 0x04, 0x02},	// /
	{0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E},	// 0
	{0x00, 0x00, 0x42, 0x7F, 0x40, 0x00},	// 1
	{0x00, 0x42, 0x61, 0x51, 0x49, 0x46},	// 2
	{0x00, 0x21, 0x41, 0x45, 0x4B, 0x31},	// 3
	{0x00, 0x18, 0x14, 0x12, 0x7F, 0x10},	// 4
	{0x00, 0x27, 0x45, 0x45, 0x45, 0x39},	// 5
	{0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30},	// 6
	{0x00, 0x01, 0x71, 0x09, 0x05, 0x03},	// 7
	{0x00, 0x36, 0x49, 0x49, 0x49, 0x36},	// 8
	{0x00, 0x06, 0x49, 0x49, 0x29, 0x1E},	// 9
	{0x00, 0x00, 0x36, 0x36, 0x00, 0x00},	// :
	{0x00, 0x00, 0x56, 0x36, 0x00, 0x00},	// ;
	{0x00, 0x08, 0x14, 0x22, 0x41, 0x00},	// <
	{0x00, 0x14, 0x14, 0x14, 0x14, 0x14},	// =
	{0x00, 0x00, 0x41, 0x22, 0x14, 0x08},	// >
	{0x00, 0x02, 0x01, 0x51, 0x09, 0x06},	// ?
	{0x00, 0x32, 0x49, 0x59, 0x51, 0x3E},	// @
	{0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C},	// A
	{0x00, 0x7F, 0x49, 0x49, 0x49, 0x36},	// B
	{0x00, 0x3E, 0x41, 0x41, 0x41, 0x22},	// C
	{0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C},	// D
	{0x00, 0x7F, 0x49, 0x49, 0x49, 0x41},	// E
	{0x00, 0x7F, 0x09, 0x09, 0x09, 0x01},	// F
	{0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A},	// G
	{0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F},	// H
	{0x00, 0x00, 0x41, 0x7F, 0x41, 0x00},	// I
	{0x00, 0x20, 0x40, 0x41, 0x3F, 0x01},	// J
	{0x00, 0x7F, 0x08, 0x14, 0x22, 0x41},	// K
	{0x00, 0x7F, 0x40, 0x40, 0x40, 0x40},	// L
	{0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F},	// M
	{0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F},	// N
	{0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E},	// O
	{0x00, 0x7F, 0x09, 0x09, 0x09, 0x06},	// P
	{0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E},	// Q
	{0x00, 0x7F, 0x09, 0x19, 0x29, 0x46},	// R
	{0x00, 0x46, 0x49, 0x49, 0x49, 0x31},	// S
	{0x00, 0x01, 0x01, 0x7F, 0x01, 0x01},	// T
	{0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F},	// U
	{0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F},	// V
	{0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F},	// W
	{0x00, 0x63, 0x14, 0x08, 0x14, 0x63},	// X
	{0x00, 0x07, 0x08, 0x70, 0x08, 0x07},	// Y
	{0x00, 0x61, 0x51, 0x49, 0x45, 0x43},	// Z
	{0x00, 0x00, 0x7F, 0x41, 0x41, 0x00},	// [
	{0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55},	// 55
	{0x00, 0x00, 0x41, 0x41, 0x7F, 0x00},	// ]
	{0x00, 0x04, 0x02, 0x01, 0x02, 0x04},	// ^
	{0x00, 0x40, 0x40, 0x40, 0x40, 0x40},	// _
	{0x00, 0x00, 0x01, 0x02, 0x04, 0x00},	// '
	{0x00, 0x20, 0x54, 0x54, 0x54, 0x78},	// a
	{0x00, 0x7F, 0x48, 0x44, 0x44, 0x38},	// b
	{0x00, 0x38, 0x44, 0x44, 0x44, 0x20},	// c
	{0x00, 0x38, 0x44, 0x44, 0x48, 0x7F},	// d
	{0x00, 0x38, 0x54, 0x54, 0x54, 0x18},	// e
	{0x00, 0x08, 0x7E, 0x09, 0x01, 0x02},	// f
	{0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C},	// g
	{0x00, 0x7F, 0x08, 0x04, 0x04, 0x78},	// h
	{0x00, 0x00, 0x44, 0x7D, 0x40, 0x00},	// i
	{0x00, 0x40, 0x80, 0x84, 0x7D, 0x00},	// j
	{0x00, 0x7F, 0x10, 0x28, 0x44, 0x00},	// k
	{0x00, 0x00, 0x41, 0x7F, 0x40, 0x00},	// l
	{0x00, 0x7C, 0x04, 0x18, 0x04, 0x78},	// m
	{0x00, 0x7C, 0x08, 0x04, 0x04, 0x78},	// n
	{0x00, 0x38, 0x44, 0x44, 0x44, 0x38},	// o
	{0x00, 0xFC, 0x24, 0x24, 0x24, 0x18},	// p
	{0x00, 0x18, 0x24, 0x24, 0x18, 0xFC},	// q
	{0x00, 0x7C, 0x08, 0x04, 0x04, 0x08},	// r
	{0x00, 0x48, 0x54, 0x54, 0x54, 0x20},	// s
	{0x00, 0x04, 0x3F, 0x44, 0x40, 0x20},	// t
	{0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C},	// u
	{0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C},	// v
	{0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C},	// w
	{0x00, 0x44, 0x28, 0x10, 0x28, 0x44},	// x
	{0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C},	// y
	{0x00, 0x44, 0x64, 0x54, 0x4C, 0x44},	// z
	{0x14, 0x14, 0x14, 0x14, 0x14, 0x14},	// horiz lines
};

static void fill (uint8_t *buf, uint8_t fill)
{
	int i = 0;

    // fill entire buffer with the same byte
    for (i = 0; i < OLED_BUF_LEN; i++) {
        buf[i] = fill;
    }
};

void fill_page (uint8_t *buf, uint8_t fill, uint8_t page)
{
    // fill entire page with the same byte
    memset(buf + (page * OLED_WIDTH), fill, OLED_WIDTH);
};

// convenience methods for printing out a buffer to be rendered
// mostly useful for debugging images, patterns, etc
static void print_buf_page (uint8_t *buf, uint8_t page)
{
	int j = 0, k = 0;

    // prints one page of a full length (128x4) buffer
    for (j = 0; j < OLED_PAGE_HEIGHT; j++) {
        for (k = 0; k < OLED_WIDTH; k++) {
            printf("%u", (buf[page * OLED_WIDTH + k] >> j) & 0x01);
        }
        printf("\n");
    }
}

void print_buf_pages (uint8_t *buf)
{
	int i = 0;

    // prints all pages of a full length buffer
    for (i = 0; i < OLED_NUM_PAGES; i++) {
        printf("--page %d--\n", i);
        print_buf_page(buf, i);
    }
}

void print_buf_area (uint8_t *buf, struct render_area *area)
{
	int i = 0, j = 0, k = 0;

    // print a render area of generic size
    int area_width = area->end_col - area->start_col + 1;
    int area_height = area->end_page - area->start_page + 1; // in pages, not pixels

    for (i = 0; i < area_height; i++) {
        for (j = 0; j < OLED_PAGE_HEIGHT; j++) {
            for (k = 0; k < area_width; k++) {
//                printf("%u", (buf[i * area_width + k] >> j) & 0x01);
            }
//            printf("\n");
        }
    }
}

void calc_render_area_buflen (struct render_area *area)
{
    // calculate how long the flattened buffer will be for a render area
    area->buflen = (area->end_col - area->start_col + 1) * (area->end_page - area->start_page + 1);
}

void oled_send_cmd (uint8_t cmd)
{
    // I2C write process expects a control byte followed by data
    // this "data" can be a command or data to follow up a command

    // Co = 1, D/C = 0 => the driver expects a command
    uint8_t buf[2] = {0x80, cmd};
    i2c_write_blocking(DEV_I2C_OLED, (OLED_ADDR & OLED_WRITE_MODE), buf, 2, false);
}

void oled_send_buf (uint8_t *buf, uint16_t len, int buflen)
{
    // in horizontal addressing mode, the column address pointer auto-increments
    // and then wraps around to the next page, so we can send the entire frame
    // buffer in one gooooooo!

    // copy our frame buffer into a new buffer because we need to add the control byte
    // to the beginning

    // TODO find a more memory-efficient way to do this..
    // maybe break the data transfer into pages?

	int i = 1;
    uint8_t *temp_buf = malloc(buflen + 1);
	if (NULL != temp_buf) {
		memset(temp_buf, 0x00, buflen+1);

		if (len <= buflen) {
		    for (i = 1; i < len + 1; i++) {
		        temp_buf[i] = buf[i - 1];
		    }
		} else {
		    for (i = 1; i < buflen + 1; i++) {
		        temp_buf[i] = buf[i - 1];
		    }
		}

	    // Co = 0, D/C = 1 => the driver expects data to be written to RAM
	    temp_buf[0] = 0x40;
	    i2c_write_blocking(DEV_I2C_OLED, (OLED_ADDR & OLED_WRITE_MODE), temp_buf, buflen + 1, false);

	    free(temp_buf);
	}
}

void oled_init_param (void)
{
    // some of these commands are not strictly necessary as the reset
    // process defaults to some of these but they are shown here
    // to demonstrate what the initialization sequence looks like

    // some configuration values are recommended by the board manufacturer

    oled_send_cmd(OLED_SET_DISP | 0x00); // set display off

    /* memory mapping */
    oled_send_cmd(OLED_SET_MEM_ADDR); // set memory address mode
    oled_send_cmd(0x00); // horizontal addressing mode

    /* resolution and layout */
    oled_send_cmd(OLED_SET_DISP_START_LINE); // set display start line to 0

    oled_send_cmd(OLED_SET_SEG_REMAP | 0x01); // set segment re-map
    // column address 127 is mapped to SEG0

    oled_send_cmd(OLED_SET_MUX_RATIO); // set multiplex ratio
    oled_send_cmd(OLED_HEIGHT - 1); // our display is only 32 pixels high

    oled_send_cmd(OLED_SET_COM_OUT_DIR | 0x08); // set COM (common) output scan direction
    // scan from bottom up, COM[N-1] to COM0

    oled_send_cmd(OLED_SET_DISP_OFFSET); // set display offset
    oled_send_cmd(0x00); // no offset

    oled_send_cmd(OLED_SET_COM_PIN_CFG); // set COM (common) pins hardware configuration
    oled_send_cmd(0x02); // manufacturer magic number

    /* timing and driving scheme */
    oled_send_cmd(OLED_SET_DISP_CLK_DIV); // set display clock divide ratio
    oled_send_cmd(0x80); // div ratio of 1, standard freq

    oled_send_cmd(OLED_SET_PRECHARGE); // set pre-charge period
    oled_send_cmd(0xF1); // Vcc internally generated on our board

    oled_send_cmd(OLED_SET_VCOM_DESEL); // set VCOMH deselect level
    oled_send_cmd(0x30); // 0.83xVcc

    /* display */
    oled_send_cmd(OLED_SET_CONTRAST); // set contrast control
    oled_send_cmd(0xFF);

    oled_send_cmd(OLED_SET_ENTIRE_ON); // set entire display on to follow RAM content

    oled_send_cmd(OLED_SET_NORM_INV); // set normal (not inverted) display

    oled_send_cmd(OLED_SET_CHARGE_PUMP); // set charge pump
    oled_send_cmd(0x14); // Vcc internally generated on our board

    oled_send_cmd(OLED_SET_SCROLL | 0x00); // deactivate horizontal scrolling if set
    // this is necessary as memory writes will corrupt if scrolling was enabled

    oled_send_cmd(OLED_SET_DISP | 0x01); // turn display on
}

void render (uint8_t *buf, uint16_t len, struct render_area *area)
{
    // update a portion of the display with a render area
    oled_send_cmd(OLED_SET_COL_ADDR);
    oled_send_cmd(area->start_col);
    oled_send_cmd(area->end_col);

    oled_send_cmd(OLED_SET_PAGE_ADDR);
    oled_send_cmd(area->start_page);
    oled_send_cmd(area->end_page);

    oled_send_buf(buf, len, area->buflen);
}

void oled_string (char *str, uint8_t *buf)
{
	int i = 0, j = 0;
	uint8_t ch = 0;

	while (str[i] != '\0') {
		ch = str[i] - ' ';
		for (j = 0; j < WIDTH_FONT_8x6; j++) {
			buf[i*WIDTH_FONT_8x6+j] = font_8x6[ch][j];
//			printf("0x%02X, ", buf[i*WIDTH_FONT_8x6+j]);
		}
		i++;
//		printf("\n");
	}
}

void oled_horiz_scroll (uint8_t page, uint8_t speed)
{
	if ((page < OLED_NUM_PAGES)&&(speed < 10)) {
	    oled_send_cmd(OLED_SET_HORIZ_SCROLL | 0x00);
	    oled_send_cmd(0x00); // dummy byte
	    oled_send_cmd(page); // start page 0
	    oled_send_cmd(speed); // time interval
	    oled_send_cmd(page); // end page 3
	    oled_send_cmd(0x00); // dummy byte
	    oled_send_cmd(0xFF); // dummy byte

	    // let's goooo!
	    oled_send_cmd(OLED_SET_SCROLL | 0x01);
	}


}

// col [0 ~ 127]; page [0 ~ 3]
int fun_oled_flush_area_string (
	uint8_t start_col, uint8_t end_col, uint8_t start_page, uint8_t end_page,
	char *str)
{
	int len = strlen(str);

	if ((end_col >= OLED_WIDTH)||(end_page >= OLED_NUM_PAGES)
		||(start_col > end_col)||(start_page > end_page)) {
		printf("error position : col %d %d , page %d %d.\n", 
			start_col, end_col, start_page, end_page);
		return -1;
	}

    struct render_area frame_area = {
    	start_col: start_col,
		end_col : end_col,
		start_page : start_page,
		end_page : end_page};

    calc_render_area_buflen(&frame_area);


	uint8_t *buf = malloc(len*WIDTH_FONT_8x6+1);
	if (buf == NULL) {
		printf("error malloc.\n");
		return -1;
	}
	memset(buf, 0x00, len*WIDTH_FONT_8x6+1);

	oled_string(str, buf);

	render(buf, len*WIDTH_FONT_8x6, &frame_area);

}

void fun_oled_flush_clock (char *clock)
{
	fun_oled_flush_area_string(0, OLED_WIDTH-3, 3, 3, clock);
}

void fun_oled_clear_screen (void)
{
    // initialize render area for entire frame (128 pixels by 4 pages)
    struct render_area frame_area = {
    	start_col: 0,
		end_col : OLED_WIDTH - 1,
		start_page : 0,
		end_page : OLED_NUM_PAGES - 1};

    calc_render_area_buflen(&frame_area);

    // zero the entire display
    uint8_t buf[OLED_BUF_LEN] = {0x00};
	memset(buf, 0, OLED_BUF_LEN);

    render(buf, OLED_BUF_LEN, &frame_area);

//    oled_send_cmd(0xA5); // ignore RAM, all pixels on
//    sleep_ms(500);
//    oled_send_cmd(0xA4); // go back to following RAM
//    sleep_ms(500);
}

int fun_oled_init (void)
{
    i2c_init(DEV_I2C_OLED, 400 * 1000);
    gpio_set_function(PIN_OLED_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PIN_OLED_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(PIN_OLED_SDA);
    gpio_pull_up(PIN_OLED_SCL);

    oled_init_param();

    fun_oled_clear_screen();

    return 0;
}



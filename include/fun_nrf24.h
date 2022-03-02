#ifndef __FUN_NRF24_H__
#define __FUN_NRF24_H__

#define SPI_PORT  spi0 // Hardware SPI instance

#define PIN_SCK   2 // SPI Clock
#define PIN_MOSI  3 // SPI Data Input
#define PIN_MISO  4 // SPI Data Output
#define PIN_CSN   5 // SPI Chip Select
#define PIN_CE    6 // Chip Enable activates Rx or Tx mode
#define PIN_IRQ   7 // IRQ (active-low)


// GPIO pin direction
typedef enum {
	LOW, 
	HIGH
} pin_direction_t;

#define LSB					(0)		// LSB in 5 byte address array (PRX_ADDR_P0[LSB])

// Bytes in data buffer for read/write over SPI
#define ONE_BYTE			(1)
#define TWO_BYTES			(2)
#define THREE_BYTES			(3) 
#define FOUR_BYTES			(4)
#define FIVE_BYTES			(5)

// Set transceiver (XCVR) mode
typedef enum {
	TX_MODE,
	RX_MODE
} xcvr_mode_t;

// Individual PTX ID, which can correspond to the relevant PRX data pipe
typedef enum {
	PTX_0,
	PTX_1,
	PTX_2,
	PTX_3,
	PTX_4,
	PTX_5
} ptx_id_t;

// FIFO_STATUS register TX & RX FIFO full/empty flags
typedef enum {
	RX_EMPTY,
	RX_FULL,
	TX_EMPTY = 4,
	TX_FULL
} fifo_status_t;

// Interrupt bit asserted in STATUS register
typedef enum {
	NONE_ASSERTED,
	RX_DR_ASSERTED,
	TX_DS_ASSERTED,
	MAX_RT_ASSERTED
} asserted_bit_t;

/**
 * Used to format message data passed between each PTX
 * and the PRX though the tx_message and rx_message functions.
 */
typedef struct { 
	ptx_id_t ptx_id;
	uint8_t value : 8;
} payload_t;


/**
 * The PRX STATUS register bits 1:3 specify the data pipe number 
 * the payload was was received on. payload_prx_t stores this data 
 * pipe number.
 */
typedef struct {
	ptx_id_t ptx_id : 8;
	uint8_t data_pipe : 8;
	uint8_t value : 8;
} payload_prx_t;

/**
 * Used to store a payload_t argument for the tx_message and rx_message 
 * functions. The union allows access to bytes within the payload_t in 
 * the form of an array. Data received by the PRX can be read over SPI 
 * into this buffer using spi_read_blocking. Data for transmission by 
 * a PTX can be written over SPI using the spi_write_blocking function.
 */
typedef union {
	payload_t payload;
	uint8_t buffer[sizeof(payload_t)];
} spi_payload_t;

// Initialise SPI and GPIO pins
extern void init_spi (void);


// Initial config when device first powered
extern void init_nrf24 (void);

// Config PTX specific registers
extern void init_nrf24_ptx_registers (uint8_t *address);

// Config PRX specific registers
extern void init_nrf24_prx_registers (void);

// Data pipes to enable auto-acknowledge
extern void en_auto_acknowledge (uint8_t data_pipes);

// Activate RX_MODE or TX_MODE
extern void set_mode (xcvr_mode_t transceiver_mode);

// Tx data
void tx_message (payload_t *msg);

// Rx data
void rx_message (payload_prx_t *msg);

// check which interrupt bit is asserted in STATUS register
uint8_t check_irq_bit (void);

// Check if RX FIFO is empty
uint8_t check_fifo_status (fifo_status_t bit_flag);

// printf register values
void debug_registers (void);

// printf RX_ADDR_P0 - RX_ADDR_P5 & TX_ADDR register values
void debug_rx_address_pipes (uint8_t reg);

extern void fun_nrf24_config_pipe_address (uint8_t mode);

extern int fun_nrf24_init (void);

extern void fun_nrf24_rcv_loop (void);

extern void fun_nrf24_snd_loop (void);

//#define PICO_SPINLOCK_ID_NRF24		(6)

typedef struct {
	void *func;
} queue_entry_t;

struct fun_nrf24_t {
	uint8_t			mode;

	uint8_t			ready;

	queue_t			irq_queue;

	struct mutex	mutex_nrf;
};


#endif


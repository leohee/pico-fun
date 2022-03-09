#ifndef __FUN_ESP_H__
#define __FUN_ESP_H__

#define UART_ESP			uart0
#define ESP_BAUDRATE		115200
#define DATA_BITS         8
#define STOP_BITS         1
#define PARITY            UART_PARITY_NONE

#define UART_TX_ESP_PIN		0
#define UART_RX_ESP_PIN		1

struct fun_esp_t {

};

extern void esp_test (void);

extern void fun_esp_init (void);


#endif



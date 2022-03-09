
#include "inc_file.h"

char SSID[] = "SSID";
char password[] = "SSID_PASS";
char ServerIP[] = "SERVER_IP";
char Port[] = "SERVER_PORT";
char uart_command[50] = "";
char buf[256] = {0};


bool sendCMD (const char *cmd, const char *act)
{
    int i = 0;
    uint64_t t = 0;

	LOG_DBG("-> %s", cmd);

    uart_puts(UART_ESP, cmd);
    uart_puts(UART_ESP, "\r\n");

    t = time_us_64();
    while (time_us_64() - t < 2500 * 1000) {
        while (uart_is_readable_within_us(UART_ESP, 2000)) {
            buf[i++] = uart_getc(UART_ESP);
        }

        if (i > 0) {
            buf[i] = '\0';
            LOG_DBG("<- %s", buf);
            if (strstr(buf, act) != NULL) {
                return true;
            } else {
                i = 0;
            }
        }
    }

    return false;
}

static void connectToWifi (void)
{
    sendCMD("AT", "OK");
    sendCMD("AT+CWMODE=3", "OK");
    sprintf(uart_command, "AT+CWJAP=\"%s\",\"%s\"", SSID, password);
    sendCMD(uart_command, "OK");
}

/// Send sensor values to REST api using TCP connection
bool send_sensor_values(const char *sensorName, const char *humidity, const char *temperature)
{
    // Open connection
    sprintf(uart_command, "AT+CIPSTART=\"TCP\",\"%s\",%s", ServerIP, Port);
    sendCMD(uart_command, "OK");

    // Send data
    sendCMD("AT+CIPMODE=1", "OK");
    sleep_ms(1000);
    sendCMD("AT+CIPSEND", ">");
    sleep_ms(2000);

    char data[100];
    sniprintf(data, sizeof(data), "{\"sensor\":\"%s\",\"temperature\":\"%s\", \"humidity\":\"%s\"}", sensorName, 
humidity, temperature);
    int data_size = strlen(data);
    char post[] = "POST /api/sensor-values HTTP/1.1\r\n";

    char host[100];
    snprintf(host, sizeof(host), "Host: %s\r\n", ServerIP);
    char content_type[] = "Content-Type: application/json\r\n";
    char accept[] = "Accept: application/json\r\n";
    char content_length[100];
    sniprintf(content_length, sizeof(content_length), "Content-Length: %d\r\n", data_size);

    snprintf(buf, sizeof(buf), "%s%s%s%s%s\r\n%s", post, host, content_type, accept, content_length, data);
    printf(buf);
    uart_puts(UART_ESP, buf);

    sleep_ms(5000);            // Seems like this is critical
    uart_puts(UART_ESP, "+++"); // Look for ESP docs

    // Close connection
    sleep_ms(1000);
    sendCMD("AT+CIPCLOSE", "OK");
    sleep_ms(1000);
    sendCMD("AT+CIPMODE=0", "OK");

    return true;
}

void esp_test (void)
{
	uart_puts(UART_ESP, "+++");

    sleep_ms(1000);

    while (uart_is_readable(UART_ESP)) {
        uart_getc(UART_ESP);
    }

    sleep_ms(2000);

    connectToWifi(); 
    sleep_ms(2000);

    // Get the IP address of the ESP
    sendCMD("AT+CIFSR", "OK"); // ASK IP

	send_sensor_values("test", "80.1", "22.5");
}


void fun_esp_init (void)
{
	uart_init(UART_ESP, ESP_BAUDRATE);

    gpio_set_function(UART_TX_ESP_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_ESP_PIN, GPIO_FUNC_UART);


    gpio_pull_up(UART_RX_ESP_PIN);

    uart_set_translate_crlf(UART_ESP, false);
    uart_set_hw_flow(UART_ESP, false, false);
    uart_set_format(UART_ESP, DATA_BITS, STOP_BITS, PARITY);
    uart_set_fifo_enabled(UART_ESP, true);

}



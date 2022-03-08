
#include "inc_file.h"



#if defined(LOG_ENABLE)

char *log_buffer = ((void *)0);
unsigned int log_buffer_len = 0;
void log_hook_default(const char *str)
{
	(void)(str);
}

void (*log_hook)(const char *str) = log_hook_default;
void log_init (char *buff, uint buff_len, void (*hook)(const char *))
{
	log_hook = hook;
	log_buffer = buff;
	log_buffer_len = buff_len;
}

int printk (const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	(void)vsnprintf(log_buffer, log_buffer_len, format, ap);
	va_end(ap);
	log_hook(log_buffer);

	return 0;
}

int printk_hex (const uint8_t *buff, uint count)
{
	static const char hex[] = "0123456789ABCDEF";
	uint i = 0, j = 0;
	char str[16] = {0};
	char str_val[75] = {0};
	uint index = 0;
	uint str_index = 0;
	uint cnt = (count+15)>>4;

	for (i = 0; i < cnt; i++) {
		index = 0;
		str_index = 0;
		str_val[index++] = hex[(i & 0xF000) >> 12];
		str_val[index++] = hex[(i & 0xF00) >> 8];
		str_val[index++] = hex[(i & 0xF0) >> 4];
		str_val[index++] = hex[i & 0xF];
		str_val[index++] = ' ';
		str_val[index++] = ' ';

		for (j = 0; j < 16; j++) {
			if (j + (i << 4) < count) {
				str_val[index++] = hex[(buff[j + (i << 4)] & 0xF0) >> 4];
				str_val[index++] = hex[buff[j + (i << 4)] & 0xF];
				str_val[index++] = ' ';
				if ((buff[j] >= 0x20) && (buff[j] <= 0x7E)) {
					str[str_index++] = buff[j];
				} else {
					str[str_index++] = '.';
				}
			} else {
				str_val[index++] = ' ';
				str_val[index++] = ' ';
				str_val[index++] = ' ';
				str[str_index++] = ' ';
			}
		}
		str_val[index++] = ' ';
		str_val[index++] = ' ';
		memcpy(&str_val[index], str, str_index);
		index += str_index;
		str_val[index++] = '\n';
		str_val[index++] = '\0';
		log_hook(str_val);
	}

	return 0;
}

char glog_buff[512] = {0};

static void fun_log_out (const char *str)
{
	printf("%s", str);
}

void fun_log_init (void)
{
	log_init(glog_buff, sizeof(glog_buff), fun_log_out);
}

#else

void fun_log_init (void)
{
	// nothing
}

#endif





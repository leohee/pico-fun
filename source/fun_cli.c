
#include "inc_file.h"


#define CLI_TOKENS_MAX		(8)

#define ASCII_EOT 4
#define ASCII_ENQ 5
#define ASCII_BS 8
#define ASCII_TAB 9
#define ASCII_LF 10
#define ASCII_VT 11
#define ASCII_FF 12
#define ASCII_CR 13
#define ASCII_SPC 32
#define ASCII_DEL 127

#define ASCII_NOT_CTRL(X)                                                      \
  ((X != ASCII_EOT && X != ASCII_ENQ && X != ASCII_LF && X != ASCII_FF &&      \
    X != ASCII_CR && X != ASCII_DEL && X != ASCII_BS))

#define ASCII_ISSPACE(X)                                                       \
  ((X == ASCII_SPC || X == ASCII_TAB || X == ASCII_LF || X == ASCII_VT ||      \
    X == ASCII_FF || X == ASCII_CR))

#define ASCII_IS_FMT_CHAR(X)                                                   \
  ((X == 'i' || X == 'd' || X == 'o' || X == 'x' || X == 'f' || X == 'c' ||    \
    X == 's'))

static struct cli_option_t cli_options[];
extern int len_cli_cmd;


static void cli_usage (int argc, const struct cli_arg_t *args)
{
	int i = 0;
	printf("cmd\tdesc\t\t\t\tex.\n");
	for (i = 0; i < len_cli_cmd; i++) {
		if (cli_options[i].name != NULL) {
			printf("%s\t%s\t\t\t%s\n", cli_options[i].name,
				cli_options[i].help_msg,
				cli_options[i].argc ? cli_options[i].example : "");
		}
	}
}

static void cli_clear_buffer (void)
{
	memset(gFUN.cli.rx_buf, 0x00, CLI_RX_BUFFERSIZE);
	gFUN.cli.rx_idx = 0;
}

static int cli_push_args (char *str, char **tokens)
{
	if (NULL == str) {
		return 0;
	}

	int nargs = 0;

	// catch 1st arg
	if (!ASCII_ISSPACE(*str)) {
		tokens[nargs++] = str;
	}

	// run through the args
	while (*str != '\0') {
		if (ASCII_ISSPACE(*str) && !ASCII_ISSPACE(*(str + 1))) {
			tokens[nargs++] = (char *)(str + 1);
			*str = '\0';
		}

		str++;
	}

	return nargs;
}

static int cli_tokenize_options (char *str, char **tokens)
{
	if (NULL == str) {
		return 0;
	}

	int nopts = 0;
	char delimiter = 0;

	// run through the format string
	while (*str != '\0') {
		delimiter = *(str - 1);
		if (ASCII_IS_FMT_CHAR(*str) && (delimiter == '%')) {
			tokens[nopts++] = str;
		}

		str++;
	}

	return nopts;
}

static char cli_parse_option_type (const char *opttypes, int argc, int optind, char **opts)
{
	if (argc == cli_tokenize_options((char *)opttypes, (char **)opts)) {
		return *opts[optind];
	}

	return -1;
}

static void cli_catch_arg_value (int argc, char **argv, 
	struct cli_option_t *pOPT, struct cli_arg_t *pARGS)
{
	int idx = 0;
	optind = 0;
	struct cli_arg_t *pARG = pARGS;

	while (1) {
		int opt_arg = 0;
		opt_arg = getopt(argc, argv, pOPT->optstring);
		if (opt_arg == -1 || opt_arg == '?') {
			break;
		}

//		printf("%c : ", opt_arg&0xFF);

		char *opts[CLI_TOKENS_MAX] = {0};
		char opttype = cli_parse_option_type(pOPT->opttypes, pOPT->argc, idx, opts);
		if (opttype != -1) {
			pARG = pARGS+idx;

			pARG->opt = opt_arg&0xFF;

			switch (opttype) {
			case 's':
				pARG->type = opttype;
				pARG->value.arg_char = optarg;
//				printf("%s\n", pARG->value.arg_char);
				idx++;
				break;
			case 'i':
				pARG->type = opttype;
				pARG->value.arg_int = atoi(optarg);
//				printf("%d\n", pARG->value.arg_int);
				idx++;
				break;
			case 'f':
				pARG->type = opttype;
				pARG->value.arg_float = atof(optarg);
//				printf("%f\n", pARG->value.arg_float);
				idx++;
				break;
			case 'c':
				pARG->type = opttype;
				pARG->value.arg_char[0] = optarg[0];
				pARG->value.arg_char[1] = 0x00;
//				printf("%c\n", pARG->value.arg_char[0]);
				idx++;
				break;
			default:
				printf("other type : %c\n", opttype); // ASCII_IS_FMT_CHAR idoxfcs
				break;
			}
		}
	}

}

static int cli_parse_string (char *str)
{
	int i = 0;
	char *argv[CLI_TOKENS_MAX] = {0};
	struct cli_option_t *pOPT = NULL;

	int argc = cli_push_args(str, (char **)argv);

	for (i = 0; i < len_cli_cmd; i++) {
		pOPT = &cli_options[i];

		if (pOPT->name == NULL) {
			break;
		}

		if (strcmp(argv[0], pOPT->name) == 0) {
			if (pOPT->argc) {
				if ((argc > 1)&&(argc == (pOPT->argc + 1))) {
					struct cli_arg_t opt_list[CLI_TOKENS_MAX];
					memset(&opt_list, 0, sizeof(struct cli_arg_t)*CLI_TOKENS_MAX);

					cli_catch_arg_value(argc, argv, pOPT, opt_list);

					if (pOPT->callback) {
						pOPT->callback(argc, opt_list);
						printf("$ ");
					}

					return 0;
				} else {
					LOG_WRN("%s ex. %s", pOPT->help_msg, pOPT->example);
					return -1;
				}
			} else {
				if (argc == 1) {
					if (pOPT->callback) {
						pOPT->callback(argc, NULL);
						printf("$ ");
					}

					return 0;
				} else {
					LOG_WRN("%s : %s", pOPT->name, pOPT->help_msg);
					return -1;
				}
			}
		}

/*
		if (strcmp(argv[0], pOPT->name) == 0) {
			if ((argc > 1) && (argc == (pOPT->argc + 1))) {
				struct cli_arg_t opt_list[CLI_TOKENS_MAX];
				memset(&opt_list, 0, sizeof(struct cli_arg_t)*CLI_TOKENS_MAX);

				cli_catch_arg_value(argc, argv, pOPT, opt_list);

				if (pOPT->callback) {
					pOPT->callback(argc, opt_list);
					printf("$ ");
				}

				return 0;
			} else if (argc == 1) {
				if (pOPT->callback) {
					pOPT->callback(argc, NULL);
					printf("$ ");
				}

				return 0;
			}

			LOG_WRN("Invalid arguments.\n$ ");

			return -1;
	    }
*/
	}

	LOG_WRN("Not found cmd : '%s'\n$ ", argv[0]);

	return -1;
}



int cli_catch_input (void)
{
//	int rc = getchar();
	int rc = getchar_timeout_us(100);
	if (rc == PICO_ERROR_TIMEOUT) {
		return -1;
	}

	uint8_t ch = (rc & 0xff);

	if (gFUN.cli.rx_idx < CLI_RX_BUFFERSIZE) {
		if (ASCII_NOT_CTRL(ch)) {		// ignore unused ASCII codes
			gFUN.cli.rx_buf[gFUN.cli.rx_idx++] = (char)ch;
			putchar_raw(ch);
		} else if ((ch == ASCII_BS)||(ch == ASCII_DEL)) { // backspace or delete
			gFUN.cli.rx_buf[gFUN.cli.rx_idx] = 0;
			if (gFUN.cli.rx_idx >= 1) {
				gFUN.cli.rx_idx--;
			}
			putchar_raw(ch);
		} else if ((ch == ASCII_LF)||(ch == ASCII_CR)) { // enter
			if (gFUN.cli.rx_idx == 0) {
				printf("\n$ ");
				return 1;
			}
			printf("\n");
//			printf("%s\n", gFUN.cli.rx_buf);
			cli_parse_string(gFUN.cli.rx_buf);
			cli_clear_buffer();
		}
	} else {
		cli_clear_buffer();
	}

	return 0;
}


void cli_test_args (int argc, const struct cli_arg_t *args)
{
  if (args) {
    for (int i = 0; i < (argc - 1); i++) {
      switch (args[i].type) {
      case 's':
        printf("get string : '%s'\n", args[i].value.arg_char);
        break;
      case 'i':
        printf("get int : '%d'\n", args[i].value.arg_int);
        break;
      case 'f':
        printf("get float : '%f'\n", args[i].value.arg_float);
        break;
      default:
        break;
      }
    }
  }
}

void cli_exit (int argc, const struct cli_arg_t *args)
{
	LOG_WRN("Bye\n");
	gFUN.wdt.quire_reboot = true;
}

void cli_clear (int argc, const struct cli_arg_t *args)
{
	putchar_raw(ASCII_FF); // clear terminal
}

void cli_wifi_test (int argc, const struct cli_arg_t *args)
{
	esp_test();
}

void cli_flash (int argc, const struct cli_arg_t *args)
{
	if ((NULL != args)&&(argc == 2)) {
		if ('w' == args[0].opt) {
			fun_flash_test();
		} else if ('r' == args[0].opt) {
			fun_flash_read();
		}
	}
}

void cli_version (int argc, const struct cli_arg_t *args)
{
	printf("BoardID : %s\n", gFUN.str_boardid);
	printf("Pico %s built @ %s %s\n", PICO_SDK_VERSION_STRING, 
		gFUN.build_date, gFUN.build_time);
}

void cli_datetime (int argc, const struct cli_arg_t *args)
{
	rtc_get_datetime(&gFUN.t);
	datetime_format(gFUN.tick.str_clock, SIZE_TIMESTAMP, &gFUN.t);
	LOG_INF("%s", gFUN.tick.str_clock);
}

void cli_set_nrf24mode (int argc, const struct cli_arg_t *args)
{
	if ((NULL != args)&&(argc == 2)) {
		if (args[0].type == 'c') {
			if ('R' == args[0].value.arg_char[0]) {
				fun_nrf24_config_pipe_address(RX_MODE);
			} else if ('T' == args[0].value.arg_char[0]) {
				fun_nrf24_config_pipe_address(TX_MODE);
			} else {
				LOG_INF("nrf -m[R|T]\n");
			}
		}
	}
}

static struct cli_option_t cli_options[] = {
	{"help",	NULL, NULL, 0, cli_usage, "show this help.", NULL},
//	{"s",		"t:", "%i", 1, cli_test_args, "single arg", "s -t1"},
//	{"d",		"t:v:", "%i%f", 2, cli_test_args, "double args", "d -t2 -v0.1"},
	{"test",	"t:v:j:", "%i%f%s", 3, cli_test_args, "triple args", "test -t3 -v0.2 -jabcdef"},
	{"nrf",		"m:", "%c", 1, cli_set_nrf24mode, "set nrf24 mode.", "\"nrf -m[R|T]\""},
	{"wifi_test",	0, 0, 0, cli_wifi_test, "esp wifi test", NULL},
	{"flash",	"w:r:", "%i", 1, cli_flash, "parameter flash.", "\"flash <-r0|-w0>\""},
	{"reboot",	0, 0, 0, cli_exit, "reboot device.", NULL},
	{"date",	0, 0, 0, cli_datetime, "show current date time.", NULL},
	{"ver",		0, 0, 0, cli_version, "show version.", NULL},
	{NULL,		NULL, NULL, 0, NULL, NULL, NULL} // sentinel
};

int len_cli_cmd = sizeof(cli_options)/sizeof(cli_options[0]);

void fun_cli_init (void)
{
	printf("$ ");

}







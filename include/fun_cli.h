#ifndef __FUN_CLI_H__
#define __FUN_CLI_H__


typedef union {
	char		*arg_char;
	int			arg_int;
	float		arg_float;
} argument_t;

struct cli_arg_t {
	char				opt;
	char				type;
	argument_t			value;
};

typedef void (*cmd_cb)(int argc, const struct cli_arg_t *args);

struct cli_option_t {
	const char			*name;
	const char			*optstring;
	const char			*opttypes;
	int					argc;
	cmd_cb				callback;
	const char			*help_msg;
	const char			*example;
};

#define CLI_RX_BUFFERSIZE		(255)

struct fun_cli_t {

	char				rx_buf[CLI_RX_BUFFERSIZE];
	uint8_t				rx_idx;
};


extern int cli_catch_input (void);


extern void fun_cli_init (void);



#endif



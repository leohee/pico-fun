#ifndef __FUN_CLI_H__
#define __FUN_CLI_H__



struct cli_parser_cmd_option;
struct cli_parser_parsed_arg;

typedef void (*command_callback_t)(int argc, const struct cli_parser_parsed_arg *args);

typedef union {
	char		*argument_s;
	int			argument_i;
	float		argument_f;
} cli_parsed_arg_t;

struct cli_parser_cmd_option {
	const char	*name;
	const char	*help_msg;
	const char	*optstring;
	const char	*optypes;
	int			argc;
	command_callback_t		callback;
};

struct cli_parser_parsed_arg {
	char		type;
	cli_parsed_arg_t		value;
};




extern void cli_parser_proc (void);

extern void fun_cli_init (void);






#endif




#ifndef __FUN_LOG_H__
#define __FUN_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif


#define LOG_ENABLE

#define LOG_CONFIG_LEVEL 4
#define LOG_CONFIG_COLOR
#define LOG_CONFIG_TAGS
#define LOG_CONFIG_NEWLINE


#define LOG_LEVEL_ASSERT 		0
#define LOG_LEVEL_ERROR 		1
#define LOG_LEVEL_WARNING 		2
#define LOG_LEVEL_INFO 			3
#define LOG_LEVEL_DEBUG 		4

#if !defined(LOG_CONFIG_LEVEL)
#define LOG_LEVEL LOG_LEVEL_DEBUG
#else
#define LOG_LEVEL LOG_CONFIG_LEVEL
#endif


#if defined(LOG_ENABLE)
extern int printk (const char *format, ...);

extern void (*log_hook)(const char *str);

extern void log_init (char *buff, uint buff_len, void (*hook)(const char *));

extern int printk_hex (uint8_t *buff, uint count);

#define LOG_COLOR_NONE    		""
#define LOG_COLOR_OFF     		"\x1B[0m"
#define LOG_COLOR_RED     		"\x1B[0;31m"
#define LOG_COLOR_LIGHT_RED     "\x1B[1;31m"
#define LOG_COLOR_GREEB     	"\x1B[0;32m"
#define LOG_COLOR_LIGHT_GREEN   "\x1B[1;32m"
#define LOG_COLOR_YELLOW  		"\x1B[0;33m"
#define LOG_COLOR_LIGHT_YELLOW  "\x1B[1;33m"
#define LOG_COLOR_BLUE  		"\x1B[0;34m"
#define LOG_COLOR_LIGHT_BLUE  	"\x1B[1;34m"
#define LOG_COLOR_MAGENTA  		"\x1B[0;35m"
#define LOG_COLOR_LIGHT_MAGENTA	"\x1B[1;35m"
#define LOG_COLOR_CYAN  		"\x1B[0;36m"
#define LOG_COLOR_LIGHT_CYAN	"\x1B[1;36m"

#if defined(LOG_CONFIG_TAGS)
#define LOG_TAG_ASS				"[A] "
#define LOG_TAG_ERR 			"[E] "
#define LOG_TAG_WRN 			"[W] "
#define LOG_TAG_INF 			"[I] "
#define LOG_TAG_DBG 			"[D] "
#else
#define LOG_TAG_ASS 			""
#define LOG_TAG_ERR 			""
#define LOG_TAG_WRN 			""
#define LOG_TAG_INF 			""
#define LOG_TAG_DBG 			""
#endif


#if !defined(LOG_CONFIG_ASS_COLOR)
#define LOG_TAG_ASS_COLOR			LOG_COLOR_LIGHT_MAGENTA
#else
#define LOG_TAG_ASS_COLOR			LOG_CONFIG_ASS_COLOR
#endif

#if !defined(LOG_CONFIG_ERR_COLOR)
#define LOG_TAG_ERR_COLOR			LOG_COLOR_LIGHT_RED
#else
#define LOG_TAG_ERR_COLOR			LOG_CONFIG_ERR_COLOR
#endif

#if !defined(LOG_CONFIG_WRN_COLOR)
#define LOG_TAG_WRN_COLOR			LOG_COLOR_LIGHT_YELLOW
#else
#define LOG_TAG_WRN_COLOR			LOG_CONFIG_WRN_COLOR
#endif

#if !defined(LOG_CONFIG_INF_COLOR)
#define LOG_TAG_INF_COLOR			LOG_COLOR_LIGHT_BLUE
#else
#define LOG_TAG_INF_COLOR			LOG_CONFIG_INF_COLOR
#endif

#if !defined(LOG_CONFIG_DBG_COLOR)
#define LOG_TAG_DBG_COLOR			LOG_COLOR_LIGHT_GREEN
#else
#define LOG_TAG_DBG_COLOR			LOG_COLOR_LIGHT_COLOR
#endif

#if !defined(LOG_CONFIG_DBG_HEX_COLOR)
#define LOG_TAG_DBG_HEX_COLOR		LOG_COLOR_NONE
#else
#define LOG_TAG_DBG_HEX_COLOR		LOG_COLOR_DBG_HEX_COLOR
#endif


#if !defined(LOG_CONFIG_NEWLINE)
#define LOG_NEWLINE ""
#else
#define LOG_NEWLINE "\n"
#endif

#if defined(LOG_CONFIG_COLOR)
#define LOG_CALL_TPYE(tag, tag_color, format, ...)	\
	printk("%s%s%s(%d): " format "%s" LOG_NEWLINE,	\
	       tag_color, tag, __func__, __LINE__, ##__VA_ARGS__, LOG_COLOR_OFF)

#define LOG_CALL_TPYE0(color) printk("%s" color)
#else
#define LOG_CALL_TPYE(tag, tag_color, format, ...)	\
	printk("%s%s%s(%d): " format "%s" LOG_NEWLINE,	\
	       LOG_COLOR_NONE, tag, __func__, __LINE__, ##__VA_ARGS__, LOG_COLOR_NONE)

#define LOG_CALL_TPYE0(color) { ; }
#endif


#define LOG_COLOR(tag, tag_color, format, ...) LOG_CALL_TPYE(tag, tag_color, format, ##__VA_ARGS__)

#if (LOG_LEVEL >= LOG_LEVEL_ASSERT)
#define LOG_ASS(EX) \
	if(!(EX)) \
	{ \
		LOG_COLOR(LOG_TAG_ASS, LOG_TAG_ASS_COLOR, "assert: '" #EX "' failed"); \
	}
#endif

#if (LOG_LEVEL >= LOG_LEVEL_ERROR)
#define LOG_ERR(format, ...) LOG_COLOR(LOG_TAG_ERR, LOG_TAG_ERR_COLOR, format, ##__VA_ARGS__)
#endif

#if (LOG_LEVEL >= LOG_LEVEL_WARNING)
#define LOG_WRN(format, ...) LOG_COLOR(LOG_TAG_WRN,	LOG_TAG_WRN_COLOR, format, ##__VA_ARGS__)
#endif

#if (LOG_LEVEL >= LOG_LEVEL_INFO)
#define LOG_INF(format, ...) LOG_COLOR(LOG_TAG_INF,	LOG_TAG_INF_COLOR, format, ##__VA_ARGS__)
#endif

#if (LOG_LEVEL >= LOG_LEVEL_DEBUG)
#define LOG_DBG(format, ...) LOG_COLOR(LOG_TAG_DBG,	LOG_TAG_DBG_COLOR, format, ##__VA_ARGS__)

#define LOG_DBG_HEX(format, buff, len) { \
		LOG_COLOR(LOG_TAG_DBG, LOG_TAG_DBG_HEX_COLOR, "%s", format); \
		printk_hex(buff, len); \
	}
#endif

#else
#define printk(...) { ; }
#define log_init(...) { ; }
#endif


#if !defined(LOG_ASS)
#define LOG_ASS(format, ...) { ; }
#endif

#if !defined(LOG_ERR)
#define LOG_ERR(format, ...) { ; }
#endif

#if !defined(LOG_WRN)
#define LOG_WRN(format, ...) { ; }
#endif

#if !defined(LOG_INF)
#define LOG_INF(format, ...) { ; }
#endif

#if !defined(LOG_DBG)
#define LOG_DBG(format, ...) { ; }
#define LOG_DBG_HEX(format, buff, len) { ; }
#endif

extern void fun_log_init (void);

#ifdef __cplusplus
}
#endif

#endif		//__FUN_LOG_H__


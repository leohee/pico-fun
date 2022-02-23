#ifndef __FUN_LED_H__
#define __FUN_LED_H__

enum {
	LED_OFF			= 0,
	LED_ON			= 1
};

enum {
	LED_STAGE_IDLE					= (0x00),	/* idle */
	LED_STAGE_ON					= (0x01),	/* hold on */
	LED_STAGE_OFF					= (0x02)	/* hold off */
};

enum {
	TIMES_ALWAYS					= (0),		/* endless */
	TIMES_ONE						= (1)
};

#define HOLD_ZERO					(0)			/* omit */
#define HOLD_ON						(1)			/* hold on : on!=0,off=0 */
#define HOLD_OFF					(1)			/* hold off : on=0, off!=0 */

struct fun_led_t {
	uint			pin;

	bool			tmr_ctrl;	/* timer control led */

	uint8_t			stage;
	uint8_t			circle;		/* one or continus */
	uint			times;		/* total run period */
	uint			cnt;		/* counting */

	int				milli_on;
	int				milli_off;

	struct repeating_timer tmr;

	void			(*put)(uint gpio, bool value);
	void			(*toggle)(void);
};


extern void fun_led_init (void);

extern void fun_led_show (uint8_t circle, uint times, uint on, uint off);

#endif



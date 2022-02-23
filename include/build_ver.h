#ifndef __BUILD_VER_H__
#define __BUILD_VER_H__


#define FIRM_VER		("1.0.0")

/* __DATE__ : "" */
/* __TIME__ : "" */

#define YEAR_CH0 (__DATE__[ 7])
#define YEAR_CH1 (__DATE__[ 8])
#define YEAR_CH2 (__DATE__[ 9])
#define YEAR_CH3 (__DATE__[10])

#define MONTH_IS_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
#define MONTH_IS_FEB (__DATE__[0] == 'F')
#define MONTH_IS_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
#define MONTH_IS_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p')
#define MONTH_IS_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
#define MONTH_IS_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
#define MONTH_IS_JUL (__DATE__[0] == 'J' && __DATE__[2] == 'l')
#define MONTH_IS_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u')
#define MONTH_IS_SEP (__DATE__[0] == 'S')
#define MONTH_IS_OCT (__DATE__[0] == 'O')
#define MONTH_IS_NOV (__DATE__[0] == 'N')
#define MONTH_IS_DEC (__DATE__[0] == 'D')

#define MONTH_CH0 ((MONTH_IS_OCT || MONTH_IS_NOV || MONTH_IS_DEC) ? '1' : '0')

#define MONTH_CH1 \
    (   (MONTH_IS_JAN) ? '1' : \
        (MONTH_IS_FEB) ? '2' : \
        (MONTH_IS_MAR) ? '3' : \
        (MONTH_IS_APR) ? '4' : \
        (MONTH_IS_MAY) ? '5' : \
        (MONTH_IS_JUN) ? '6' : \
        (MONTH_IS_JUL) ? '7' : \
        (MONTH_IS_AUG) ? '8' : \
        (MONTH_IS_SEP) ? '9' : \
        (MONTH_IS_OCT) ? '0' : \
        (MONTH_IS_NOV) ? '1' : \
        (MONTH_IS_DEC) ? '2' : \
        /* default */    '?' \
    )

#define DAY_CH0 ((__DATE__[4] >= '0') ? (__DATE__[4]) : '0')
#define DAY_CH1 (__DATE__[5])

#define DATE_BUILD { YEAR_CH0, YEAR_CH1, YEAR_CH2, YEAR_CH3, '-', \
	MONTH_CH0, MONTH_CH1, '-', DAY_CH0, DAY_CH1, '\0' }

#define TIME_BUILD __TIME__


#endif


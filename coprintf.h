/* see [https://github.com/springlie/coprintf] for details */

#ifndef CO_PRINTF_H
#define CO_PRINTF_H

/*** you can customize these macros before calling ***/
/*** you have to change them here if you want to customize them ***/

/* disable co_printf */
/* #define CO_PRINTF_INACTIVE */

/* leader character for mode */
#define CO_PRINTF_LEADER	'^'

#include <stdio.h>

/*** interface ***/

/* colorful stdout */
int coprintf(const char* fmt, ...);

/* colorful stderr */
int ceprintf(const char* fmt, ...);

#endif


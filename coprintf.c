#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include "coprintf.h"

/* max len of origin format string */
#define CO_PRINTF_MAX_LEN	1024

/* added spaces for ascii mode chars */
#define CO_PRINTF_MAX_ADD	256

/* max len of final format string */
#define CO_PRINTF_MAX_MODE	10

#ifdef CO_PRINTF_INACTIVE
	static const int inactive = 1;
#else
	static const int inactive = 0;
#endif

/* set modes, do nothing if inactive */
static int set_mode(FILE* fp, char* dest, const char* mode)
{
	if(inactive
		|| (stdout == fp && !isatty(STDOUT_FILENO))
		|| (stderr == fp && !isatty(STDERR_FILENO)))
		return 0;

	strcat(dest, mode);
	return strlen(mode);
}

/* internal core */

static int covprintf(FILE* fp, const char* fmt, va_list parg)
{
	/* mode strings definition */

	static const char* black	= "\e[30m";
	static const char* red		= "\e[31m";
	static const char* green	= "\e[32m";
	static const char* yellow	= "\e[33m";
	static const char* blue		= "\e[34m";
	static const char* purple	= "\e[35m";
	static const char* cyan		= "\e[36m";
	static const char* white	= "\e[37m";

	static const char* b_black	= "\e[40m";
	static const char* b_red	= "\e[41m";
	static const char* b_green	= "\e[42m";
	static const char* b_yellow	= "\e[43m";
	static const char* b_blue	= "\e[44m";
	static const char* b_purple	= "\e[45m";
	static const char* b_cyan	= "\e[46m";
	static const char* b_white	= "\e[47m";

	static const char* done		= "\e[0m";
	static const char* highlight= "\e[1m";
	static const char* underline= "\e[4m";
	static const char* blink	= "\e[5m";
	static const char* reverse	= "\e[7m";
	static const char* invisible= "\e[8m";

	/* too long origin format string, give up */

	if(CO_PRINTF_MAX_LEN < strlen(fmt))
		return vfprintf(fp, fmt, parg);

	static char new_fmt[CO_PRINTF_MAX_LEN + CO_PRINTF_MAX_ADD];
	memset(new_fmt, 0, CO_PRINTF_MAX_LEN + CO_PRINTF_MAX_ADD);
	const char* p = fmt;

	/* clear env at beginning*/

	int i = set_mode(fp, new_fmt, done);

	while(*p && i < CO_PRINTF_MAX_LEN + CO_PRINTF_MAX_MODE)
	{
		/* keep normal char */

		if(CO_PRINTF_LEADER != *p)
		{
			new_fmt[i++] = *p++;
			continue;
		}

		/* skip leader char itself, match next char to mode */

		switch(*++p)
		{
			/* foreground */

			case 'k': i += set_mode(fp, new_fmt, black		); p++; break;
			case 'r': i += set_mode(fp, new_fmt, red		); p++; break;
			case 'g': i += set_mode(fp, new_fmt, green		); p++; break;
			case 'y': i += set_mode(fp, new_fmt, yellow		); p++; break;
			case 'b': i += set_mode(fp, new_fmt, blue		); p++; break;
			case 'p': i += set_mode(fp, new_fmt, purple		); p++; break;
			case 'c': i += set_mode(fp, new_fmt, cyan		); p++; break;
			case 'w': i += set_mode(fp, new_fmt, white		); p++; break;

			/* background */

			case 'K': i += set_mode(fp, new_fmt, b_black	); p++; break;
			case 'R': i += set_mode(fp, new_fmt, b_red		); p++; break;
			case 'G': i += set_mode(fp, new_fmt, b_green	); p++; break;
			case 'Y': i += set_mode(fp, new_fmt, b_yellow	); p++; break;
			case 'B': i += set_mode(fp, new_fmt, b_blue		); p++; break;
			case 'P': i += set_mode(fp, new_fmt, b_purple	); p++; break;
			case 'C': i += set_mode(fp, new_fmt, b_cyan		); p++; break;
			case 'W': i += set_mode(fp, new_fmt, b_white	); p++; break;

			/* action */

			case 'd': i += set_mode(fp, new_fmt, done		); p++; break;
			case 'h': i += set_mode(fp, new_fmt, highlight	); p++; break;
			case 'u': i += set_mode(fp, new_fmt, underline	); p++; break;
			case 'e': i += set_mode(fp, new_fmt, reverse	); p++; break;
			case 'l': i += set_mode(fp, new_fmt, blink		); p++; break;
			case 'v': i += set_mode(fp, new_fmt, invisible	); p++; break;

			/* if next char can't match any mode, keep it */

			default:
				new_fmt[i++] = *p++;
		}
	}

	/* clear env to exit */

	set_mode(fp, new_fmt, done);

	return vfprintf(fp, new_fmt, parg);
}

int coprintf(const char* fmt, ...)
{
	va_list parg;
	va_start(parg, fmt);
	int ret = covprintf(stdout, fmt, parg);
	va_end(parg);

	return ret;
}

int ceprintf(const char* fmt, ...)
{
	va_list parg;
	va_start(parg, fmt);
	int ret = covprintf(stderr, fmt, parg);
	va_end(parg);

	return ret;
}


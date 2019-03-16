#include <unistd.h>
#include "holberton.h"


/**
 * print_plain - print the literal parts of the format string
 * @fmt: format string
 * @fpos: current position in format string
 * @buf: buffer to print to
 * @bpos: current position in buffer
 */
void print_plain(
		char const * const fmt,
		size_t * const fpos,
		char * const buf,
		size_t * const bpos
)
{
	while (fmt[*fpos] != '\0' && fmt[*fpos] != '%')
	{
		buf[*bpos] = fmt[*fpos];
		++*fpos;
		++*bpos;
	}
}

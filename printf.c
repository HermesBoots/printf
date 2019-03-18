#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include "holberton.h"


/**
 * _printf - print formatted output
 * @fmt: format string indicating how to format other arguments
 *
 * Return: number of characters printed
 */
int _printf(char const *fmt, ...)
{
	size_t fpos = 0, backup, bpos = 0;
	char buf[1024];
	fmt_spec spec;
	int prefix;
	va_list list;

	if (fmt == NULL)
		return (-1);
	va_start(list, fmt);
	while (fmt[fpos] != '\0')
	{
		print_plain(fmt, &fpos, buf, &bpos);
		init_spec(&spec);
		parse_format_spec(&spec, fmt, &fpos);
		if (spec.conversion != CONVERSION_UNKNOWN)
		{
			backup = bpos;
			prefix = print_data(buf, &bpos, &spec, &list);
			pad_field(buf, &backup, &bpos, prefix, &spec);
		}
	}
	return (write(1, buf, bpos));
}


/**
 * init_spec - intitialize a format specifier structure
 * @spec: pointer to structure
 */
void init_spec(fmt_spec * const spec)
{
	*(unsigned int *)&spec->flags = 0;
	spec->width = FORMAT_UNSPECIFIED;
	spec->precision = FORMAT_UNSPECIFIED;
	spec->length = LENGTH_DEFAULT;
	spec->conversion = CONVERSION_INITIAL;
}



/**
 * parse_format_spec - parse the current format specifier in the format
 * @spec: pointer to format specifier
 * @text: pointer to format string
 * @pos: position in the format string
 *
 * Return: which conversion specifier terminates this format specifier
 */
conversions parse_format_spec(
		fmt_spec * const spec,
		char const * const text,
		size_t * const pos
)
{
	parser_states state = PARSER_FLAGS;

	if (text[*pos] != '%')
		return (CONVERSION_UNKNOWN);
	++*pos;
	while (state != PARSER_DONE)
	{
		switch (state)
		{
		case PARSER_FLAGS:
			state = parse_format_flags(spec, text, pos);
			break;
		case PARSER_WIDTH:
			state = parse_format_width(spec, text, pos);
			break;
		case PARSER_PRECISION:
			state = parse_format_precision(spec, text, pos);
			break;
		case PARSER_LENGTH:
			state = parse_format_length(spec, text, pos);
			break;
		case PARSER_CONVERSION:
			state = parse_format_conversion(spec, text, pos);
			break;
		case PARSER_DONE:
			break;
		}
	}
	return (spec->conversion);
}


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

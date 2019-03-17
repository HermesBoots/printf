#include <unistd.h>
#include "holberton.h"


/**
 * parse_format_specifier - parse the current format specifier in the format
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

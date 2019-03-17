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
 * parse_format_flags - parse the current format specifier flags
 * @spec: pointer to format specifier
 * @text: pointer to format string
 * @pos: position in the format string
 *
 * Return: which state the parser should be in after the flags are parsed
 */
parser_states parse_format_flags(
		fmt_spec * const spec,
		char const * const text,
		size_t * const pos
)
{
	switch (text[*pos])
	{
	case '-':
		spec->flags.left_justify = 1;
		++*pos;
		return (PARSER_FLAGS);
	case '+':
		spec->flags.show_positive_sign = 1;
		++*pos;
		return (PARSER_FLAGS);
	case ' ':
		spec->flags.pad_positives = 1;
		++*pos;
		return (PARSER_FLAGS);
	case '#':
		spec->flags.alternate_form = 1;
		++*pos;
		return (PARSER_FLAGS);
	case '0':
		spec->flags.pad_with_zero = 1;
		++*pos;
		return (PARSER_FLAGS);
	default:
		return (PARSER_WIDTH);
	}
}


/**
 * parse_format_width - parse the current format specifier field width
 * @spec: pointer to format specifier
 * @text: pointer to format string
 * @pos: position in the format string
 *
 * Return: which state the parser should be in after the width is parsed
 */
parser_states parse_format_width(
		fmt_spec * const spec,
		char const * const text,
		size_t * const pos
)
{
	switch (text[*pos])
	{
	case '0': case '1': case '2': case '3': case '4': case '5': case '6':
	case '7': case '8': case '9':
		if (spec->width == FORMAT_UNSPECIFIED)
			spec->width = 0;
		spec->width = spec->width * 10 + text[*pos] - '0';
		++*pos;
		return (PARSER_WIDTH);
	default:
		return (PARSER_PRECISION);
	}
}


/**
 * parse_format_precision - parse the current format specifier precision
 * @spec: pointer to format specifier
 * @text: pointer to format string
 * @pos: position in the format string
 *
 * Return: which state the parser should be in after the precision is parsed
 */
parser_states parse_format_precision(
		fmt_spec * const spec,
		char const * const text,
		size_t * const pos
)
{
	switch (text[*pos])
	{
	case '0': case '1': case '2': case '3': case '4': case '5': case '6':
	case '7': case '8': case '9':
		if (spec->precision >= 0)
		{
			spec->precision *= 10;
			spec->precision += text[*pos] - '0';
			++*pos;
			return (PARSER_PRECISION);
		}
		if (spec->precision == FORMAT_NEGATIVE)
			++*pos;
		return (PARSER_LENGTH);
	case '.':
		if (spec->precision == FORMAT_UNSPECIFIED)
		{
			spec->precision = 0;
			++*pos;
			return (PARSER_PRECISION);
		}
		return (PARSER_LENGTH);
	case '-':
		if (spec->precision == 0)
		{
			spec->precision = FORMAT_NEGATIVE;
			++*pos;
			return (PARSER_PRECISION);
		}
		return (PARSER_LENGTH);
	default:
		return (PARSER_LENGTH);
	}
}


/**
 * parse_format_length - parse the current format specifier data length
 * @spec: pointer to format specifier
 * @text: pointer to format string
 * @pos: position in the format string
 *
 * Return: which state the parser should be in after the data length is parsed
 */
parser_states parse_format_length(
		fmt_spec * const spec,
		char const * const text,
		size_t * const pos
)
{
	switch (text[*pos])
	{
	case 'h':
		++*pos;
		if (spec->length == LENGTH_SHORT)
		{
			spec->length = LENGTH_SHORTER;
			return (PARSER_CONVERSION);
		}
		spec->length = LENGTH_SHORT;
		return (PARSER_LENGTH);
	case 'l':
		++*pos;
		if (spec->length == LENGTH_LONG)
		{
			spec->length = LENGTH_LONGER;
			return (PARSER_CONVERSION);
		}
		spec->length = LENGTH_LONG;
		return (PARSER_CONVERSION);
	case 'j':
		spec->length = LENGTH_MAXIMUM;
		++*pos;
		return (PARSER_CONVERSION);
	case 't':
		spec->length = LENGTH_POINTER_DIFFERENCE;
		++*pos;
		return (PARSER_CONVERSION);
	case 'z':
		spec->length = LENGTH_SIZE;
		++*pos;
		return (PARSER_CONVERSION);
	case 'L':
		spec->length = LENGTH_EXTENDED_FLOAT;
		++*pos;
		return (PARSER_CONVERSION);
	default:
		return (PARSER_CONVERSION);
	}
}


/**
 * parse_format_conversion - parse the current format specifier conversion type
 * @spec: pointer to format specifier
 * @text: pointer to format string
 * @pos: position in the format string
 *
 * Return: which state the parser should be in after the conversion is parsed
 */
parser_states parse_format_conversion(
		fmt_spec * const spec,
		char const * const text,
		size_t * const pos
)
{
	switch (text[*pos])
	{
	case 'd': case 'i':
		spec->conversion = CONVERSION_SIGNED_DECIMAL_INTEGER;
		break;
	case 'u':
		spec->conversion = CONVERSION_UNSIGNED_DECIMAL_INTEGER;
		break;
	case 'o':
		spec->conversion = CONVERSION_OCTAL_INTEGER;
		break;
	case 'X':
		spec->flags.capitals = 1;
		/* fall through */
	case 'x':
		spec->conversion = CONVERSION_HEXADECIMAL_INTEGER;
		break;
	case 'c':
		spec->conversion = CONVERSION_CHARACTER;
		break;
	case 's':
		spec->conversion = CONVERSION_STRING;
		break;
	case 'p':
		spec->conversion = CONVERSION_POINTER;
		break;
	case '%':
		spec->conversion = CONVERSION_ESCAPE;
		break;
	case 'S':
		spec->conversion = CONVERSION_STRING_ESCAPED;
		break;
	case 'r':
		spec->conversion = CONVERSION_STRING_REVERSE;
		break;
	case 'R':
		spec->conversion = CONVERSION_STRING_ROT13;
		break;
	default:
		spec->conversion = CONVERSION_UNKNOWN;
	}
	++*pos;
	return (PARSER_DONE);
}

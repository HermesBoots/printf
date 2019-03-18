#include "holberton.h"


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


#define X(c) CONVERSION_ ## c
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
	conversions const map[] = {
		X(HEXADECIMAL_FLOAT), X(BINARY_INTEGER), X(CHARACTER),
		X(SIGNED_DECIMAL_INTEGER), X(EXPONENTIAL_FLOAT),
		X(NORMAL_FLOAT), X(CLEAN_FLOAT), X(UNKNOWN),
		X(SIGNED_DECIMAL_INTEGER), X(UNKNOWN), X(UNKNOWN), X(UNKNOWN),
		X(UNKNOWN), X(COUNT_SO_FAR), X(OCTAL_INTEGER), X(POINTER),
		X(UNKNOWN), X(STRING_REVERSE), X(STRING), X(UNKNOWN),
		X(UNSIGNED_DECIMAL_INTEGER), X(UNKNOWN), X(UNKNOWN),
		X(HEXADECIMAL_INTEGER), X(UNKNOWN), X(UNKNOWN)
	};
	char c;

	spec->conversion = CONVERSION_UNKNOWN;
	c = text[(*pos)++];
	if (c >= 'A' && c <= 'Z')
		spec->flags.capitals = 1;
	switch (c)
	{
	case 'p':
		spec->flags.alternate_form = 1;
		spec->flags.capitals = 1;
		spec->length = LENGTH_LONG;
		spec->conversion = CONVERSION_HEXADECIMAL_INTEGER;
		break;
	case '%':
		spec->conversion = CONVERSION_ESCAPE;
		break;
	case 'S':
		spec->conversion = CONVERSION_STRING_ESCAPED;
		break;
	case 'R':
		spec->conversion = CONVERSION_STRING_ROT13;
		break;
	default:
		if (spec->flags.capitals)
			c += 32;
		if (c >= 'a' && c <= 'z')
			spec->conversion = map[c - 'a'];
	}
	return (PARSER_DONE);
}
#undef X

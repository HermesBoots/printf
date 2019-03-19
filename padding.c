#include <stdio.h>
#include <stdlib.h>
#include "holberton.h"


/**
 * pad_field - pad a newly-printed field to given specification
 * @buf: buffer containing field
 * @start: starting position of field
 * @end: ending position of field
 * @prefix: length of number prefix
 * @spec: format specifier
 */
void pad_field(
		char * const buf,
		size_t * const start,
		size_t * const end,
		int prefix,
		fmt_spec * const spec
)
{
	pad_precision(buf, start, end, prefix, spec);
	pad_width(buf, start, end, prefix, spec);
}


/**
 * pad_width - handle width of fields
 * @buf: buffer containing field
 * @start: starting position of field
 * @end: ending position of field
 * @spec: format specifier
 */
void pad_width(
		char * const buf,
		size_t * const start,
		size_t * const end,
		int prefix,
		fmt_spec * const spec
)
{
	char padding;
	size_t diff, i, temp;

	if (spec->width <= 0)
		return;
	diff = *end - *start;
	temp = spec->width - diff;
	if (spec->flags.left_justify)
	{
		for (i = 0; i < spec->width - diff; i++)
			buf[*end + i] = ' ';
		*end += i;
	}
	else
	{
		if (spec->flags.pad_with_zero && spec->precision < 0)
		{
			spec->precision = spec->width;
			pad_precision(buf, start, end, prefix, spec);
			return;
		}
		else
			padding = ' ';
		movebuf(buf, *start, *start + temp, diff);
		for (i = 0; i < temp; i++)
			buf[*start + i] = padding;
		*end += i;
	}
}


/**
 * pad_precision - handle precision of fields
 * @buf: buffer containing field
 * @start: starting position of field
 * @end: ending position of field
 * @prefix: length of number prefix
 * @spec: format specifier
 */
void pad_precision(
		char * const buf __attribute__((unused)),
		size_t * const start,
		size_t * const end,
		int prefix,
		fmt_spec const * const spec
)
{
	char sign;
	size_t diff, temp;

	diff = *end - *start;
	switch (spec->conversion)
	{
	case CONVERSION_STRING:
		if (spec->precision >= 0 && (unsigned int)spec->precision < diff)
			*end -= diff - spec->precision;
		break;
	case CONVERSION_SIGNED_DECIMAL_INTEGER:
	case CONVERSION_UNSIGNED_DECIMAL_INTEGER:
	case CONVERSION_BINARY_INTEGER:
	case CONVERSION_OCTAL_INTEGER:
	case CONVERSION_HEXADECIMAL_INTEGER:
		diff -= prefix;
		if (spec->precision == 0)
		{
			if (*start + prefix + 1 == *end && buf[*end - 1] == '0')
			{
				*end = *start;
				sign = buf[*start];
				if (sign == '+' || sign == ' ' || sign == '+')
					*end += 1;
			}
		}
		else if (spec->precision > 0 && (unsigned int)spec->precision > diff)
		{
			temp = spec->precision - diff;
			movebuf(buf, *start + prefix, *start + temp + prefix, diff);
			for (temp = 0; temp < spec->precision - diff; temp++)
				buf[*start + prefix + temp] = '0';
			*end += temp;
		}
		break;
	default:
		break;
	}
}


/**
 * movebuf - move bytes inside a buffer
 * @buf: buffer to use
 * @from: index of beginning of source
 * @to: index of beginning of destination
 * @count: number of bytes to move
 */
void movebuf(char * const buf, size_t from, size_t to, size_t count)
{
	size_t i;

	if (to > from)
	{
		for (i = 1; i <= count; i++)
			buf[to + count - i] = buf[from + count - i];
	}
	else
	{
		for (i = 0; i < count; i++)
			buf[to + i] = buf[from + i];
	}
}

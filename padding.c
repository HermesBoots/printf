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
		char * const buf __attribute__((unused)),
		size_t * const start,
		size_t * const end,
		int prefix,
		fmt_spec const * const spec
)
{
	pad_precision(buf, start, end, prefix, spec);
	/*pad_width(buf, start, end, spec);*/
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
	size_t diff, temp;

	printf("%lu %lu %d\n", *start, *end, prefix);
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
				*end -= diff;
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
	char * copy;
	size_t i;

	copy = malloc(count);
	if (copy == NULL)
		exit(98);
	for (i = 0; i < count; i++)
		copy[i] = buf[from + i];
	for (i = 0; i < count; i++)
		buf[to + i] = copy[i];
}

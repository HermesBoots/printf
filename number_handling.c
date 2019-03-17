/* Functions to accept data from parse_format_spec.c and prepares ints for */
/* tx  to buffer. Also handles all int types for conversion (bases) and from */
/* signed to unsigned. */

#include "holberton.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

/**
 * print_data - take parsed formatting and send ints to be changed
 * @buf: current buffer to print to
 * @pos: current position in buffer
 * @spec: how to format
 * @list: va_list
 *
 * Return: VOID
 */
void print_data(char * const buf, size_t * const pos,
		fmt_spec const * const spec, va_list *list)
{
	int const bases[] = {0, 2, 8, 10, 10, 16, 16};
	unsigned long uln = 0;

	switch (spec->conversion)
	{
	case CONVERSION_OCTAL_INTEGER:
	case CONVERSION_UNSIGNED_DECIMAL_INTEGER:
	case CONVERSION_HEXADECIMAL_INTEGER:
	case CONVERSION_SIGNED_DECIMAL_INTEGER:
	case CONVERSION_BINARY_INTEGER:
		uln = convert_int(buf, pos, spec, list);
		print_int(buf, pos, spec, uln, bases[spec->conversion]);
		break;
	case CONVERSION_STRING:
		print_str(buf, pos, spec, va_arg(*list, char *));
		break;
	case CONVERSION_CHARACTER:
		buf[*pos] = va_arg(*list, int) & 0xFF;
		++*pos;
		break;
	case CONVERSION_ESCAPE:
		buf[*pos] = '%';
		++*pos;
	default:
		break;
	}
}

/**
 * print_str - print a string to the buffer
 * @buf: buffer
 * @pos: position in buffer to write to
 * @spec: to check if reverse
 * @str: pointer to string
 */
void print_str(char * const buf, size_t * const pos,
	       fmt_spec const * const spec, char const *str)
{
	char *s = str;

	if (spec->conversions == CONVERSION_STRING_REVERSE)
	{
		while (*s++)
			;
		for (s--; s != str; (*pos)++, s--)
			buf[*pos] = *s;
	}
	else
	{
		while (*str != '\0')
		{
			buf[*pos] = *str;
			++*pos;
			++str;
		}
	}
}

/**
 * convert_int - convert int to unsigned long
 * @buf: buffer
 * @pos: current position in buffer
 * @spec: lots of stuff
 * @list: va_list
 *
 * Return: unsigned long int
 */
unsigned long convert_int(char * const buf, size_t * const pos,
			  fmt_spec const * const spec, va_list *list)
{
	unsigned long int uli;
	int negative = false;

	switch (spec->conversion)
	{
	case CONVERSION_OCTAL_INTEGER:
	case CONVERSION_HEXADECIMAL_INTEGER:
	case CONVERSION_UNSIGNED_DECIMAL_INTEGER:
	case CONVERSION_BINARY_INTEGER:
		if (spec->length == LENGTH_LONG)
			uli = va_arg(*list, unsigned long);
		/* will be positive */
		else
			uli = va_arg(*list, unsigned int);
		/* will be positive */
		break;
	case CONVERSION_SIGNED_DECIMAL_INTEGER:
		if (spec->length == LENGTH_LONG)
			uli = va_arg(*list, long);
		else
			uli = va_arg(*list, int);
		if (uli & 0x8000000000000000)
		{
			uli = (ULONG_MAX - uli + 1);
			negative = true;
			print_prefix(buf, pos, spec, negative);
		}
		break;
	default:
		break;
	}
	return (uli);
}

/**
 * print_int - convert to base and print to buffer
 * @buf: buffer to print to
 * @pos: current position in buffer
 * @spec: to check if flags.capitals is true
 * @val: value to convert and print
 * @radix: base to convert to
 *
 * Return: VOID
 */
void print_int(char * const buf, size_t * const pos,
	       fmt_spec const * const spec, unsigned long val, int radix)
{
	int caps = spec->flags.capitals, alt = spec->flags.alternate_form;
	const char digitsUp[16] = "0123456789ABCDEF";
	const char digitsLow[16] = "0123456789abcdef";
	int index = 0, temp = 0;
	int convNum[64];

	do {
		convNum[index] = val % radix;
		index++;
		val /= radix;
	} while (val);
	if (caps)
		for (index--; index >= 0; index--)
		{
			temp = convNum[index];
			buf[(*pos)++] = digitsUp[temp];
		}
	else
		for (index--; index >= 0; index--)
		{
			temp = convNum[index];
			buf[(*pos)++] = digitsLow[temp];
		}
}

int print_prefix(char * const buf, size_t * const pos,
		 fmt_spec const * const spec, int negative)
{
	int caps = spec->flag.capitals, alt = spec->flag.alternate_form;

	if (negative == true)
	{
		buf[(*pos)++] = '-';
		return (1);
	}
	else if (spec->flags.show_positive_sign)
	{
		buf[(*pos)++] = '+';
		return (1);
	}
	else if (spec->flags.pad_positives)
	{
		buf[(*pos)++] = ' ';
		return (1);
	}
	if (alt)
	{
		if (spec->conversion == CONVERSION_OCTAL_INTEGER)
		{
			buf[(*pos)++] = '0';
			return (1);
		}
		else if (spec->conversion == CONVERSION_HEXADECIMAL_INTEGER)
		{
			buf[(*pos)++] = '0';
			if (caps)
			{
				buf[(*pos)++] = 'X';
				return (2);
			}
			else
			{
				buf[(*pos)++] = 'x';
				return (2);
			}
		}
	}
}

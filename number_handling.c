/**
 * Functions to accept data from parse_format_spec.c and prepares ints for tx
 * to buffer. Also handles all int types for conversion (bases) and from signed
 * to unsigned.
 */
#include "holberton.h"
#include <stdargs.h>
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
	va_arg(*list, int);
	int const bases[] = {0, 8, 10, 10, 16, 16};
	unsigned long uln = 0;
	int carry = false, negative = false;

	switch (spec->conversion)
	{
	case CONVERSION_OCTAL_INTEGER:
	case CONVERSION_UNSIGNED_DECIMAL_INTEGER:
	case CONVERSION_HEXADECIMAL_INTEGER:
	case CONVERSION_SIGNED_DECIMAL_INTEGER:
		uln = convert_int(buf, pos, spec, list);
		print_int(buf, pos, spec, uln, bases[spec->conversion])
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
		}
		break;
	default:
		break;
	}
	if (negative == true)
		buf[(*pos)++] = '-';
	else if (spec->flags.show_positive_sign)
		buff[(*pos)++] = '+';
	else if (spec->flags.pad_positives)
		buff[(*pos)++] = ' ';
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
	int caps = spec->flags.capitals;
	const char digitsUp[16] = "0123456789ABCDEF";
	const char digitsLow[16] = "0123456789abcdef";
	int index = 0, length = 0, temp = 0;
	int convNum[64];
	char digit;

	do {
		convNum[index] = val % radix;
	        index++;
		convNum /= radix;
	} while (num);
	length = index;
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

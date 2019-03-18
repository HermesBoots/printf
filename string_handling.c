/* Functions for handling strings */
#include "holberton.h"

/**
 * print_str - print a string to the buffer or reverse and print
 * @buf: buffer
 * @pos: position in buffer to write to
 * @spec: to check if reverse
 * @str: pointer to string
 */
void print_str(char * const buf, size_t * const pos,
	       fmt_spec const * const spec, char *str)
{
	char *s = str, *null = "(null)";
	int i;

	if (str == NULL)
		for (i = 0; i < 6; i++)
		{
			buf[(*pos)++] = null[i];
			return;
		}
	if (spec->conversion == CONVERSION_STRING_ROT13)
		rot_13(s);
	if (spec->conversion == CONVERSION_STRING_REVERSE)
	{
		while (*s++)
			;
		for (s--; s >= str; (*pos)++, s--)
			buf[*pos] = *s;
	}
	else
	{
		while (*s != '\0')
		{
			buf[*pos] = *s;
			++*pos;
			++s;
		}
	}
}

/**
 * rot_13 - convert string to rot13
 * @str: string to modify
 *
 * Return: VOID
 */
void rot_13(char *str)
{
	char *s = str;
	char const *rot =
		"NOPQRSTUVWXYZABCDEFGHIJKLM123456nopqrstuvwxyzabcdefghijklm";

	for (; *s; s++)
	{
		if ((*s >= 'A' || *s <= 'Z') && (*s >= 'a' || *s <= 'z'))
			*s = rot[*s - 'A'];
	}
}

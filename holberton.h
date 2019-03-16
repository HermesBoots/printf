#ifndef _FORMATTER_H_
#define _FORMATTER_H_

#include <stdlib.h>


#define FORMAT_UNSPECIFIED (-1)
#define FORMAT_NEGATIVE (-2)


/**
 * enum lengths - argument data lengths supported by custom printf
 * @LENGTH_DEFAULT: used when length isn't specified
 * @LENGTH_SHORTER: "hh"
 * @LENGTH_SHORT: "h"
 * @LENGTH_LONG: "l"
 * @LENGTH_LONGER: "ll"
 * @LENGTH_MAXIMUM: "j"
 * @LENGTH_SIZE: "z"
 * @LENGTH_POINTER_DIFFERENCE: "t"
 * @LENGTH_EXTENDED_FLOAT: "L"
 */
enum lengths
{
	LENGTH_DEFAULT,
	LENGTH_SHORTER,
	LENGTH_SHORT,
	LENGTH_LONG,
	LENGTH_LONGER,
	LENGTH_MAXIMUM,
	LENGTH_SIZE,
	LENGTH_POINTER_DIFFERENCE,
	LENGTH_EXTENDED_FLOAT
};


/**
 * enum parser_states - states for the format specifier parser
 * @PARSER_INITIAL: intitial state, sanity test to make sure a % exists
 * @PARSER_FLAGS: parse the flags '0', '-', '+', ' ', '#'
 * @PARSER_WIDTH: parse the field width, consisting of a sequence of digits
 * @PARSER_DOT: handle the optional dot that separates the width and precision
 * @PARSER_PRECISION: parse the precision, consisting of a sequence of digits
 * @PARSER_SKIP_DIGITS: ignore digits when precision is negative
 * @PARSER_LENGTH: parse the data lengths
 * @PARSER_CONVERSION: parse the conversion format
 */
typedef enum parser_states
{
	PARSER_FLAGS,
	PARSER_WIDTH,
	PARSER_DOT,
	PARSER_PRECISION,
	PARSER_SKIP_DIGITS,
	PARSER_LENGTH,
	PARSER_CONVERSION
} parser_states;


/**
 * enum conversions - conversion types supported by custom printf
 * @CONVERSION_INITIAL: initial value, indicates uninitialized specifier struct
 * @CONVERSION_SIGNED_DECIMAL_INTEGER: 'd', 'i'
 * @CONVERSION_UNSIGNED_DECIMAL_INTEGER: 'u'
 * @CONVERSION_OCTAL_INTEGER: 'o'
 * @CONVERSION_HEXADECIMAL_INTEGER: 'x', 'X'
 * @CONVERSION_NORMAL_FLOAT: 'f', 'F'
 * @CONVERSION_EXPONENTIAL_FLOAT: 'e', 'E'
 * @CONVERSION_CLEAN_FLOAT: 'g', 'G'
 * @CONVERSION_HEXADECIMAL_FLOAT: 'a', 'A'
 * @CONVERSION_CHARACTER: 'c'
 * @CONVERSION_STRING: 's'
 * @CONVERSION_POINTER: 'p'
 * @CONVERSION_COUNT_SO_FAR: 'n'
 * @CONVERSION_ESCAPE: '%'
 * @CONVERSION_UNKNOWN: indicates invalid conversion specifier
 */
typedef enum conversions
{
	CONVERSION_INITIAL,
	CONVERSION_SIGNED_DECIMAL_INTEGER,
	CONVERSION_UNSIGNED_DECIMAL_INTEGER,
	CONVERSION_OCTAL_INTEGER,
	CONVERSION_HEXADECIMAL_INTEGER,
	CONVERSION_NORMAL_FLOAT,
	CONVERSION_EXPONENTIAL_FLOAT,
	CONVERSION_CLEAN_FLOAT,
	CONVERSION_HEXADECIMAL_FLOAT,
	CONVERSION_CHARACTER,
	CONVERSION_STRING,
	CONVERSION_POINTER,
	CONVERSION_COUNT_SO_FAR,
	CONVERSION_ESCAPE,
	CONVERSION_UNKNOWN
} conversions;


/**
 * struct fmt_spec_flags - bit fields for printf-family format flags
 * @left_justify: pad field on the right instead of left
 * @show_positive_sign: show + before positive numbers
 * @pad_positives: show a space before positive numbers
 * @alternate_form: various meanings for the float conversions
 * @pad_with_zero: pad fields with zeros instead of spaces
 * @capitals: whether the conversion type was a capital letter
 */
struct fmt_spec_flags
{
	unsigned int left_justify : 1;
	unsigned int show_positive_sign : 1;
	unsigned int pad_positives : 1;
	unsigned int alternate_form : 1;
	unsigned int pad_with_zero : 1;
	unsigned int capitals : 1;
};

/**
 * struct fmt_spec - printf-family format specifier
 * @flags: bit field of flags
 * @width: width of field
 * @precision: precision of field
 * @length: size of field data in memory
 * @conversion: which data type in memory
 */
typedef struct fmt_spec
{
	struct fmt_spec_flags flags;
	int width;
	int precision;
	enum lengths length;
	enum conversions conversion;
} fmt_spec;


void init_spec(fmt_spec * const spec);
parser_states parse_format_flags(
		fmt_spec * const spec,
		char const * const text,
		size_t * const pos
);
parser_states parse_format_width(
		fmt_spec * const spec,
		char const * const text,
		size_t * const pos
);
parser_states parse_format_precision(
		fmt_spec * const spec,
		char const * const text,
		size_t * const pos
);
parser_states parse_format_length(
		fmt_spec * const spec,
		char const * const text,
		size_t * const pos
);
parser_states parse_format_length(
		fmt_spec * const spec,
		char const * const text,
		size_t * const pos
);
parser_states parse_format_conversion(
		fmt_spec * const spec,
		char const * const text,
		size_t * const pos
);


#endif /* _FORMATTER_H_ */
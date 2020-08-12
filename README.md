# `_printf`

A project to recreate the C standard `printf` function with some extra extensions.

## Non-Standard Features:
- `b` prints an integer converted to binary
- `o` prints an integer converted to octal
- `#` as a flag prepends `0x` to hexadecimal numbers and `0` to octal numbers
- `S` prints a string as the standard `s` specifier, except non-printable characters are printed as `\x` followed by the character's code point in hexadecimal
- `r` prints a string in reverse
- `R` prints a string with all English letters encoded with [ROT13](https://en.wikipedia.org/wiki/ROT13)

## Contributors
- Nate Peterson [GitHub](https://github.com/blueExcess/) [Twitter](https://twitter.com/Natefp)
- Sam Hermes [GitHub](https://github.com/HermesBoots/) [Twitter](https://twitter.com/SamHermesBoots)

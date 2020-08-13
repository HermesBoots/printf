# `_printf`

![printf in Bash](https://i.imgur.com/EMc1wor.png)

A project to recreate the C standard `printf` function with some extra extensions.

## Usage

Functions as a drop-in replacement for the standard `printf` function when used in supported ways. This code has no external dependencies and can added to any C project and compiled along with it (barring name conflicts).

## Non-Standard Features:
- `b` prints an integer converted to binary
- `o` prints an integer converted to octal
- `#` as a flag prepends `0x` to hexadecimal numbers and `0` to octal numbers
- `S` prints a string as the standard `s` specifier, except non-printable characters are printed as `\x` followed by the character's code point in hexadecimal
- `r` prints a string in reverse
- `R` prints a string with all English letters encoded with [ROT13](https://en.wikipedia.org/wiki/ROT13)
- lacks support for printing non-integer numbers

## Contributors
- Nate Peterson [GitHub](https://github.com/blueExcess/) [LinkedIn](https://www.linkedin.com/in/natefp/) [Twitter](https://twitter.com/Natefp)
- Sam Hermes [GitHub](https://github.com/HermesBoots/) [LinkedIn](https://www.linkedin.com/in/samuel-hermes/) [Twitter](https://twitter.com/SamHermesBoots)

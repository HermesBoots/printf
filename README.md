# `printf`

A project to recreated the C standard `printf` function with some extra extensions.


## Checklist:
### Format specifiers (%n)
- [x] c - if no l modifier, int converted to unsigned char and resulting char is printed (ASCII)
- [x] s - if no l modifier, will print string up to but not including '\0'.
- [x] d - int argument converted to signed decimal notation
- [x] i - s/a
- [x] b - arguemnt is converted to binary [partial complete - not in enum]
- [x] u - converted to unsigned decimal
- [x] o - converted to unsigned octal
- [x] x - converted to unsigned hex (lowercase)
- [x] X - converted to unsigned hex (uppercase)
- [x] S - print a string, but non-printable chars are upper hex, 2 chars (\xNN)(custom)
- [x] p - print address
- [x] + - A  sign  (+ or -) should always be placed before a number produced by a signed conversion.
- [x]  - (a space) A blank should be left before a positive number (or empty string) produced by a signed conversion.
- [x] # - "alternate form" -- o: preceeded by a 0, x/X: preceeded by 0x, floats: all numbers will have decimal point
- [ ] l - length modifier for d, i, o, u, x, X
- [ ] h - s/a
- [ ] 0 - padded with 0
- [x] r - prints the reversed string (custom)
- [x] R - print ROT13'd string (custom)
- [ ] - - left justify
- [x] % - will print a '%' (use: %%)

### Other:
- [ ] man page for function [draft complete]
- [x] local buffer of 1024 chars
- [x] handle field width for non-custom conversions
- [x] handle precision for non-custom conversions
- [ ] GG - will change voltage of computer and make it explode. Super exciting.

## Issues to resolve:


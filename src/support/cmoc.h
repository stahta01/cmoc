// cmoc.h - CMOC's standard library functions.
//
// By Pierre Sarrazin <http://sarrazip.com/>.
// This file is in the public domain.
//
// Functions not documented here should be assumed to behave as in C.

#ifndef _H_CMOC
#define _H_CMOC

#ifndef __GNUC__

typedef unsigned size_t;

#ifndef VECTREX
// Supports %u, %d, %x, %X, %p, %s, %c and %%. Specifying a field width is
// allowed, but a left justification is only supported for strings, i.e.,
// %-15s will work, but %-6u will not. Zero padding for a number is supported
// (e.g., %04x).
//
int printf(char *format, ...);
#endif

// Writes to 'dest'. Not thread-safe. Does not check for buffer overflow.
int sprintf(char *dest, char *format, ...);

#ifndef VECTREX
// Writes the first 'n' characters designated by 's', regardless of any
// null characters encountered among them.
//
void putstr(char *s, size_t n);

void putchar(int c);
#endif

int strcmp(char *s1, char *s2);
int memcmp(void *s1, void *s2, size_t n);
void *memcpy(void *dest, void *src, size_t n);
void *memset(void *s, int c, size_t n);
size_t strlen(char *s);
char *strcpy(char *dest, char *src);
char *strcat(char *dest, char *src);
char *strncpy(char *dest, char *src, size_t n);
char *strchr(char *s, int c);
char *strlwr(char *s);
char *strupr(char *s);

// Double-word to ASCII.
// Converts the unsigned 32-bit integer formed by hi * 65536 + lo into
// an ASCII decimal representation that gets written to 'out'.
// 'out' must point to at least 11 bytes. The string written there will
// be terminated by a null character.
// Returns the address of the first non-'0' character in the 11-byte
// buffer, or to "0" if hi and lo are both zero.
// Example: char s[11]; char *p = dwtoa(s, 1, 2);
//          s will get the string "
//
char *dwtoa(char *out, unsigned hi, unsigned lo);

// Divides an unsigned 32-bit integer by an unsigned 8-bit integer.
// The 4 bytes designated by 'dividendInQuotientOut' are the input dividend.
// The 32-bit quotient is left in those 4 bytes.
//
void div328(char *dividendInQuotientOut, unsigned char divisor);

// Multiply a word by a byte.
// Stores the high word of the product in *hi and returns the low word.
//
unsigned mulwb(unsigned char *hi, unsigned wordFactor, unsigned char byteFactor);

// Similar to mulwb().
unsigned mulww(unsigned *hi, unsigned factor0, unsigned factor1);

// Stores 0 in twoWords[0], twoWords[1].
//
void zerodw(unsigned *twoWords);

// Adds the 16-bit integer 'term' to the 32-bit integer designated by
// twoWords[0] and twoWords[1].
//
void adddww(unsigned *twoWords, unsigned term);

int tolower(int c);
int toupper(int c);
void exit(int status);

#define RAND_MAX 0x7FFF
void srand(unsigned seed);
int rand();

// See the CMOC manual.
void *sbrk(size_t increment);
size_t sbrkmax();
void set_null_ptr_handler(void *newHandler);
void set_stack_overflow_handler(void *newHandler);


// Redirect printf() et al. to the function at 'routine', which will
// receive each character to be printed, in register A.
//
// That routine MUST preserve registers B, X, Y and U.
//
// If this function is never called, printf() et al. write to the
// system's standard character output routine.
//
// Returns the original output routine address.
// To uninstall the new routine, call this function again with
// the original routine address.
//
void *setConsoleOutHook(void *routine);


#ifndef VECTREX

// Blocks the execution for the specified time in 60ths of a second.
//
void delay(size_t sixtiethsOfASecond);

// Reads a line from standard input, converts an expected 16-bit decimal
// number and returns it. Not thread-safe.
//
unsigned readword();

// Reads a line from standard input and returns it.
// Not thread-safe.
// Returns a null pointer if the operation failed (e.g., end of file
// encountered).
//
char *readline();

#endif

#else

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif  /* __GNUC__ */

#endif  /* _H_CMOC */

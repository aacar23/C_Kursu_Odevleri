#include "is_anagram_improved.h"

#include <ctype.h>
#include <stddef.h>

#define NTH_LETTER(letter) ((toupper((letter))) - 48)

int is_anagram_improved(const char* str1, const char* str2)
{
	int flags = 0;

	for (;*str1;++str1)
		flags ^= (1 << NTH_LETTER(*str1));

	for (;*str2;++str2)
		flags ^= (1 << NTH_LETTER(*str2));

	return !flags;
}
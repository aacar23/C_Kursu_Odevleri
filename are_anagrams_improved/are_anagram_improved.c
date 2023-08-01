#include "are_anagrams_improved.h"

#include <stddef.h>

int are_anagrams_improved(const char* str1, const char* str2)
{
	int flags = 0;

	size_t size_str1 = 0;
	size_t size_str2 = 0;

	for (;*(str1 + size_str1); ++size_str1)
		flags ^= (1 << *(str1 + size_str1));
	for (;*(str2 + size_str2); ++size_str2)
		flags ^= (1 << *(str2 + size_str2));
			

	return size_str1 == size_str2 && !flags;
}
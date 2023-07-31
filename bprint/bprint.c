#include "bprint.h"

#include <stdio.h>
#include <string.h>

void swap(char* a, char* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void reverse_str(const char* str)
{
	size_t size = strlen(str);
	for (size_t i = 0; i < size / 2; ++i)
		swap(str + i, str + size - i - 1);
}

void bprint(int val)
{
	static char str[33] = { 0 };

	int print_ind = 0;
	for (int i = 0;val; val /= 2, ++i)
		*(str + i) += val % 2 + 48;

	reverse_str(str);

	while (!(*(str + print_ind) - 48))
		++print_ind;

	if (!*(str + print_ind)) {
		putchar('\x30');
		return;
	}
	puts(str + print_ind);
}
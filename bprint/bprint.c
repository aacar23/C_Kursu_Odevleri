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
	char str[33] = { 0 };
	memset(str, 48, 32);

	int print_ind = 0;
	for (int i = 0;i < 32; val /= 2, ++i)
		*(str + i) += val % 2;

	reverse_str(str);

	while (!(*(str + print_ind) - 48))
		++print_ind;

	puts(str + print_ind);
}
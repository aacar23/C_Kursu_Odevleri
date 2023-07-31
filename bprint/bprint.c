#include "bprint.h"

#include <stdio.h>
#include <inttypes.h>

void bprint(int32_t low, int32_t high)
{
	union num_64{
		struct{
			int32_t low;
			int32_t high;
		};
		int64_t value;
	}num;

	num.low = low;
	num.high = high;

	printf("%" PRId64 , num.value);
}
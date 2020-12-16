#include "SC_Random.h"

#include <stdlib.h>

void SC_RandomSetSeed(unsigned long seed)
{
	srand(seed);
}

float SC_RandomOut(void)
{
	return ((float)rand())/RAND_MAX;
}

#include "Random.h"
#include <iostream>

Random::Random()
{
	//srand(time(NULL));
	//rand();
}

float Random::rand_uniform()
{
	int result = rand();
	return (float)(result % 10000) / 10000.0;
}

int Random::rand_binary()
{
	return rand() % 2;
}

int Random::rand_int(int max)
{
	return rand() % max;
}

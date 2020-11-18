#pragma once
#include <ctime>
#include <cstdlib>

class Random
{
public:
	Random();
	float rand_uniform();
	int rand_binary();
	int rand_int(int max);
};

#pragma once
#include <string>
#include "random.h"

using namespace std;

class DNA
{
private:
	int gene_dimension;
	float mutation_probability;
	Random random_generator;
	string gene;

public:
	DNA(int gene_dimension, float mutation_probability, Random random_generator);
	DNA(string gene, float mutation_probability, Random random_generator);
	string generate_gene();
	string get_gene();
	int get_dimension();
	void mutate(int position);
};


#pragma once
#include "DNA.h"
#include <vector>
#include <iostream>

class Population
{
private:
	int pop_number;
	int gene_dimension;
	int function_dimension;
	float mutation_probability;
	float(*function)(vector<float>, int);
	float a;
	float b;
	int precision;
	float C;
	Random rand;
	vector<float> fitness;

public:
	vector<DNA> population;
	Population(int pop_number, float mutation_probability
			, float (*function)(vector<float>, int), int function_dimension, float a
			, float b, int precision, float C);

	DNA crossover(DNA gene1, DNA gene2, float gene1_fitness, float gene2_fitness);
	DNA cut_crossover(DNA gene1, DNA gene2, int cut_position);
	float get_function_value(string gene);
	void calc_fitness();
	void show_DNA();
	void natural_selection();
	void generate();
	DNA best_mutation(DNA D);
	DNA get_top_candidate();
};


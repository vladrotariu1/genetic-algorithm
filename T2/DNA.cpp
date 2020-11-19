#include "DNA.h"

DNA::DNA(int gene_dimension, float mutation_probability, Random random_generator)
{
	this->gene_dimension = gene_dimension;
	this->mutation_probability = mutation_probability;
	this->random_generator = random_generator;
	this->gene = generate_gene();
}

DNA::DNA(string gene, float mutation_probability, Random random_generator)
{
	this->gene = gene;
	this->gene_dimension = this->gene.length();
	this->mutation_probability = mutation_probability;
	this->random_generator = random_generator;
}

string DNA::generate_gene()
{
	string result;
	for (int i = 0; i < this->gene_dimension; i++) {
		result.push_back('0' + this->random_generator.rand_binary());
	}

	return result;
}

string DNA::get_gene()
{
	return this->gene;
}

int DNA::get_dimension()
{
	return this->gene_dimension;
}

void DNA::mutate(int position)
{
	//int position = random_generator.rand_int(this->gene_dimension);
	if (this->random_generator.rand_uniform() <= this->mutation_probability) {
		if (gene.at(position) == '0') {
			gene[position] = '1';
		}
		else {
			gene[position] = '0';
		}
	}
}

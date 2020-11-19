#include "Population.h"

float Population::get_function_value(string gene)
{
	int parameter_length = this->gene_dimension / this->function_dimension;
	vector<float> parameters;

	for (int i = 0; i < function_dimension; i++) {
		float decimal = strtol(gene.substr((size_t)i * (size_t)parameter_length, parameter_length).c_str(), NULL, 2);
		float parameter = this->a + ((double)decimal * ((double)this->b - (double)this->a) / (pow(2, this->gene_dimension / function_dimension) - 1));
		//cout << parameter << " ";
		parameters.push_back(parameter);
	}
	//cout << '\n';

	return this->function(parameters, this->function_dimension);
}

Population::Population(int pop_number, float mutation_probability, float(*function)(vector<float>, int), int function_dimension, float a, float b, int precision, float C)
{
	this->pop_number = pop_number;
	this->gene_dimension = function_dimension * ceil(log2(((double)b - a) * pow(10, precision)));
	this->mutation_probability = mutation_probability;
	this->function = function;
	this->function_dimension = function_dimension;
	this->a = a;
	this->b = b;
	this->precision = precision;
	this->rand = Random();
	this->C = C;

	for (int i = 0; i < pop_number; i++) {
		DNA new_gene = DNA(gene_dimension, this->mutation_probability, this->rand);
		this->population.push_back(new_gene);
	}
}


DNA Population::crossover(DNA gene1, DNA gene2, float gene1_fitness, float gene2_fitness)
{
	string gene1_info = gene1.get_gene();
	string gene2_info = gene2.get_gene();
	string result;

	float total_fitness = gene1_fitness + gene2_fitness;

	for (int i = 0; i < this->gene_dimension; i++) {
		float probability = this->rand.rand_uniform();
		
		if (gene1_fitness / total_fitness < probability) {
			result.push_back(gene1_info[i]);
		}
		else {
			result.push_back(gene2_info[i]);
		}
	}

	return DNA(result, this->mutation_probability, rand);
}

DNA Population::cut_crossover(DNA gene1, DNA gene2, int cut_position)
{
	string gene1_info = gene1.get_gene();
	string gene2_info = gene2.get_gene();

	string result = gene1_info.substr(0, cut_position + 1);
	result += gene2_info.substr(cut_position + 1);

	return DNA(result, this->mutation_probability, this->rand);
}

void Population::calc_fitness()
{
	fitness.clear();
	for (int i = 0; i < pop_number; i++) {
		DNA candidate = population[i];
		
		float candidate_fitness = pow(1 / (C + get_function_value(candidate.get_gene())), 4);
		fitness.push_back(candidate_fitness);
	}
}

void Population::show_DNA()
{
	for (int i = 0; i < this->pop_number; i++) {
		cout << this->population.at(i).get_gene() << "\n";
	}

	cout << '\n' << '\n';
}

void Population::natural_selection()
{
	float total_fitness = 0;
	for (int i = 0; i < pop_number; i++) {
		total_fitness += this->fitness[i];
	}

	float q_counter = 0;
	vector<float> p;
	vector<float> q;

	for (int i = 0; i < pop_number; i++) {
		p.push_back(this->fitness[i] / total_fitness);
		q.push_back(q_counter += this->fitness[i] / total_fitness);
	}

	vector<DNA> selected_population;
	vector<float> new_fitness;
	
	selected_population.push_back(get_top_candidate());
	new_fitness.push_back(pow(1 / (get_function_value(get_top_candidate().get_gene())), 4));

	for (int i = 1; i < pop_number; i++) {
		float probability = rand.rand_uniform();

		for (int j = 0; j < pop_number; j++) {
			if (j == 0 && probability <= q[j]) {
				DNA selected_DNA = DNA(population[j].get_gene(), this->mutation_probability, rand);
				selected_population.push_back(selected_DNA);
				new_fitness.push_back(fitness[j]);
			}
			else if (j > 0 && (q[j - 1] < probability && probability <= q[j])) {
				DNA selected_DNA = DNA(population[j].get_gene(), this->mutation_probability, rand);
				selected_population.push_back(selected_DNA);
				new_fitness.push_back(fitness[j]);
			}
		}
	}

	population = selected_population;
	fitness = new_fitness;
}

void Population::generate()
{
	vector<DNA> children;
	children.push_back(population[0]);
	for (int i = 1; i < this->pop_number; i++) {
		int x = rand.rand_int(pop_number);
		int y = rand.rand_int(pop_number);
		DNA parent1 = population[x];
		DNA parent2 = population[y];

		while (true) {
			if (parent1.get_gene() != parent2.get_gene())
				break;

			x = rand.rand_int(pop_number);
			y = rand.rand_int(pop_number);
			parent1 = population[x];
			parent2 = population[y];
		}
	
		DNA child = crossover(parent1, parent2, fitness[x], fitness[y]);
		child.mutate(this->rand.rand_int(this->gene_dimension));
		children.push_back(child);
		child = cut_crossover(child, population[rand.rand_int(pop_number)], rand.rand_int(gene_dimension));
	}

	population = children;
	//this->mutation_probability *= 0.9999;
}

DNA Population::best_mutation(DNA D)
{
	float best_fitness = 0;
	DNA result = D;
	
	for (int i = 0; i < this->gene_dimension; i++) {
		DNA new_gene = D;
		new_gene.mutate(i);
		float fitness = pow(1 / (C + get_function_value(new_gene.get_gene())), 4);
		if (best_fitness < fitness) {
			best_fitness = fitness;
			result = new_gene;
		}
	}
	return result;
}

DNA Population::get_top_candidate()
{
	float max_fitness = 0;
	int position = 0;

	for (int i = 0; i < pop_number; i++) {
		if (max_fitness < fitness[i]) {
			position = i;
			max_fitness = fitness[i];
		}
	}

	return population[position];
}

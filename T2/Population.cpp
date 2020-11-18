#include "Population.h"

float Population::get_function_value(string gene)
{
	int parameter_length = this->gene_dimension / this->function_dimension;
	vector<float> parameters;

	for (int i = 0; i < function_dimension; i++) {
		float decimal = strtol(gene.substr(i * parameter_length, parameter_length).c_str(), NULL, 2);
		float parameter = this->a + (decimal * (this->b - this->a) / (pow(2, this->gene_dimension / function_dimension) - 1));
		//cout << parameter << " ";
		parameters.push_back(parameter);
	}
	//cout << '\n';

	return this->function(parameters, this->function_dimension);
}

Population::Population(int pop_number, float mutation_probability, float(*function)(vector<float>, int), int function_dimension, float a, float b, int precision)
{
	this->pop_number = pop_number;
	this->gene_dimension = function_dimension * ceil(log2((b - a) * pow(10, precision)));
	this->mutation_probability = mutation_probability;
	this->function = function;
	this->function_dimension = function_dimension;
	this->a = a;
	this->b = b;
	this->precision = precision;
	this->rand = Random();

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

	for (int i = 0; i < this->gene_dimension; i++) {
		float probability = this->rand.rand_uniform();
		
		if (0.5 < probability) {
			result.push_back(gene1_info[i]);
		}
		else if (0.5 >= probability) {
			result.push_back(gene2_info[i]);
		}
	}

	return DNA(result, this->mutation_probability, rand);
}

void Population::calc_fitness(float C)
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

	//selected_population.push_back(get_top_candidate());
	//new_fitness.push_back(pow(1 / (get_function_value(get_top_candidate().get_gene())), 4));

	for (int i = 0; i < pop_number; i++) {
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
	//children.push_back(population[0]);
	for (int i = 0; i < this->pop_number; i++) {
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
	
		DNA child = crossover(parent1, parent2, 0.5, 0.5);
		child.mutate();
		children.push_back(child);
	}

	population = children;
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

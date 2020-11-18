#include <iostream>
#include "functions.h"
#include "Population.h"

int main() {
	srand(time(NULL));
	int dimension = 5;
	float C = 0;

	Population P = Population(200, 0.02, de_jong, dimension, -5.12, 5.12, 3);
	P.calc_fitness(C);
	
	for (int i = 0; i < 2000; i++) {
		DNA top_candidate = P.get_top_candidate();
		cout << i << ' ' << P.get_function_value(top_candidate.get_gene()) << '\n';
		P.natural_selection();
		P.generate();
		P.calc_fitness(C);
	}

	DNA top_candidate = P.get_top_candidate();
	cout << '\n' << P.get_function_value(top_candidate.get_gene());

	return 0;
}
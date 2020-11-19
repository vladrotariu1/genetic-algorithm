#include <iostream>
#include "functions.h"
#include "Population.h"

int main() {
	srand(time(NULL));
	int dimension = 30;
	float C = dimension * 419;

	Population P = Population(1000, 0.02, schwefel, dimension, -500, 500, 3, C);
	P.calc_fitness();

	for (int i = 0; i < 200; i++) {
		DNA top_candidate = P.get_top_candidate();
		cout << i << ' ' << P.get_function_value(top_candidate.get_gene()) << '\n';
		P.natural_selection();
		P.generate();
		P.calc_fitness();
	}

	DNA top_candidate = P.get_top_candidate();
	cout << '\n' << P.get_function_value(top_candidate.get_gene());

	return 0;
}
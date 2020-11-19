#pragma once
#include <cmath>
#include <vector>

#define PI 3.14159265359

using namespace std;

float de_jong(vector<float> parameters, int dimension) {
	float result = 0;
	for (int i = 0; i < dimension; i++) {
		result += pow(parameters[i], 2);
	}

	return result;
}

float rastrigin(vector<float> parameters, int dimension) {
	float result = 10 * dimension;
	for (int i = 0; i < dimension; i++) {
		result += pow(parameters[i], 2) - 10 * cos(2 * PI * parameters[i]);
	}

	return result;
}

float schwefel(vector<float> parameters, int dimension) {
	float result = 0;
	for (int i = 0; i < dimension; i++) {
		result += -1 * (parameters[i] * sin(sqrt(abs(parameters[i]))));
	}

	return result;
}
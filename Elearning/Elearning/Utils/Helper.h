#pragma once

#include "pch.h"

// Test Driven Development (TDD)
// ---> scriem mai intai testul ---> apoi codul

inline double calculateMaxInVector(const std::vector<double>& vector)
{
	if (vector.size() == 0)
		throw std::invalid_argument("Empty vector!"); // #include<stdexcept>
	double maxim = vector[0];
	for (int i = 1;i < vector.size();i++)
		if (vector[i] > maxim)
			maxim = vector[i];
	return maxim;
}

inline double calculateAverageInVector(const std::vector<double>& vector)
{
	if (vector.size() == 0)
		throw std::invalid_argument("Empty vector!");
	double total = 0.0;
	for (int i = 0;i < vector.size();i++)
		total += vector[i];
	return total / vector.size();
}

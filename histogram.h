#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED

#include <vector>

using namespace std;

// Поиск МИНИМУМА И МАКСИМУМА
void find_minmax(const vector<double>& numbers, double& min_values, double& max_values);

// Ширина рамки
size_t line_length(size_t width, size_t block, size_t max_values, size_t limit);

#endif // HISTOGRAM_H_INCLUDED

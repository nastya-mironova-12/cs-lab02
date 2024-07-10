#include "histogram.h"

// Поиск минимума и максимума
void find_minmax(const vector<double>& numbers, double& min_values, double& max_values) {
    if (numbers.size() == 0) {
        min_values = 0;
        max_values = 0;
    }
    else {
        min_values = numbers[0];
        max_values = numbers[0];
        for (double number : numbers) {
            if (number < min_values) {
                min_values = number;
            }
            if (number > max_values) {
                max_values = number;
            }
        }
    }
}

// Ширина рамки
size_t line_length(size_t width, size_t block, size_t max_values, size_t limit) {
    if (max_values > limit) {
        return width + limit * block;
    }
    else {
        return width + max_values * block;
    }
}

#include "histogram.h"

// ����� �������� � ���������
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

#include <iostream>
#include <vector>

using namespace std;


// ���� �����
vector<double> input_numbers(size_t number_values) {
    vector<double> result(number_values);    // ������ �������� (������ �����)
    for (size_t i = 0; i < number_values; i++) { // ����, ����������� ������
        cin >> result[i];   // ���� ��������
    }
    return result;
}

// ����� �������� � ���������
void find_minmax(const vector<double>& numbers, double& min_values, double& max_values) {
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

// ���ר� ����������� ����� � �������� �����������
vector<double> make_histogram(size_t bin_values, const vector<double>& numbers) {
    vector<double> result(bin_values);  // ������/������ ��������
    double numbers_min, numbers_max;
    find_minmax(numbers, numbers_min, numbers_max); // ����� ������� ������ ����������� � ����������� ��������
    for (double number : numbers) { // ������� ���� �������� � �������
        size_t bin = (size_t)((number - numbers_min) / (numbers_max - numbers_min) * bin_values);  // ����������� ������� ������� �� �������� ��������
        if (bin == bin_values) {    // ����� ������� ����� ����� �� ������� �������,
            bin--;          // ��� ��� ���������� � ����� ������� ���������� � ����
        }
        result[bin]++;    // ���������� ������ �������
    }
    return result;
}

// ����������� �����������
void show_histogram_text(const vector<double>& bins) {
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

    size_t max_count = 0;
    for (size_t bin : bins) {   // ����� ����������� ����������
        if (bin > max_count) {  // ����� � ����� �������
            max_count = bin;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;   // ����� �� ��������� ���������������

    for (size_t bin : bins) {
        if (bin < 100) {    // ������������
            cout << ' ';    // ��������
        }                   // ��������
        if (bin < 10) {     // �� ���
            cout << ' ';    // ���������
        }
        cout << bin << "|";

        size_t height = bin;    // ������ ������� (���������� ���������)
        if (scaling_needed) {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_count);   // ���������������
        }                                                                   // ������ �������

        for (size_t i = 0; i < height; i++) {
            cout << '*';    // ����� (��������) �������
        }
        cout << '\n';
    }
}


int main() {
    // ���� ������
    size_t number_count, bin_count;
	cerr << "Enter number count: ";
	cin >> number_count;    // ���� ���������� ��������
	cerr << "Enter numbers: ";
	const auto numbers = input_numbers(number_count);   // ������ �������� (���� �����)
	cerr << "Enter column count: ";
	cin >> bin_count;   // ���� ���������� ������ (��������)

    // ��������� ������
    const auto bins = make_histogram(bin_count, numbers);   // ������ ��������� ����� � ������ �������

    // ����� ������
    show_histogram_text(bins);  // ����������� �����������
}

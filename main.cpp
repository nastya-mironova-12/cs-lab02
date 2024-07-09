#include <iostream>
#include <vector>
#include <string>

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
vector<size_t> make_histogram(size_t bin_values, const vector<double>& numbers) {
    vector<size_t> result(bin_values);  // ������/������ ��������
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

// ����� ��������� SVG
void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

// ����� ��������� SVG
void svg_end() {
    cout << "</svg>\n";
}

// ������� ������ ��������� SVG

//����� �������� � ��������
void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>" << '\n';
}

//����� �������������� � SVG
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "#F09DEC") {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />" << '\n';
}

// ����������� ����� �����������
void show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    const size_t SCREEN_WIDTH = 80; // ���������������
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

    size_t max_count = 0;
    for (size_t bin : bins) {   // ����� ����������� ����������
        if (bin > max_count) {  // ����� � ����� �������
            max_count = bin;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;   // ����� �� ��������� ���������������

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins) {
        size_t height = bin;    // ������ �������
        if (scaling_needed) {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_count);   // ���������������
        }                                                                      // ������ �������
        const double bin_width = BLOCK_WIDTH * height;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
        top += BIN_HEIGHT;
    }
    svg_end();
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
    show_histogram_svg(bins);  // ����������� �����������
}

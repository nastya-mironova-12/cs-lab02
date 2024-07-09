#include <iostream>
#include <vector>
#include "histogram.h"
#include "SVG.h"

using namespace std;


// ВВОД ЧИСЕЛ
vector<double> input_numbers(size_t number_values) {
    vector<double> result(number_values);    // Массив значений (вектор чисел)
    for (size_t i = 0; i < number_values; i++) { // Цикл, заполняющий массив
        cin >> result[i];   // Ввод значений
    }
    return result;
}

// РАСЧЁТ КОЛЛИЧЕСТВА ЧИСЕЛ В СТОЛБЦАХ ГИСТОГРАММЫ
vector<size_t> make_histogram(size_t bin_values, const vector<double>& numbers) {
    vector<size_t> result(bin_values);  // Массив/вектор столбцов
    double numbers_min, numbers_max;
    find_minmax(numbers, numbers_min, numbers_max); // Вызов функции поиска наибольшего и наименьшего значения
    for (double number : numbers) { // Перебор вхех значений в массиве
        size_t bin = (size_t)((number - numbers_min) / (numbers_max - numbers_min) * bin_values);  // Определение индекса столбца по значению элемента
        if (bin == bin_values) {    // Номер столбца может выйти за пределы вектора,
            bin--;          // так как индексация в нашем векторе начинаестя с нуля
        }
        result[bin]++;    // Увеличение высоты столбца
    }
    return result;
}

// ОТОБРАЖЕНИЕ ГИСТОГРАММЫ (ввиде звёздочек)
void show_histogram_text(const vector<double>& bins) {
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

    size_t max_count = 0;
    for (size_t bin : bins) {   // Поиск наибольшего количества
        if (bin > max_count) {  // чисел в одной корзине
            max_count = bin;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;   // Нужно ли применять масштабирование

    for (size_t bin : bins) {
        if (bin < 100) {    // Выравнивание
            cout << ' ';    // подписей
        }                   // столбцов
        if (bin < 10) {     // до трёх
            cout << ' ';    // знакомест
        }
        cout << bin << "|";

        size_t height = bin;    // Высота столбца (количество звездочек)
        if (scaling_needed) {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_count);   // Масштабирование
        }                                                                   // высоты столбца

        for (size_t i = 0; i < height; i++) {
            cout << '*';    // Вывод (звёздочек) столбца
        }
        cout << '\n';
    }
}


int main() {
    // ВВОД ДАННЫХ
    size_t number_count, bin_count;
	cerr << "Enter number count: ";
	cin >> number_count;    // Ввод количества значений
	cerr << "Enter numbers: ";
	const auto numbers = input_numbers(number_count);   // Массив значений (ввод чисел)
	cerr << "Enter column count: ";
	cin >> bin_count;   // Ввод количества корзин (столбцов)

    // ОБРАБОТКА ДАННЫХ
    if (bin_count == 0) {
        cerr << "Error: you have entered the number of columns = 0.";
    }
    const auto bins = make_histogram(bin_count, numbers);   // Вектор количеств чисел в каждой корзине

    // ВЫВОД ДАННЫХ
    show_histogram_svg(bins);  // Отображение гистограммы
}

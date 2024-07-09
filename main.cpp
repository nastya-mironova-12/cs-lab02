#include <iostream>
#include <vector>
#include <string>

using namespace std;


// ВВОД ЧИСЕЛ
vector<double> input_numbers(size_t number_values) {
    vector<double> result(number_values);    // Массив значений (вектор чисел)
    for (size_t i = 0; i < number_values; i++) { // Цикл, заполняющий массив
        cin >> result[i];   // Ввод значений
    }
    return result;
}

// ПОИСК МИНИМУМА И МАКСИМУМА
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

// ВЫВОД ЗАГОЛОВКА SVG
void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

// ВЫВОД ОКОНЧАНИЯ SVG
void svg_end() {
    cout << "</svg>\n";
}

// ФУНКЦИИ ВЫВОДА ЭЛЕМЕНТОВ SVG

//Вывод подписей к столбцам
void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>" << '\n';
}

//Вывод прямоугольника в SVG
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "#F09DEC") {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />" << '\n';
}

// ГРАФИЧЕСКИЙ ВЫВОД ГИСТОГРАММЫ
void show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    const size_t SCREEN_WIDTH = 80; // Масштабирование
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

    size_t max_count = 0;
    for (size_t bin : bins) {   // Поиск наибольшего количества
        if (bin > max_count) {  // чисел в одной корзине
            max_count = bin;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;   // Нужно ли применять масштабирование

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins) {
        size_t height = bin;    // Высота столбца
        if (scaling_needed) {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_count);   // Масштабирование
        }                                                                      // высоты столбца
        const double bin_width = BLOCK_WIDTH * height;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
        top += BIN_HEIGHT;
    }
    svg_end();
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
    const auto bins = make_histogram(bin_count, numbers);   // Вектор количеств чисел в каждой корзине

    // ВЫВОД ДАННЫХ
    show_histogram_svg(bins);  // Отображение гистограммы
}

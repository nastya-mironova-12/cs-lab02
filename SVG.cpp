#include "SVG.h"
#include "histogram.h"

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

// Вывод подписей к столбцам
void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>" << '\n';
}

// Вывод прямоугольника в SVG
void svg_rect(double x, double y, double width, double height, string stroke, string fill) {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />" << '\n';
}

// Вывод рамки вокруг гистограммы, с использованием пунктирных линий
void svg_line_frame(double k, double a, double b, string stroke, string dasharray) {
    cout << "<line x1='" << k << "' y1='" << k << "' x2='" << k << "' y2='" << a << "' stroke='" << stroke << "' stroke-dasharray='" << dasharray << "' />" << '\n';
    cout << "<line x1='" << k << "' y1='" << a << "' x2='" << b << "' y2='" << a << "' stroke='" << stroke << "' stroke-dasharray='" << dasharray << "' />" << '\n';
    cout << "<line x1='" << b << "' y1='" << a << "' x2='" << b << "' y2='" << k << "' stroke='" << stroke << "' stroke-dasharray='" << dasharray << "' />" << '\n';
    cout << "<line x1='" << b << "' y1='" << k << "' x2='" << k << "' y2='" << k << "' stroke='" << stroke << "' stroke-dasharray='" << dasharray << "' />" << '\n';
}

// ГРАФИЧЕСКИЙ ВЫВОД ГИСТОГРАММЫ
void show_histogram_svg(const vector<size_t>& bins) {
    const auto TEXT_BASELINE = 20;  // База/основа (отступы/левая верхняя граница)
    const auto TEXT_WIDTH = 65;     // Координата x для столбцов
    const auto BIN_HEIGHT = 30;     // Высота ячейки (столбца) или Координата x для тескта
    const auto BLOCK_WIDTH = 10;    // Ширина блока
    const auto IMAGE_WIDTH = 400;   // Ширина изображения
    const auto IMAGE_HEIGHT = bins.size() * BIN_HEIGHT + 50;    // Высота изображения
    const auto LINE_HEIGHT = IMAGE_HEIGHT - 1; // Высота рамки
    const auto LINE_WIDTH = 79;    // Коэффициент ширины рамки
    const size_t MAX_ASTERISK = 32; // Коэффициент масштабирования

    // МАСШТАБИРОВАНИЕ
    size_t max_count = 0;
    for (size_t bin : bins) {   // Поиск наибольшего количества
        if (bin > max_count) {  // чисел в одной корзине
            max_count = bin;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;   // Нужно ли применять масштабирование
    size_t length = line_length(LINE_WIDTH, BLOCK_WIDTH, max_count, MAX_ASTERISK);  // Ширина рамки

    // ДЕЙСТВИЯ С SVG ФУНКЦИЯМИ
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);   // Функция вывода начала SVG изображения для страницы в браузере (xml)
    svg_line_frame(TEXT_BASELINE, LINE_HEIGHT, length);    //  Функция вывода рамки пунктирной линиею
    double top = TEXT_BASELINE * 2 - 3; // Шаг сверху
    for (size_t bin : bins) {
        size_t height = bin;    // Высота столбца
        if (scaling_needed) {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_count);   // Масштабирование высоты столбца
        }
        const double bin_width = BLOCK_WIDTH * height;  // Ширина ячейки (столбца)
        svg_text(BIN_HEIGHT, top + TEXT_BASELINE, to_string(bin));  // Функция вывода подписей столбцов
        svg_rect(TEXT_WIDTH, top - 2, bin_width, BIN_HEIGHT);   // Функция вывода геометрических фигур (столбцов)
        top += BIN_HEIGHT;
    }
    svg_end();  // Функция вывода конца SVG изображения
}

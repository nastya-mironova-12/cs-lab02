#include "SVG.h"

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

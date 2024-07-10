#include "SVG.h"
#include "histogram.h"

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

// ����� �������� � ��������
void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>" << '\n';
}

// ����� �������������� � SVG
void svg_rect(double x, double y, double width, double height, string stroke, string fill) {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />" << '\n';
}

// ����� ����� ������ �����������, � �������������� ���������� �����
void svg_line_frame(double k, double a, double b, string stroke, string dasharray) {
    cout << "<line x1='" << k << "' y1='" << k << "' x2='" << k << "' y2='" << a << "' stroke='" << stroke << "' stroke-dasharray='" << dasharray << "' />" << '\n';
    cout << "<line x1='" << k << "' y1='" << a << "' x2='" << b << "' y2='" << a << "' stroke='" << stroke << "' stroke-dasharray='" << dasharray << "' />" << '\n';
    cout << "<line x1='" << b << "' y1='" << a << "' x2='" << b << "' y2='" << k << "' stroke='" << stroke << "' stroke-dasharray='" << dasharray << "' />" << '\n';
    cout << "<line x1='" << b << "' y1='" << k << "' x2='" << k << "' y2='" << k << "' stroke='" << stroke << "' stroke-dasharray='" << dasharray << "' />" << '\n';
}

// ����������� ����� �����������
void show_histogram_svg(const vector<size_t>& bins) {
    const auto TEXT_BASELINE = 20;  // ����/������ (�������/����� ������� �������)
    const auto TEXT_WIDTH = 65;     // ���������� x ��� ��������
    const auto BIN_HEIGHT = 30;     // ������ ������ (�������) ��� ���������� x ��� ������
    const auto BLOCK_WIDTH = 10;    // ������ �����
    const auto IMAGE_WIDTH = 400;   // ������ �����������
    const auto IMAGE_HEIGHT = bins.size() * BIN_HEIGHT + 50;    // ������ �����������
    const auto LINE_HEIGHT = IMAGE_HEIGHT - 1; // ������ �����
    const auto LINE_WIDTH = 79;    // ����������� ������ �����
    const size_t MAX_ASTERISK = 32; // ����������� ���������������

    // ���������������
    size_t max_count = 0;
    for (size_t bin : bins) {   // ����� ����������� ����������
        if (bin > max_count) {  // ����� � ����� �������
            max_count = bin;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;   // ����� �� ��������� ���������������
    size_t length = line_length(LINE_WIDTH, BLOCK_WIDTH, max_count, MAX_ASTERISK);  // ������ �����

    // �������� � SVG ���������
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);   // ������� ������ ������ SVG ����������� ��� �������� � �������� (xml)
    svg_line_frame(TEXT_BASELINE, LINE_HEIGHT, length);    //  ������� ������ ����� ���������� ������
    double top = TEXT_BASELINE * 2 - 3; // ��� ������
    for (size_t bin : bins) {
        size_t height = bin;    // ������ �������
        if (scaling_needed) {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_count);   // ��������������� ������ �������
        }
        const double bin_width = BLOCK_WIDTH * height;  // ������ ������ (�������)
        svg_text(BIN_HEIGHT, top + TEXT_BASELINE, to_string(bin));  // ������� ������ �������� ��������
        svg_rect(TEXT_WIDTH, top - 2, bin_width, BIN_HEIGHT);   // ������� ������ �������������� ����� (��������)
        top += BIN_HEIGHT;
    }
    svg_end();  // ������� ������ ����� SVG �����������
}

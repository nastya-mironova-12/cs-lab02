#pragma once

#include <vector>
#include <string>
#include <iostream>

using namespace std;

// ВЫВОД ЗАГОЛОВКА SVG
void svg_begin(double width, double height);

// ВЫВОД ОКОНЧАНИЯ SVG
void svg_end();

// Вывод подписей к столбцам
void svg_text(double left, double baseline, string text);

// Вывод прямоугольника в SVG
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "#F09DEC");

// Вывод рамки вокруг гистограммы, с использованием пунктирных линий
void svg_line_frame(double k, double a, double b, string stroke = "black", string dasharray = "10 10");

// ГРАФИЧЕСКИЙ ВЫВОД ГИСТОГРАММЫ
void show_histogram_svg(const vector<size_t>& bins);

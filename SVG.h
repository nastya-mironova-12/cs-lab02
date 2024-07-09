#pragma once

#include <vector>
#include <string>
#include <iostream>

using namespace std;

// ÂÛÂÎÄ ÇÀÃÎËÎÂÊÀ SVG
void svg_begin(double width, double height);

// ÂÛÂÎÄ ÎÊÎÍ×ÀÍÈ‗ SVG
void svg_end();

// Âûגמה ןמהןטסוי ך סעמכבצאל
void svg_text(double left, double baseline, string text);

// Âûגמה ןנÿלמףדמכüםטךא ג SVG
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "#F09DEC");

// ÃÐÀÔÈ×ÅÑÊÈÉ ÂÛÂÎÄ ÃÈÑÒÎÃÐÀÌÌÛ
void show_histogram_svg(const vector<size_t>& bins);

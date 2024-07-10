#pragma once

#include <vector>
#include <string>
#include <iostream>

using namespace std;

// ����� ��������� SVG
void svg_begin(double width, double height);

// ����� ��������� SVG
void svg_end();

// ����� �������� � ��������
void svg_text(double left, double baseline, string text);

// ����� �������������� � SVG
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "#F09DEC");

// ����� ����� ������ �����������, � �������������� ���������� �����
void svg_line_frame(double k, double a, double b, string stroke = "black", string dasharray = "10 10");

// ����������� ����� �����������
void show_histogram_svg(const vector<size_t>& bins);

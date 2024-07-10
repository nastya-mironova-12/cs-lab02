#include "histogram.h"

#include <cassert>

void test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void test_negative() {
	double min = 0;
	double max = 0;
	find_minmax({ -1, -2, -3 }, min, max);
	assert(min == -3);
	assert(max == -1);
}

void test_identical() {
	double min = 0;
	double max = 0;
	find_minmax({ 2, 2, 2 }, min, max);
	assert(min == 2);
	assert(max == 2);
}

void test_alone() {
	double min = 0;
	double max = 0;
	find_minmax({1}, min, max);
	assert(min == 1);
	assert(max == 1);
}

void test_empty() {
	double min = 0;
	double max = 0;
	find_minmax({}, min, max);
	assert(min == 0);
	assert(max == 0);
}

void test_little() {
    size_t width = 50;
    size_t block = 10;
    size_t max_values = 20;
    size_t limit = 30;
    size_t length = line_length(width, block, max_values, limit);
    assert(length == 250);
}

void test_big() {
    size_t width = 40;
    size_t block = 10;
    size_t max_values = 150;
    size_t limit = 30;
    size_t length = line_length(width, block, max_values, limit);
    assert(length == 340);
}

void test_equal() {
    size_t width = 150;
    size_t block = 5;
    size_t max_values = 30;
    size_t limit = 30;
    size_t length = line_length(width, block, max_values, limit);
    assert(length == 300);
}

int main() {
    test_positive();
    test_negative();
	test_identical();
	test_alone();
	test_empty();

	test_little();
	test_big();
	test_equal();
}

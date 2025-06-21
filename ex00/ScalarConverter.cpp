#include "ScalarConverter.hpp"

#include <iostream>

using std::cout;
using std::endl;
using std::string;

ScalarConverter::ScalarConverter() {
}

ScalarConverter::~ScalarConverter() {
}

ScalarConverter::ScalarConverter(const ScalarConverter &other) {
	(void)other;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other) {
	(void)other;
	return *this;
}

static void print(char *c, int *i, float *f, double *d) {
	
}

void ScalarConverter::convert(const string &literal) {
	cout << static_cast<char>(literal[0]);
}

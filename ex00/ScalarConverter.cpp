#include "ScalarConverter.hpp"

#include <iostream>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::exception;
using std::istringstream;
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

void ScalarConverter::print(char c, int i, float f, double d, unsigned long flags) {
	cout << "char: ";
	if (flags & C_IMPOSSIBLE) {
		cout << "impossible";
	} else if (flags & C_NONPRINTABLE) {
		cout << "non displayable";
	} else {
		cout << "'" << c << "'";
	}
	cout << endl << "int: ";
	if (flags & I_IMPOSSIBLE) {
		cout << "impossible";
	} else {
		cout << i;
	}
	cout << endl << "float: ";
	if (flags & F_IMPOSSIBLE) {
		cout << "impossible";
	} else if (flags & F_PLUSINF) {
		cout << "+inf";
	} else if (flags & F_MINUSINF) {
		cout << "-inf";
	} else if (flags & F_NAN) {
		cout << "nan";
	} else {
		cout << f << "f";
	}
	cout << endl << "double: ";
	if (flags & D_IMPOSSIBLE) {
		cout << "impossible";
	} else if (flags & D_PLUSINF) {
		cout << "+inf";
	} else if (flags & D_MINUSINF) {
		cout << "-inf";
	} else if (flags & D_NAN) {
		cout << "nan";
	} else {
		cout << d;
	}
	cout << endl;
}

/*
 * returns: 0 if zero, 1 if not zero, -1 if invalid
 */
int ScalarConverter::tryZero(const string &literal) {
	const int SIGNS = 0;
	const int BEFORE_DOT = 1;
	const int AFTER_DOT = 2;
	int stage = SIGNS;
	int sign = 1;
	for (size_t i = 0; i < literal.length(); ++i) {
		if (literal[i] == '-') {
			if (stage == SIGNS) {
				sign *= -1;
			} else {
				return -1;
			}
		} else if (literal[i] == '+') {
			if (stage != SIGNS) {
				return -1;
			}
		} else if (isdigit(literal[i])) {
			if (literal[i] != '0') {
				return 1;
			}
			if (stage == SIGNS) {
				stage = BEFORE_DOT;
			}
		} else if (literal[i] == '.') {
			if (stage == AFTER_DOT) {
				return -1;
			} else {
				stage = AFTER_DOT;
			}
		} else if (literal[i] == 'f') {
			if (stage == SIGNS) {
				return -1; // no digits
			}
			if (i != literal.length() - 1) {
				return -1;
			}
		} else {
			return -1;
		}
	}
	print(0, 0, 0.0f, 0.0, C_NONPRINTABLE);
	return (0);
}

void ScalarConverter::convert(const string &literal) {
	if (ScalarConverter::tryZero(literal) == 0) {
		return;
	}
	unsigned long flags = 0;
	char c = literal[0];
	if (c < 0 || c > 127 || literal.length() > 1) {
		flags |= C_IMPOSSIBLE;
	} else if (!isprint(c)) {
		flags |= C_NONPRINTABLE;
	} else {
		int i = static_cast<int>(c);
		float f = static_cast<float>(c);
		double d = static_cast<double>(c);
		print(c, i, f, d, flags);
		return;
	}
	double d = strtod(literal.c_str(), NULL);
	if (d == 0) {
		flags |= D_IMPOSSIBLE;
	} else if (d == 1.0 / 0.0) {
		flags |= D_PLUSINF;
	} else if (d == -1.0 / 0.0) {
		flags |= D_MINUSINF;
	} else if (d != d) {
		flags |= D_NAN;
	}
	int i = static_cast<int>(d);
	if (i == 0) {
		flags |= I_IMPOSSIBLE;
	} else if (i < -2147483648 || i > 2147483647) {
		flags |= I_IMPOSSIBLE;
	}
	float f = static_cast<float>(d);
	if (f == 0) {
		flags |= F_IMPOSSIBLE;
	} else if (f == 1.0f / 0.0f) {
		flags |= F_PLUSINF;
	} else if (f == -1.0f / 0.0f) {
		flags |= F_MINUSINF;
	} else if (f != f) {
		flags |= F_NAN;
	}
	print(c, i, f, d, flags);
}

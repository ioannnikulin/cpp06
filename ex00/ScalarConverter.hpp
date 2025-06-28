#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

using std::string;

class ScalarConverter {
private:
	ScalarConverter();
	~ScalarConverter();
	ScalarConverter(const ScalarConverter &other);
	ScalarConverter &operator=(const ScalarConverter &other);
	static const unsigned long D_IMPOSSIBLE = 1;
	static const unsigned long I_IMPOSSIBLE = 2;
	static const unsigned long C_IMPOSSIBLE = 4;
	static const unsigned long C_NONPRINTABLE = 8;
	static const unsigned long F_IMPOSSIBLE = 16;
	static const unsigned long F_PLUSINF = 32;
	static const unsigned long F_MINUSINF = 64;
	static const unsigned long F_NAN = 128;
	static const unsigned long D_PLUSINF = 256;
	static const unsigned long D_MINUSINF = 512;
	static const unsigned long D_NAN = 1024;
	static void print(char c, int i, float f, double d, unsigned long flags);
	static int tryZero(const string &literal);
	static int tryInf(const string &literal);

public:
	static void convert(const string &literal);
};

#endif

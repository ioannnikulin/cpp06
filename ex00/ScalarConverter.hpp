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

public:
	static void convert(const string &literal);
};

#endif

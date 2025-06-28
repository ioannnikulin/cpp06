#include "ScalarConverter.hpp"

#include <iostream>
#include <sstream>
#include <streambuf>
#include <cassert> // should be included LAST

using std::cout;
using std::endl;
using std::streambuf;
using std::ostringstream;

static void autotest() {
	streambuf *originalCout = cout.rdbuf();
	ostringstream captured;
	cout.rdbuf(captured.rdbuf());

	ScalarConverter::convert("");
	assert(captured.str() == "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n");
	captured.str("");
	
	ScalarConverter::convert("c");
	assert(captured.str() == "char: 'c'\nint: 99\nfloat: 99f\ndouble: 99\n");
	captured.str("");
	
	ScalarConverter::convert("##");
	assert(captured.str() == "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n");
	captured.str("");

	string zeros[] = {
		"0f"
		, "00f"
		, "0.0f"
		, "0.00000000000000000f"
		, "000.00000000000000000f"
		, ".00000000000000000f"
		, "0000.f"
		, "+0f"
		, "-+--+00f"
	};
	for (unsigned int i = 0; i < sizeof(zeros)/sizeof(string); ++i) {
		ScalarConverter::convert(zeros[i]);
		assert(captured.str() == "char: non displayable\nint: 0\nfloat: 0f\ndouble: 0\n");
		captured.str("");
		ScalarConverter::convert(zeros[i].substr(0, zeros[i].length() - 1));
		assert(captured.str() == "char: non displayable\nint: 0\nfloat: 0f\ndouble: 0\n");
		captured.str("");
	}

	ScalarConverter::convert("42.0f");
	assert(captured.str() == "char: '*'\nint: 42\nfloat: 42f\ndouble: 42\n");
	captured.str("");
	
	ScalarConverter::convert("-42.0f");
	assert(captured.str() == "char: impossible\nint: -42\nfloat: -42f\ndouble: -42\n");
	captured.str("");

	ScalarConverter::convert("-42.0001f");
	assert(captured.str() == "char: impossible\nint: -42\nfloat: -42.00009918212890625f\ndouble: -42.00010000000000332\n");
	captured.str("");

	ScalarConverter::convert("-42.00001f");
	assert(captured.str() == "char: impossible\nint: -42\nfloat: -42.000011444091796875f\ndouble: -42.000010000000003174\n");
	captured.str("");

	ScalarConverter::convert("-42.0001");
	assert(captured.str() == "char: impossible\nint: -42\nfloat: -42.00009918212890625f\ndouble: -42.00010000000000332\n");
	captured.str("");

	ScalarConverter::convert("-42.00001");
	assert(captured.str() == "char: impossible\nint: -42\nfloat: -42.000011444091796875f\ndouble: -42.000010000000003174\n");
	captured.str("");

	ScalarConverter::convert("789.123456f");
	assert(captured.str() == "char: impossible\nint: 789\nfloat: 789.12347412109375f\ndouble: 789.12345600000003287\n");
	captured.str("");

	string weird[] = {
		"+inff"
		, "-inff"
		, "nanf"
	};
	for (unsigned int i = 0; i < sizeof(weird)/sizeof(string); ++i) {
		ScalarConverter::convert(weird[i]);
		ostringstream exp;
		exp << "char: impossible\n"
			<< "int: impossible\n"
			<< "float: " << weird[i] << "\n"
			<< "double: " << weird[i].substr(0, weird[i].length() - 1) << "\n";
		assert(captured.str() == exp.str());
		captured.str("");
	}

	cout.rdbuf(originalCout);
}

int main(int argc, char **argv) {
	if (argc == 1) {
		autotest();
		return (0);
	}
	if (argc != 2) {
		cout << "Usage: '" << argv[0] << " <literal>' for manual conversion, or '" << argv[0] << "' for silent autotests" << endl;
		return (1);
	}
	ScalarConverter::convert(argv[1]);
	return (0);
}

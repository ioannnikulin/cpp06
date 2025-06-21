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
	for (int i = 0; i < 9; ++i) {
		ScalarConverter::convert(zeros[i]);
		assert(captured.str() == "char: non displayable\nint: 0\nfloat: 0f\ndouble: 0\n");
		captured.str("");
		ScalarConverter::convert(zeros[i].substr(0, zeros[i].length() - 1));
		assert(captured.str() == "char: non displayable\nint: 0\nfloat: 0f\ndouble: 0\n");
		captured.str("");
	}

	ScalarConverter::convert("42.0f");
	assert(captured.str() == "char: *\nint: 42\nfloat: 42\ndouble: 42\n");
	captured.str("");
	
	ScalarConverter::convert("-42.0f");
	assert(captured.str() == "char: impossible\nint: -42\nfloat: -42\ndouble: -42\n");
	captured.str("");

	cout.rdbuf(originalCout);
}

int main() {
	ScalarConverter::convert("0f");
	ScalarConverter::convert("0.0f");
	ScalarConverter::convert("0.000000000000000001f");
	ScalarConverter::convert("42.000000000000000001f");
	ScalarConverter::convert("42.000000000000000001f");
	autotest();
	return (0);
}

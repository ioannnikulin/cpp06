#include "ScalarConverter.hpp"

#include <iostream>
#include <sstream>
#include <streambuf>
#include <cassert> // should be included LAST

using std::cout;
using std::endl;
using std::streambuf;
using std::ostringstream;

int main() {
	streambuf *originalCout = cout.rdbuf();
	ostringstream captured;
	cout.rdbuf(captured.rdbuf());

	ScalarConverter::convert("42.0f");
	assert(captured.str() == "42.0f");
	captured.str("");
	
	ScalarConverter::convert("-42.0f");
	assert(captured.str() == "-42.0f");
	captured.str("");

	cout.rdbuf(originalCout);
	assert(true);
	return (0);
}

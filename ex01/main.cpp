#include <iostream>
#include <sstream>
#include <cassert>

#include "Serializer.hpp"

using std::cout;
using std::endl;
using std::ostringstream;
using std::streambuf;

int main() {
	streambuf *originalCout = cout.rdbuf();
	ostringstream captured;
	cout.rdbuf(captured.rdbuf());

	Data data;
	data.value = 42;
	uintptr_t serialized = Serializer::serialize(&data);
	Data* deserialized = Serializer::deserialize(serialized);
	assert(deserialized->value == data.value);
	assert(deserialized == &data);

	cout.rdbuf(originalCout);
	return (0);
}

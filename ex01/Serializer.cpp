#include "Serializer.hpp"

Serializer::Serializer() {
}

Serializer::~Serializer() {
}

Serializer::Serializer(const Serializer &other) {
	(void)other;
}

Serializer &Serializer::operator=(const Serializer &other) {
	(void)other;
	return *this;
}

uintptr_t Serializer::serialize(Data* ptr) {
	uintptr_t raw = reinterpret_cast<uintptr_t>(ptr);
	return raw;
}

Data* Serializer::deserialize(uintptr_t raw) {
	Data* dataPtr = reinterpret_cast<Data*>(raw);
	return dataPtr;
}

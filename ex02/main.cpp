#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <cassert>

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::clog;
using std::streambuf;
using std::string;
using std::ostringstream;

static Base* generate(void) {
	int random = rand() % 3;
	if (random == 0) {
		clog << "Generating A" << endl;
		return new A();
	}
	else if (random == 1) {
		clog << "Generating B" << endl;
		return new B();
	}
	else {
		clog << "Generating C" << endl;
		return new C();
	}
}

static void identify(Base* p) {
	try {
		A* a = dynamic_cast<A*>(p);
		if (a) {
			cout << "A" << endl;
			return ;
		}
	} catch (...) {
	}
	try {
		B* b = dynamic_cast<B*>(p);
		if (b) {
			cout << "B" << endl;
			return ;
		}
	} catch (...) {
	}
	try {
		C* c = dynamic_cast<C*>(p);
		if (c) {
			cout << "C" << endl;
			return ;
		}
	} catch (...) {	
	}
	cout << "Unknown type" << endl;
}

static void identify(Base& p) {
	try {
		A& a = dynamic_cast<A&>(p);
		cout << "A" << endl;
		(void)a;
		return ;
	} catch (...) {
	}
	try {
		B& b = dynamic_cast<B&>(p);
		cout << "B" << endl;
		(void)b;
		return ;
	} catch (...) {
	}
	try {
		C& c = dynamic_cast<C&>(p);
		cout << "C" << endl;
		(void)c;
		return ;
	} catch (...) {	
	}
	cout << "Unknown type" << endl;
}

static void autotest() {
	streambuf *originalClog = clog.rdbuf();
	ostringstream capturedClog;
	clog.rdbuf(capturedClog.rdbuf());

	streambuf *originalCout = cout.rdbuf();
	ostringstream capturedCout;
	cout.rdbuf(capturedCout.rdbuf());

	Base *base = new Base();
	identify(base);
	delete base;

	for (int i = 0; i < 10; ++i) {
		Base* basePtr = generate();
		identify(basePtr);
		if (capturedClog.str().find("A") != string::npos) {
			assert(capturedCout.str().find("A") != string::npos);
		} else if (capturedClog.str().find("B") != string::npos) {
			assert(capturedCout.str().find("B") != string::npos);
		} else if (capturedClog.str().find("C") != string::npos) {
			assert(capturedCout.str().find("C") != string::npos);
		} else {
			assert(capturedCout.str().find("Unknown type") != string::npos);
		}
		capturedCout.str("");
		identify(*basePtr);
		if (capturedClog.str().find("A") != string::npos) {
			assert(capturedCout.str().find("A") != string::npos);
		} else if (capturedClog.str().find("B") != string::npos) {
			assert(capturedCout.str().find("B") != string::npos);
		} else if (capturedClog.str().find("C") != string::npos) {
			assert(capturedCout.str().find("C") != string::npos);
		} else {
			assert(capturedCout.str().find("Unknown type") != string::npos);
		}
		delete basePtr;
		capturedCout.str("");
		capturedClog.str("");
	}

	cout.rdbuf(originalCout);
	clog.rdbuf(originalClog);
}

int main() {
	srand(time(NULL));

	autotest();
	
	return (0);
}

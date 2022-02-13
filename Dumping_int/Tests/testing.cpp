#include <iostream>
#include "../Int/my_int.h"
#include "testing.h"

#define VAR(type, name, value) type name(value, #name)

void testing() {
	std::cout << __PRETTY_FUNCTION__ << "\n";

	VAR(Int, a, 10);
	VAR(Int, b, 20);

	printf("\n");

	b = a;

	// VAR(Int, c, 0);
	// c = a + b;
}
#include <iostream>
#include "../Int/my_int.h"
#include "testing.h"

#define VAR(type, name, value) type name(value, #name)

Int nothing(Int var) {
	return var;
}

void testing() {
	std::cout << __PRETTY_FUNCTION__ << "\n";

	VAR(Int, a, 10);
	VAR(Int, b, 20);
	VAR(Int, d, 30);

	printf("\n");

	// b = a;
	// b = nothing(a);

	VAR(Int, c, 0);
	c = (a + b) * d;
}
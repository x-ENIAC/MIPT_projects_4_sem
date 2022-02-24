#include <iostream>
#include "../Int/my_int.h"
#include "testing.h"

#define VAR(type, name, value) type name(value, #name)

Int get_var(Int var) {
	return var;
}

Int mult(Int& var) {
	return var * var * 5 + get_var(var) * 3 + 1;
}

void testing() {
	VAR(Int, a, 130);
	VAR(Int, b, 20);

	b = mult(a);
}
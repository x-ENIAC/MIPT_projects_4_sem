#include <iostream>
#include "../Int/my_int.h"
#include "testing.h"
#include "../Dumper/calling_trace.h"

#define VAR(type, name, value) type name(value, #name)
#define BEGIN_ANY_FUNC Function_name_sender sender(__FUNCTION__); 

// Int create_var() {
// 	VAR(Int, new_var, 10);
// 	return new_var;
// }

// Int get_var(Int var) {
// 	VAR(Int, help, 666);
// 	return help;
// }

// Int sum(Int& a, Int& b) {
// 	BEGIN_ANY_FUNC

// 	Int res = a + b;

// 	return res;
// }

// void testing() {
// VAR(Int, a, 10);
// 	VAR(Int, b, 20);
// 	VAR(Int, c, 100);

// 	c = a + b;
// }

Int get_var(Int var) {
	BEGIN_ANY_FUNC
	
	return var;
}

void testing() {
	VAR(Int, a, 130);
	VAR(Int, b, 20);
	VAR(Int, c, 0);

	c = get_var(a) + get_var(b);
}
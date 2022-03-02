#include <iostream>
#include "../Int/my_int.h"
#include "testing.h"
#include "../Dumper/calling_trace.h"

#define VAR(type, name, value) type name(value, #name)
// #define BEGIN_ANY_FUNC Function_name_sender sender(__FUNCTION__); 

Int create_var() {
	VAR(Int, new_var, 10);
	printf("Definitely here\n");
	return new_var;
}

// Int get_var(Int var) {
// 	return var;
// }

void testing() {
	VAR(Int, a, 130);
	VAR(Int, c, 0);

	c = create_var() + a;
}
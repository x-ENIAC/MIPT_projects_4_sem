#include <iostream>
#include "../Int/my_int.h"
#include "testing.h"
#include "../Dumper/calling_trace.h"
#include "../My_references/my_std_move.h"
#include "../My_references/my_std_forward.h"

#define VAR(type, name, value) type name(value, #name)
#define BEGIN_ANY_FUNC Function_name_sender sender(__FUNCTION__); 

template<class T>
void example_1(T&& arg) {
	BEGIN_ANY_FUNC
	volatile auto new_tmp = arg;
}

template<class T>
void wrapper(T&& arg) {
	BEGIN_ANY_FUNC
	example_1(arg);
}

void testing() {
	VAR(Int, a, 10);
	wrapper(a);
}
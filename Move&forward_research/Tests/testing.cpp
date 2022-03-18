#include <iostream>
#include "testing.h"
#include "../Int/my_int.h"
#include "../Dumper/calling_trace.h"
#include "../My_references/my_std_move.h"
#include "../My_references/my_std_forward.h"

#define VAR(type, name, value) type name(value, #name)
#define BEGIN_ANY_FUNC Function_name_sender sender(__FUNCTION__); 

template<class T>
void example(T&& arg) {
	BEGIN_ANY_FUNC
	volatile auto new_tmp = my_move(arg); // my_move(arg)
}

template<class T>
void wrapper(T&& arg) {
	BEGIN_ANY_FUNC
	example(arg);
}

void testing() {
	VAR(Int, a, 10);
	wrapper(a);
}
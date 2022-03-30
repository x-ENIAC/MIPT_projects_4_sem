#include <iostream>
#include "testing.h"
#include "../Int/my_int.h"
#include "../Dumper/calling_trace.h"
#include "../My_references/my_std_move.h"
#include "../My_references/my_std_forward.h"

#define VAR(type, name, value) type name(value, #name)
#define BEGIN_ANY_FUNC Function_name_sender sender(__FUNCTION__); 

template<class T>
void push_into_container(T arg) {
	BEGIN_ANY_FUNC
	volatile auto new_tmp = arg;
}

template<class T>
void wrapper(T&& arg) {
	push_into_container(my_forward<T>(arg));
}

void testing() {
	VAR(Int, a, 10);

	printf("a = %d\n", a.get_value()); 				// move: 10, forward: 10
	wrapper(a);
	printf("a = %d\n", a.get_value()); 				// move: 0, forward: 10
}




template<class T>
void push_into_container(T arg) {
	BEGIN_ANY_FUNC
	volatile auto new_tmp = arg;
}

template<class T>
void wrapper(T&& arg) {
	push_into_container(my_forward<T>(arg));
}

void testing() {
	VAR(Int, a, 10);

	printf("a = %d\n", a.get_value()); // forward: 10
	wrapper(a);
	printf("a = %d\n", a.get_value()); // forward: 10
}
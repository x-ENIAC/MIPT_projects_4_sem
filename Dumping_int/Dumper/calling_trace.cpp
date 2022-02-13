#include <iostream>
#include "calling_trace.h"
#include "int_dumping.h"

//------------------ [Calling_trace] --------------------------------------

Calling_trace::Calling_trace() {
	functions = new Stack;
}

Calling_trace::~Calling_trace() {
	delete[] functions;
}

void Calling_trace::add_function(Elem_t new_element) {
	$ std::cout << "[Calling_trace] called " << new_element << "\n";
	functions->push(new_element);
}

void Calling_trace::delete_function() {
	functions->pop();
}

Elem_t& Calling_trace::get_last_function() {
	return functions->back();
}

size_t Calling_trace::get_count_functions() const {
	return functions->get_size_stack();
}

//------------------ [Adder_at_trace] --------------------------------------

Adder_at_trace::Adder_at_trace(Elem_t name_func) {
	is_func_added = true;
	Dumper::get_dumper()->get_tracer_functions()->add_function(name_func);
}

Adder_at_trace::~Adder_at_trace() {
	if(is_func_added)
		Dumper::get_dumper()->get_tracer_functions()->delete_function();
	$$
}
#ifndef CALLING_TRACE
#define CALLING_TRACE

#include "../Tools/stack.h"

class Calling_trace {

public:
	Stack* functions;

	Calling_trace();

	~Calling_trace();

	void add_function(Elem_t new_element);

	void delete_function();

	Elem_t& get_last_function();
	
	size_t get_count_functions() const;
};

class Adder_at_trace {

public:
	bool is_func_added;

	Adder_at_trace(Elem_t name_func);
	
	~Adder_at_trace();
};

#endif
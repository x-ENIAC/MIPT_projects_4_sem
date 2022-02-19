#ifndef CALLING_TRACE
#define CALLING_TRACE

#include "../Tools/stack.h"
#include "../Tools/console_colours.h"
#include "../Int/my_int.h"

const int MAX_TRACE_SIZE = 128;

class Calling_trace {

  public:
	Stack* functions;

	Calling_trace();

	~Calling_trace();

	void add_function(Elem_t new_element, const Type_functions type_function, const Console_colours colour);

	void delete_function();

	Elem_t& get_last_function();
	
	size_t get_count_functions() const;
};

class Adder_at_trace {

  public:
	bool is_func_added;

	Adder_at_trace(Elem_t name_func, const Type_functions type_function, const Console_colours colour);
	
	~Adder_at_trace();
};

#endif
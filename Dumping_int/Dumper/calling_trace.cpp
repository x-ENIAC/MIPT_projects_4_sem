#include "calling_trace.h"
#include "int_dumping.h"

//------------------ [Calling_trace] --------------------------------------

Calling_trace::Calling_trace() {
	functions = new Stack;
}

Calling_trace::~Calling_trace() {
	delete functions;
}

void Calling_trace::add_function(Elem_t new_element, 	const Type_functions type_function,
														const Console_colours colour = Console_colours::GREEN) {
	char additionally_info[MAX_TRACE_SIZE] = "";

	$ printf("%s[Calling_trace] %s %s%s\n", console_colours_text[(int)colour], char_type_functions[(int)type_function],
											new_element.c_str(), console_colours_text[(int)Console_colours::RESET]);
	
	Dumper::get_dumper()->get_html_dumper()->dump_indents(Dumper::get_dumper()->get_tracer_functions()->get_count_functions());

	char html_info[MAX_TRACE_SIZE] = "";
	sprintf(html_info, "[Calling_trace] %s %s\n", char_type_functions[(int)type_function], new_element.c_str());

	Dumper::get_dumper()->get_html_dumper()->dump(html_info, colour);

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

Adder_at_trace::Adder_at_trace(Elem_t name_func, 	const Type_functions type_function,
													const Console_colours colour = Console_colours::GREEN) {
	is_func_added = true;
	Dumper::get_dumper()->get_tracer_functions()->add_function(name_func, type_function, colour);
}

Adder_at_trace::~Adder_at_trace() {
	if(is_func_added)
		Dumper::get_dumper()->get_tracer_functions()->delete_function();
	$$
}
#include "int_dumping.h"

Dumper* Dumper::dumper = nullptr;

Dumper* Dumper::get_dumper() {
	if(!dumper)
		dumper = new Dumper();
	return dumper;
}

Calling_trace* Dumper::get_tracer_functions() {
	return tracer_functions;
}

Html_listing* Dumper::get_html_dumper() {
	return html_dumper;
}

Console_colours Dumper::get_colour(const Int_signal& int_signal) {
	switch((int)int_signal) {
		case (int)Int_signal::CONSTRUCT:
			return CONSTRUCTOR_COLOUR;
		case (int)Int_signal::DESTRUCT:
			return DESTRUCTOR_COLOUR;
		case (int)Int_signal::ADD:
		case (int)Int_signal::SUB:
		case (int)Int_signal::MUL:
		case (int)Int_signal::DIV:
		case (int)Int_signal::ASSIGNMENT:
			return OPERATOR_COLOUR;
		case (int)Int_signal::COPY:
			return COPY_COLOUR;
		default:
			return DEFAULT_COLOUR;
	}
}
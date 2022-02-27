#include "int_dumping.h"

Dumper* Dumper::dumper = nullptr;
Dumper_destroyer Dumper::destroyer;

Dumper* Dumper::get_dumper() {
	if(!dumper) {
		dumper = new Dumper();
		destroyer.initialize(dumper);
	}
	return dumper;
}

Calling_trace* Dumper::get_tracer_functions() {
	return tracer_functions;
}

Html_listing* Dumper::get_html_dumper() {
	return html_dumper;
}

Graph_dumper* Dumper::get_graph_dumper() {
	return graph_dumper;
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
		case (int)Int_signal::MOVE:
			return MOVE_COLOUR;
		default:
			return DEFAULT_COLOUR;
	}
}

void Dumper_destroyer::initialize(Dumper* arg_dumper) { 
	dumper = arg_dumper; 
}

Dumper_destroyer::~Dumper_destroyer() { 
	delete dumper; 
}
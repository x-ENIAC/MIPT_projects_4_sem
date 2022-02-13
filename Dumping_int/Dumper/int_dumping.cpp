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
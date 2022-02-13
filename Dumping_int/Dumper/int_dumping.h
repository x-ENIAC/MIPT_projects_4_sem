#include <iostream>
#include <string>
#include "int_signals_default_handler.h"

#ifndef SIGNALS_RECIPIENT_H
#define SIGNALS_RECIPIENT_H

#include "calling_trace.h"

extern const char* signals[];

class Int;

class Dumper : public Signals_default_handler {
  private:
	static Dumper* dumper;
	Calling_trace* tracer_functions;

	Dumper() {
		tracer_functions = new Calling_trace;
	}

	~Dumper() {
		delete tracer_functions;
	}

  public:
	static Dumper* get_dumper();

	Calling_trace* get_tracer_functions();
	
	void signal(const Int& sender, const Int& recipient, const Int_signal int_signal) override {}
};

#endif
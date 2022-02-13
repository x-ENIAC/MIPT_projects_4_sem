#include <iostream>
#include <string>
#include "int_signals_default_handler.h"

#ifndef SIGNALS_RECIPIENT_H
#define SIGNALS_RECIPIENT_H

#include "calling_trace.h"

// #include "int_signals.h"
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
	
	void signal(const Int& sender, const Int& recipient, const Int_signal int_signal) override {
		// printf("%d %s %d\n", sender.get_id(), signals[(int)int_signal], recipient.get_id());
		// std::string message = std::to_string(sender.get_value()) + " " + signals[(int)int_signal] + " " + std::to_string(recipient.get_value()) + "\n";
		// std::cout << signals[(int)int_signal] << " " << signals.size() << "\n";
		// printf(	//"[WAS] Sender: id=%d, value=%d | Recipient: id=%d, value=%d\n"
		// 		"[OPERATION] %s\n",
		// 		//"[NOW] Sender: id=%d, value=%d | Recipient: id=%d, value=%d\n\n", 
		// 		//sender.get_id(), sender. (int)int_signal, signals[(int)int_signal]);
		// 		signals[(int)int_signal]);
		// for(int i = 0; i < 1; ++i)
		// 	printf("%c", signals[(int)int_signal][i]);
	}
};

#endif
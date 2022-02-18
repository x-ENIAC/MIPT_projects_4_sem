#include <iostream>
#include <string>
#include <cstring>
#include "int_signals_default_handler.h"

#ifndef SIGNALS_RECIPIENT_H
#define SIGNALS_RECIPIENT_H

#include "calling_trace.h"
#include "../Tools/console_colours.h"
#include "console.h"
#include "html_listing.h"

extern const char* signals[];

#define SINGLE_PRETTY_ARITHM	\
	printf("%s", ARROWS[1]);

class Int;

class Dumper : public Signals_default_handler {
  private:
	static Dumper* dumper;
	Calling_trace* tracer_functions;
	Html_listing* html_dumper;

	Dumper() {
		tracer_functions = new Calling_trace;
		html_dumper = new Html_listing;
	}

	~Dumper() {
		delete tracer_functions;
		delete html_dumper;
	}

  public:
	static Dumper* get_dumper();

	Calling_trace* get_tracer_functions();

	Html_listing* get_html_dumper();
	
	void signal(const Int& sender, const Int_signal int_signal) override {
		Console_colours colour = get_colour(int_signal);

		//----------------------------- console -----------------------------\\

		$ SINGLE_PRETTY_ARITHM

		printf("%s[%p]: id = %ld, %s=%d%s\n",
			console_colours_text[(int)colour], &sender, sender.get_id(),
			sender.get_name().c_str(), sender.get_value(), console_colours_text[(int)Console_colours::RESET]);

		//------------------------------- html -------------------------------\\

		html_dumper->dump_indents(tracer_functions->get_count_functions());

		char str_dump[256] = {};
		sprintf(str_dump, "%s[%p]: id = %ld, %s=%d\n",
			ARROWS[1], &sender, sender.get_id(), sender.get_name().c_str(), sender.get_value());

		std::string dump_str(str_dump);
		html_dumper->dump(dump_str, colour);

		dump_str.clear();
		dump_str = "\n";
		html_dumper->dump(dump_str, colour);		
	}

	void signal(const Int& sender, const Int_signal int_signal, const Int& other) override {
		Console_colours colour = get_colour(int_signal);

		char first[MAX_SIZE], second[MAX_SIZE];

		if(int_signal == Int_signal::ASSIGNMENT) {
			strcpy(first,  "from");
			strcpy(second, "to  ");
		} else {
			strcpy(first,  "left ");
			strcpy(second, "right");
		}

		//----------------------------- console -----------------------------\\

		$ SINGLE_PRETTY_ARITHM

		printf("%s[%p]: %s id = %ld, %s=%d%s\n", console_colours_text[(int)colour], &sender, first, sender.get_id(),
					sender.get_name().c_str(), sender.get_value(), console_colours_text[(int)Console_colours::RESET]);

		$ SINGLE_PRETTY_ARITHM

		printf("%s[%p]: %s id = %ld, %s=%d%s\n", console_colours_text[(int)colour], &other, second, other.get_id(),
					other.get_name().c_str(), other.get_value(), console_colours_text[(int)Console_colours::RESET]);

		//------------------------------- html -------------------------------\\

		html_dumper->dump_indents(tracer_functions->get_count_functions());

		char str_dump[512] = {};
		sprintf(str_dump, "%s[%p]: %s id = %ld, %s=%d\n", 	ARROWS[1], &sender, first, sender.get_id(),
															sender.get_name().c_str(), sender.get_value());

		std::string dump_str(str_dump);
		html_dumper->dump(dump_str, colour);

		html_dumper->dump_indents(tracer_functions->get_count_functions());

		sprintf(str_dump, "%s[%p]: %s id = %ld, %s=%d\n", 	ARROWS[1], &other, second, other.get_id(),
															other.get_name().c_str(), other.get_value());

		dump_str.clear();
		dump_str = str_dump;
		html_dumper->dump(dump_str, colour);

		dump_str.clear();
		dump_str = "\n";
		html_dumper->dump(dump_str, colour);
	}

	Console_colours get_colour(const Int_signal& int_signal);
};

#endif
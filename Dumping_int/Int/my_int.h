#ifndef MY_INT_H
#define MY_INT_H

#include <cstdio>
#include <string>
#include "../Tools/console_colours.h"
#include "../Dumper/int_signals_default_handler.h"

class Signals_default_handler;

extern size_t indents;

#define $ 																					\
	indents = Dumper::get_dumper()->get_tracer_functions()->get_count_functions();			\
	for(int i = 0; i < indents; ++i)														\
		printf("\t");

#define $$ printf("\n");

const Console_colours CONSTRUCTOR_COLOUR = Console_colours::BOLDGREEN;
const Console_colours ARGUMENTS_COLOUR = Console_colours::BOLDYELLOW;
const Console_colours DESTRUCTOR_COLOUR = Console_colours::BOLDMAGENTA;
const Console_colours OPERATOR_COLOUR = Console_colours::BOLDCYAN;
const Console_colours DEFAULT_COLOUR = Console_colours::BOLDWHITE;
const Console_colours COPY_COLOUR = Console_colours::BOLDRED;
// const Console_colours 

enum class Type_functions {
	NOT_FUNCTION,
	CONSTRUCT,
	DESTRUCT,
	OPERATION,
	COPY
};

extern const char* char_type_functions[];

class Int {
private:
	int value;
	std::string name;

	static size_t max_id;
	static size_t max_tmp_number;
	size_t id;

	Signals_default_handler* parent;

public:
	Int();

	~Int();

	Int(const int arg_value, const std::string arg_name = "tmp");

	Int(const Int &other);

	Int& operator=(const int &other);

	Int& operator=(const Int &other);

	Int& operator+=(const Int &other);

	Int& operator-=(const Int &other);

	Int& operator*=(const Int &other);

	Int& operator/=(const Int &other);

	bool operator<(const Int &other) const;

	bool operator>(const Int &other) const;

	bool operator<=(const Int &other) const;

	bool operator>=(const Int &other) const;

	bool operator==(const Int &other) const;

	bool operator!=(const Int &other) const;

	const Int operator+(const Int &other) const;

	const Int operator-(const Int &other) const;

	const Int operator*(const Int &other) const;

	const Int operator/(const Int &other) const;

	int get_value() const;

	size_t get_id() const;

	std::string get_name() const;

	void set_value(const int new_value);
};

#endif
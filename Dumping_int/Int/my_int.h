#ifndef MY_INT_H
#define MY_INT_H

#include <cstdio>
#include <string>
#include "../Tools/console_colours.h"

extern size_t indents;

#define $ 																					\
	indents = Dumper::get_dumper()->get_tracer_functions()->get_count_functions();			\
	for(int i = 0; i < indents; ++i)														\
		printf("\t");

#define $$ printf("\n");

const Console_colours CONSTRUCTOR_COLOUR = Console_colours::GREEN;
const Console_colours ARGUMENTS_COLOUR = Console_colours::YELLOW;
const Console_colours DESTRUCTOR_COLOUR = Console_colours::BOLDMAGENTA;
const Console_colours OPERATOR_COLOUR = Console_colours::CYAN;
// const Console_colours 

class Int {
private:
	int value;
	std::string name;

	static size_t max_id;
	size_t id;

public:
	Int();

	~Int();

	Int(const int arg_value, const std::string arg_name = "aboba");

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
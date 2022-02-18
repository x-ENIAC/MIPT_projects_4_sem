#include "my_int.h"
#include "../Dumper/int_dumping.h"
#include "../Dumper/console.h"
#include "../Tools/console_colours.h"

size_t indents = 0;
bool pair_arithm_flag  = false;

#define BEGIN_FUNC(func_type, colour) Adder_at_trace adder(__PRETTY_FUNCTION__, func_type, colour);

#define SINGLE_PRETTY_ARITHM							\
	printf("%s", ARROWS[1]);

#define PAIR_PRETTY_ARITHM								\
	printf("%s", ARROWS[(int)pair_arithm_flag]);		\
	pair_arithm_flag = !pair_arithm_flag;

#define INFO_ABOUT_VAR_PTR(int_ptr, colour)
#define INFO_ABOUT_VAR_NOT_PTR(int_ptr, colour)
#define INFO_ABOUT_VARS_PTR_AND_NOT_PTR(colour)

const char* char_type_functions[] = {
	"CTOR",
	"DTOR",
	"OPERATION",
	"!!! COPY !!!"
};

// #define INFO_ABOUT_VAR_PTR(int_ptr, colour) 																		\
// 	printf("%s[%p]: id = %ld, %s=%d%s\n",																			\
// 		console_colours_text[(int)colour], int_ptr, int_ptr->get_id(),												\
// 		int_ptr->get_name().c_str(), int_ptr->get_value(), console_colours_text[(int)Console_colours::RESET]);

// #define INFO_ABOUT_VAR_NOT_PTR(int_ptr, colour)																		\
// 	printf("%s[%p]: id = %ld, %s=%d%s\n",																			\
// 		console_colours_text[(int)colour], &int_ptr, int_ptr.get_id(),												\
// 		int_ptr.get_name().c_str(), int_ptr.get_value(), console_colours_text[(int)Console_colours::RESET]);

// #define INFO_ABOUT_VARS_PTR_AND_NOT_PTR(colour)							\
// 	$ PAIR_PRETTY_ARITHM INFO_ABOUT_VAR_PTR(this, colour)				\
// 	$ PAIR_PRETTY_ARITHM INFO_ABOUT_VAR_NOT_PTR(other, colour)

size_t Int::max_id = 0;
size_t Int::max_tmp_number = 1;

Int::Int() {
	BEGIN_FUNC(Type_functions::CONSTRUCT, CONSTRUCTOR_COLOUR)

	value = 0;
	id = max_id++;
	name = "not_defined";
	parent = Dumper::get_dumper();

	if(parent)
		parent->signal(*this, Int_signal::CONSTRUCT);

	// $ SINGLE_PRETTY_ARITHM INFO_ABOUT_VAR_PTR(this, ARGUMENTS_COLOUR)
}

Int::~Int() {
	BEGIN_FUNC(Type_functions::DESTRUCT, DESTRUCTOR_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::DESTRUCT);

	// $ SINGLE_PRETTY_ARITHM INFO_ABOUT_VAR_PTR(this, DESTRUCTOR_COLOUR)
}

Int::Int(const Int &other) {
	BEGIN_FUNC(Type_functions::COPY, COPY_COLOUR)

	value = other.get_value();
	id = max_id++;
	name = other.get_name();
	parent = Dumper::get_dumper();

	// printf("COPY!!!!!!!!!!!!!!\n");
	if(parent)
		parent->signal(*this, Int_signal::COPY);

	// $ SINGLE_PRETTY_ARITHM INFO_ABOUT_VAR_PTR(this, ARGUMENTS_COLOUR)
}

Int::Int(const int arg_value, const std::string arg_name) {
	BEGIN_FUNC(Type_functions::CONSTRUCT, CONSTRUCTOR_COLOUR)

	value = arg_value;
	id = max_id++;
	name = arg_name;
	parent = Dumper::get_dumper();

	if(arg_name == "tmp")
		name += "_" + std::to_string(max_tmp_number++);

	if(parent)
		parent->signal(*this, Int_signal::CONSTRUCT);

	// $ SINGLE_PRETTY_ARITHM INFO_ABOUT_VAR_PTR(this, ARGUMENTS_COLOUR)
}

Int& Int::operator=(const int &other) {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	value = other;

	return *this;
}

Int& Int::operator=(const Int &other) {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	value = other.get_value();
	// id = other.get_id();

	if(parent)
		parent->signal(*this, Int_signal::ASSIGNMENT, other);
		// parent->signal(*this, Int_signal::ASSIGNMENT);

	// Dumper::get_dumper()->signal(*this, other, Int_signal::ASSIGNMENT);

	return *this; 
}

Int& Int::operator+=(const Int &other) {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR(ARGUMENTS_COLOUR)

	value += other.get_value();

	if(parent)
		parent->signal(*this, Int_signal::ADD_AND_ASSIGNMENT, other);
		// parent->signal(*this, Int_signal::ADD_AND_ASSIGNMENT);

	return *this; 
}

Int& Int::operator-=(const Int &other) {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR(ARGUMENTS_COLOUR)

	value -= other.get_value();

	if(parent)
		parent->signal(*this, Int_signal::SUB_AND_ASSIGNMENT, other);
		// parent->signal(*this, Int_signal::SUB_AND_ASSIGNMENT);

	return *this; 
}

Int& Int::operator*=(const Int &other) {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR(ARGUMENTS_COLOUR)

	value *= other.get_value();

	if(parent)
		parent->signal(*this, Int_signal::MUL_AND_ASSIGNMENT, other);
		// parent->signal(*this, Int_signal::MUL_AND_ASSIGNMENT);

	return *this; 
}

Int& Int::operator/=(const Int &other) {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR(ARGUMENTS_COLOUR)

	value /= other.get_value();

	if(parent)
		parent->signal(*this, Int_signal::DIV_AND_ASSIGNMENT, other);
		// parent->signal(*this, Int_signal::DIV_AND_ASSIGNMENT);

	return *this; 
}

bool Int::operator<(const Int &other) const {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR(ARGUMENTS_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::LESS, other);
		// parent->signal(*this, Int_signal::LESS);

	return value < other.get_value();
}

bool Int::operator>(const Int &other) const {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR(ARGUMENTS_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::MORE, other);
		// parent->signal(*this, Int_signal::MORE);

	return value > other.get_value();
}

bool Int::operator<=(const Int &other) const {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR(ARGUMENTS_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::LESS_OR_EQUAL, other);
		// parent->signal(*this, Int_signal::LESS_OR_EQUAL);

	return value <= other.get_value();
}

bool Int::operator>=(const Int &other) const {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR(ARGUMENTS_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::MORE_OR_EQUAL, other);
		// parent->signal(*this, Int_signal::MORE_OR_EQUAL);

	return value >= other.get_value();
}

bool Int::operator==(const Int &other) const {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR(ARGUMENTS_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::EQUAL, other);
		// parent->signal(*this, Int_signal::EQUAL);

	return value == other.get_value();
}

bool Int::operator!=(const Int &other) const {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR(ARGUMENTS_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::NOT_EQUAL, other);
		// parent->signal(*this, Int_signal::NOT_EQUAL);

	return value != other.get_value();
}

const Int Int::operator+(const Int &other) const {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR(ARGUMENTS_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::ADD, other);
		// parent->signal(*this, Int_signal::ADD);

	return { value + other.get_value() }; 
}

const Int Int::operator-(const Int &other) const {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR(ARGUMENTS_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::SUB, other);
		// parent->signal(*this, Int_signal::SUB);

	return { value - other.get_value() }; 
}

const Int Int::operator*(const Int &other) const {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR(ARGUMENTS_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::MUL, other);
		// parent->signal(*this, Int_signal::MUL);

	return { value * other.get_value() }; 
}

const Int Int::operator/(const Int &other) const {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR(ARGUMENTS_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::DIV, other);
		// parent->signal(*this, Int_signal::DIV);

	return { value / other.get_value() }; 
}

int Int::get_value() const {
	return value;
}

void Int::set_value(const int new_value) {
	value = new_value;
}

size_t Int::get_id() const {
	return id;
}

std::string Int::get_name() const {
	return name;
}
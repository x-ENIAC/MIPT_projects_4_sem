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
#define REFRESH_UNARY(object, left, type) object->refresh_last_node_operation(left, type);
#define REFRESH_BINARY(object, left, type, right) object->refresh_last_node_operation(left, type, right);

const char* char_type_functions[] = {
	"",
	"CTOR",
	"DTOR",
	"OPERATION",
	"!!! COPY !!!"
};

size_t Int::max_id = 0;
size_t Int::max_tmp_number = 1;

Int::Int() {
	BEGIN_FUNC(Type_functions::CONSTRUCT, CONSTRUCTOR_COLOUR)

	value = 0;
	id = max_id++;
	name = "not_defined";
	parent = Dumper::get_dumper();

	REFRESH_UNARY(this, *this, Int_signal::CONSTRUCT)
	if(parent)
		parent->signal(*this, Int_signal::CONSTRUCT);
}

Int::~Int() {
	BEGIN_FUNC(Type_functions::DESTRUCT, DESTRUCTOR_COLOUR)

	REFRESH_UNARY(this, *this, Int_signal::DESTRUCT)
	if(parent)
		parent->signal(*this, Int_signal::DESTRUCT);
}

Int::Int(const Int &other) {
	BEGIN_FUNC(Type_functions::COPY, COPY_COLOUR)

	value = other.get_value();
	id = max_id++;
	name = other.get_name();
	parent = Dumper::get_dumper();

	REFRESH_UNARY(this, *this, Int_signal::COPY)
	if(parent)
		parent->signal(*this, Int_signal::COPY);
}

Int::Int(const int arg_value, const std::string arg_name) {
	BEGIN_FUNC(Type_functions::CONSTRUCT, CONSTRUCTOR_COLOUR)

	value = arg_value;
	id = max_id++;
	name = arg_name;
	parent = Dumper::get_dumper();

	if(arg_name == "tmp")
		name += "_" + std::to_string(max_tmp_number++);

	REFRESH_UNARY(this, *this, Int_signal::CONSTRUCT)
	if(parent)
		parent->signal(*this, Int_signal::CONSTRUCT);
}

Int& Int::operator=(const int &other) {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	value = other;

	return *this;
}

Int& Int::operator=(const Int &other) {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	value = other.get_value();

	if(parent)
		parent->signal(*this, Int_signal::ASSIGNMENT, other);

	REFRESH_BINARY(this, *this, Int_signal::ASSIGNMENT, other)
	REFRESH_BINARY((&other), *this, Int_signal::ASSIGNMENT, other)

	return *this; 
}

Int& Int::operator+=(const Int &other) {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	value += other.get_value();

	if(parent)
		parent->signal(*this, Int_signal::ADD_AND_ASSIGNMENT, other);

	REFRESH_BINARY(this, *this, Int_signal::ADD_AND_ASSIGNMENT, other)
	REFRESH_BINARY((&other), *this, Int_signal::ADD_AND_ASSIGNMENT, other)

	return *this; 
}

Int& Int::operator-=(const Int &other) {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	value -= other.get_value();

	if(parent)
		parent->signal(*this, Int_signal::SUB_AND_ASSIGNMENT, other);

	REFRESH_BINARY(this, *this, Int_signal::SUB_AND_ASSIGNMENT, other)
	REFRESH_BINARY((&other), *this, Int_signal::SUB_AND_ASSIGNMENT, other)

	return *this; 
}

Int& Int::operator*=(const Int &other) {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	value *= other.get_value();

	if(parent)
		parent->signal(*this, Int_signal::MUL_AND_ASSIGNMENT, other);

	REFRESH_BINARY(this, *this, Int_signal::MUL_AND_ASSIGNMENT, other)
	REFRESH_BINARY((&other), *this, Int_signal::MUL_AND_ASSIGNMENT, other)

	return *this; 
}

Int& Int::operator/=(const Int &other) {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	value /= other.get_value();

	if(parent)
		parent->signal(*this, Int_signal::DIV_AND_ASSIGNMENT, other);

	REFRESH_BINARY(this, *this, Int_signal::DIV_AND_ASSIGNMENT, other)
	REFRESH_BINARY((&other), *this, Int_signal::DIV_AND_ASSIGNMENT, other)

	return *this; 
}

bool Int::operator<(const Int &other) const {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::LESS, other);

	REFRESH_BINARY(this, *this, Int_signal::LESS, other)
	REFRESH_BINARY((&other), *this, Int_signal::LESS, other)

	return value < other.get_value();
}

bool Int::operator>(const Int &other) const {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::MORE, other);

	REFRESH_BINARY(this, *this, Int_signal::MORE, other)
	REFRESH_BINARY((&other), *this, Int_signal::MORE, other)

	return value > other.get_value();
}

bool Int::operator<=(const Int &other) const {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::LESS_OR_EQUAL, other);

	REFRESH_BINARY(this, *this, Int_signal::LESS_OR_EQUAL, other)
	REFRESH_BINARY((&other), *this, Int_signal::LESS_OR_EQUAL, other)

	return value <= other.get_value();
}

bool Int::operator>=(const Int &other) const {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::MORE_OR_EQUAL, other);

	REFRESH_BINARY(this, *this, Int_signal::MORE_OR_EQUAL, other)
	REFRESH_BINARY((&other), *this, Int_signal::MORE_OR_EQUAL, other)

	return value >= other.get_value();
}

bool Int::operator==(const Int &other) const {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::EQUAL, other);

	REFRESH_BINARY(this, *this, Int_signal::EQUAL, other)
	REFRESH_BINARY((&other), *this, Int_signal::EQUAL, other)

	return value == other.get_value();
}

bool Int::operator!=(const Int &other) const {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::NOT_EQUAL, other);

	REFRESH_BINARY(this, *this, Int_signal::NOT_EQUAL, other)
	REFRESH_BINARY((&other), *this, Int_signal::NOT_EQUAL, other)

	return value != other.get_value();
}

const Int Int::operator+(const Int &other) const {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::ADD, other);

	REFRESH_BINARY(this, *this, Int_signal::ADD, other)
	REFRESH_BINARY((&other), *this, Int_signal::ADD, other)

	return { value + other.get_value() }; 
}

const Int Int::operator-(const Int &other) const {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::SUB, other);

	REFRESH_BINARY(this, *this, Int_signal::SUB, other)
	REFRESH_BINARY((&other), *this, Int_signal::SUB, other)

	return { value - other.get_value() }; 
}

const Int Int::operator*(const Int &other) const {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::MUL, other);

	REFRESH_BINARY(this, *this, Int_signal::MUL, other)
	REFRESH_BINARY((&other), *this, Int_signal::MUL, other)

	return { value * other.get_value() }; 
}

const Int Int::operator/(const Int &other) const {
	BEGIN_FUNC(Type_functions::OPERATION, OPERATOR_COLOUR)

	if(parent)
		parent->signal(*this, Int_signal::DIV, other);

	REFRESH_BINARY(this, *this, Int_signal::DIV, other)
	REFRESH_BINARY((&other), *this, Int_signal::DIV, other)

	return { value / other.get_value() }; 
}

void Int::refresh_last_node_operation(const Int& sender, const Int_signal int_signal) const {
	last_operation.left_id = sender.get_id();

	if(int_signal == Int_signal::CONSTRUCT)
		last_operation.type = Type_functions::CONSTRUCT;
	else
	if(int_signal == Int_signal::DESTRUCT)
		last_operation.type = Type_functions::DESTRUCT;
	else
	if(int_signal == Int_signal::COPY)
		last_operation.type = Type_functions::COPY;
	else
	if(int_signal == Int_signal::NOT_SIGNAL)
		last_operation.type = Type_functions::NOT_FUNCTION;
	else
		last_operation.type = Type_functions::OPERATION;

	last_operation.is_binary = false;
	last_operation.is_used = true;
}

void Int::refresh_last_node_operation(const Int& sender, const Int_signal int_signal, const Int& other) const {
	last_operation.left_id = sender.get_id();

	if(int_signal == Int_signal::CONSTRUCT)
		last_operation.type = Type_functions::CONSTRUCT;
	else
	if(int_signal == Int_signal::DESTRUCT)
		last_operation.type = Type_functions::DESTRUCT;
	else
	if(int_signal == Int_signal::COPY)
		last_operation.type = Type_functions::COPY;
	else
	if(int_signal == Int_signal::NOT_SIGNAL)
		last_operation.type = Type_functions::NOT_FUNCTION;
	else
		last_operation.type = Type_functions::OPERATION;

	last_operation.right_id = other.get_id();

	last_operation.is_binary = true;
	last_operation.is_used = true;
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
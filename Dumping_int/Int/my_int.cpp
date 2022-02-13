#include "my_int.h"
#include "../Dumper/int_dumping.h"
#include "../Dumper/console.h"

size_t indents = 0;
bool pair_arithm_flag  = false;

#define BEGIN_FUNC Adder_at_trace adder(__PRETTY_FUNCTION__);

#define SINGLE_PRETTY_ARITHM							\
	printf("%s", ARROWS[1]);

#define PAIR_PRETTY_ARITHM								\
	printf("%s", ARROWS[(int)pair_arithm_flag]);		\
	pair_arithm_flag = !pair_arithm_flag;

#define INFO_ABOUT_VAR_PTR(int_ptr) 	printf("[%p]: id = %ld, value = %d, name=%s\n", 											\
											int_ptr, int_ptr->get_id(), int_ptr->get_value(), int_ptr->get_name().c_str());

#define INFO_ABOUT_VAR_NOT_PTR(int_ptr) printf("[%p]: id = %ld, value = %d, name=%s\n", 											\
											&int_ptr, int_ptr.get_id(),  int_ptr.get_value(), int_ptr.get_name().c_str());

#define INFO_ABOUT_VARS_PTR_AND_NOT_PTR 				\
	$ PAIR_PRETTY_ARITHM INFO_ABOUT_VAR_PTR(this)		\
	$ PAIR_PRETTY_ARITHM INFO_ABOUT_VAR_NOT_PTR(other)

size_t Int::max_id = 0;

Int::Int() {
	BEGIN_FUNC

	value = 0;
	id = max_id++;
	name = "not_defined";

	$ SINGLE_PRETTY_ARITHM INFO_ABOUT_VAR_PTR(this)
}

Int::Int(const int arg_value, const std::string arg_name) {
	BEGIN_FUNC

	value = arg_value;
	id = max_id++;
	name = arg_name;

	$ SINGLE_PRETTY_ARITHM INFO_ABOUT_VAR_PTR(this)
}

Int& Int::operator=(const int &other) {
	BEGIN_FUNC

	value = other;

	return *this;
}

Int& Int::operator=(const Int &other) {
	BEGIN_FUNC

	value = other.get_value();
	id = other.get_id();

	Dumper::get_dumper()->signal(*this, other, Int_signal::ASSIGNMENT);

	return *this; 
}

Int& Int::operator+=(const Int &other) {
	BEGIN_FUNC

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR

	value += other.get_value();

	return *this; 
}

Int& Int::operator-=(const Int &other) {
	BEGIN_FUNC

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR

	value -= other.get_value();

	return *this; 
}

Int& Int::operator*=(const Int &other) {
	BEGIN_FUNC

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR

	value *= other.get_value();

	return *this; 
}

Int& Int::operator/=(const Int &other) {
	BEGIN_FUNC

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR

	value /= other.get_value();

	return *this; 
}

bool Int::operator<(const Int &other) const {
	BEGIN_FUNC

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR

	return value < other.get_value();
}

bool Int::operator>(const Int &other) const {
	BEGIN_FUNC

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR

	return value > other.get_value();
}

bool Int::operator<=(const Int &other) const {
	BEGIN_FUNC

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR

	return value <= other.get_value();
}

bool Int::operator>=(const Int &other) const {
	BEGIN_FUNC

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR

	return value >= other.get_value();
}

bool Int::operator==(const Int &other) const {
	BEGIN_FUNC

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR

	return value == other.get_value();
}

bool Int::operator!=(const Int &other) const {
	BEGIN_FUNC

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR

	return value != other.get_value();
}

const Int Int::operator+(const Int &other) const {
	BEGIN_FUNC

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR

	return { value + other.get_value() }; 
}

const Int Int::operator-(const Int &other) const {
	BEGIN_FUNC

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR

	return { value - other.get_value() }; 
}

const Int Int::operator*(const Int &other) const {
	BEGIN_FUNC

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR

	return { value * other.get_value() }; 
}

const Int Int::operator/(const Int &other) const {
	BEGIN_FUNC

	INFO_ABOUT_VARS_PTR_AND_NOT_PTR

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
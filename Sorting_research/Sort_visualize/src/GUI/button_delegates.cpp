#include "button_delegates.h"


Begin_sort_delegate::Begin_sort_delegate(Number_container* arg_number_container, bool* arg_is_running_sorting) {
	number_container = arg_number_container;
	is_running_sorting = arg_is_running_sorting;
}
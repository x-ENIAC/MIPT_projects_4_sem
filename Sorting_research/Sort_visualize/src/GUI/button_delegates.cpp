#include "button_delegates.h"


Begin_sort_delegate::Begin_sort_delegate(Number_container* arg_number_container, bool* arg_is_running_sorting) {
	number_container = arg_number_container;
	is_running_sorting = arg_is_running_sorting;
}

Stop_sort_delegate::Stop_sort_delegate(Number_container* arg_number_container, bool* arg_is_running_sorting) {
	number_container = arg_number_container;
	is_running_sorting = arg_is_running_sorting;
}

Choose_sort_delegate::Choose_sort_delegate(int* arg_number_of_sort, SORTING arg_sorting) {
	number_of_sort = arg_number_of_sort;
	sorting = arg_sorting;
}

Refresh_array_delegate::Refresh_array_delegate(Number_container* arg_number_container) {
	number_container = arg_number_container;
}
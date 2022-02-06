#include "button_delegates.h"


Show_points_delegate::Show_points_delegate(bool* arg_is_visible, const int arg_index) {
	is_visible = arg_is_visible;
	index = arg_index;
}
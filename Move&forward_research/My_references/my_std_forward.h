#ifndef MY_STD_FORWARD_H
#define MY_STD_FORWARD_H

#include "my_std_move.h"

template<class T>
T&& my_forward(typename type_without_reference<T>::type& a) {
    return static_cast<T&&>(a);
}

template<class T>
T&& my_forward(typename type_without_reference<T>::type&& a) {
    return static_cast<T&&>(a);
}

#endif
#ifndef MY_STD_FORWARD_H
#define MY_STD_MOVE_H

template<class T>
T&& my_forward(T& a) {
    return static_cast<T&&>(a);
}

template<class T>
T&& my_forward(T&& a) {
    return static_cast<T&&>(a);
}

#endif
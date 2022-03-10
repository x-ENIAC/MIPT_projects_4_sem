#ifndef MY_STD_MOVE_H
#define MY_STD_MOVE_H

template<class T>
struct type_without_reference {
    typedef T type;
};

template<class T>
struct type_without_reference<T&> {
    typedef T type;
};

template<class T>
struct type_without_reference<T&&> {
    typedef T type;
};

template<class T>
typename type_without_reference<T>::type&& my_move(T&& arg) {
    return (static_cast<typename type_without_reference<T>::type&&>(arg));
}

#endif
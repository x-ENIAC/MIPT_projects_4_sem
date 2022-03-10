#ifndef STACK_H
#define STACK_H

#include <cstdio>
#include <cstddef>
#include <string>

typedef std::string Elem_t;
const size_t DIMENSION = 128;

class Stack {

public:
	Elem_t* data;
    size_t size_stack;
    size_t capacity;

    Stack() {
    	data = new Elem_t[DIMENSION];
    	capacity = DIMENSION;
    	size_stack = 0;
    }

    ~Stack() {
    	delete[] data;
    }

    void push(Elem_t new_element) {
    	if(size_stack + 1 < capacity) {
    		data[size_stack++] = new_element;
    	} else {
    		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!1\n");
    	}
    }

    Elem_t& back() {
    	return data[size_stack];
    }

    void pop() {
    	--size_stack;
    }

    size_t get_size_stack() const {
        return size_stack;
    }
};

#endif
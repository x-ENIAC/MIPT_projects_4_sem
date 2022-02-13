#include "number.h"
#include <cstdio>
#include <cmath>

#ifndef NUMBER_CONTAINER_H
#define NUMBER_CONTAINER_H

class Number_container {
  public:
  	Number* numbers;
  	int count;
  	int capacity;
  	int max_value;

  	Number_container(const int arg_capacity) : capacity(arg_capacity) {
  		numbers = new Number[capacity];
  		count = max_value = 0;

  		fill_container();
  	}

  	~Number_container() {
  		delete[] numbers;
  		count = capacity = 0;
  	}

  	void fill_container() {
  		for(int i = 0; i < capacity; ++i) {
  			numbers[i].value = rand() % 99 + 1;
  			numbers[i].pos = i;

  			if(numbers[i].value > max_value)
  				max_value = numbers[i].value;
  		}

  		count = capacity;
  	}

  	void begin_sort() {
  		printf("[Number_container] begin sort!\n");
  	}

  	int get_max_value() {
  		return max_value;
  	}

  	int get_count() {
  		return count;
  	}

  	Number* get_numbers() {
  		return numbers;
  	}

};

#endif
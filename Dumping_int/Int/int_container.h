#ifndef INT_CONTAINER
#define INT_CONTAINER

#include <cmath>
#include "my_int.h"
#include "../Dumper/int_signals_default_handler.h"

class Int_container : public Signals_default_handler {
  private:
  	Int* numbers;
  	size_t count;
  	size_t capacity;

  	Signals_default_handler* recipient;

  public:
  	Int_container(size_t arg_capacity) {
  		numbers = new Int[arg_capacity];
  		count = 0;
  		capacity = arg_capacity;

  		recipient = nullptr;
  	}

  	~Int_container() {
  		delete[] numbers;
  	}

  	void fill_array() {
  		for(int i = 0; i < capacity; ++i)
  			numbers[i].set_value(rand() % 100 + 1);

  		count = capacity;
  	}

  	void signal(const Int& sender, const Int_signal int_signal) override {
  		// if(recipient)
  		// 	recipient->signal(sender, recipient_, int_signal);
  		// else
  		// 	printf("[Int_container] Recipient doesn't found!\n");
  	}

  	void print_array() {
  		for(int i = 0; i < count; ++i)
  			printf("%d ", numbers[i].get_value());
  		printf("\n");
  	}

  	Int* get_array() {
  		return numbers;
  	}

  	int get_count() {
  		return count;
  	}
};

#endif
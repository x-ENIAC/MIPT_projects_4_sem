
#ifndef NUMBER_H
#define NUMBER_H

extern int comparisons;
extern int assignments;

class Number {
  public:
	int value;
	int pos;

	// int* assignments;
	// int* comparisons;
	Number() {
		value = 0;
		pos = 0;
	}

	Number(const int arg_value, const int arg_pos) {
		value = arg_value;
		pos = arg_pos;
		++assignments;
	}

	Number& operator=(const Number& right) {
		if(this != &right) {
			value = right.value;
			pos = right.pos;
			++assignments;
		}

		return *this;
	}

	bool operator<(const Number& right) const {
		++comparisons;
		return (value < right.value);
	}

};

#endif
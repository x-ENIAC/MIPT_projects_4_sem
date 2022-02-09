
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

	Number(const int arg_value) {
		value = arg_value;
		pos = 0;
		++assignments;
	}


	Number(const int arg_value, const int arg_pos) {
		value = arg_value;
		pos = arg_pos;
		++assignments;
	}

	void set_pos(const int arg_pos) {
		pos = arg_pos;
	}

	Number& operator=(const Number& right) {
		if(this != &right) {
			value = right.value;
			pos = right.pos;
			++assignments;
			// printf("!!!, assignments %d\n", assignments);
		}

		return *this;
	}

	bool operator<(const Number& right) const {
		++comparisons;
		// printf("???, comparisons %d\n", comparisons);
		return (value < right.value);
	}

	bool operator<(const int& right) const {
		++comparisons;
		// printf("???, comparisons %d\n", comparisons);
		return (value < right);
	}

	bool operator>(const Number& right) const {
		++comparisons;
		// printf("???, comparisons %d\n", comparisons);
		return (value > right.value);
	}

	bool operator>(const int& right) const {
		++comparisons;
		// printf("???, comparisons %d\n", comparisons);
		return (value > right);
	}


};

#endif
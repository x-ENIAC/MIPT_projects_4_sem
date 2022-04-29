#ifndef ALLOCATOR_H
#define ALLOCATOR_H

template < typename T >
class Allocator {
  public:
  	Allocator() {}
  	~Allocator() {}
	
	T* allocate(size_t size) {
		return (T*)(new char[size * sizeof(T)]);
	}

	void deallocate(T* memory) {
		delete[] (char*)memory;
	}

	void construct(T* pointer, T value) {
		new(pointer) T(value);
	}

	void destroy(T* pointer) {
		pointer->~T();
	}
};

#endif
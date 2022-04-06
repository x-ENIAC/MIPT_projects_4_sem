CUR_PROG = vector
ARGS = 

CPP = g++ -std=c++11
LD = g++

WARNINGS = 
STANDARD =

CFLAGS = $(WARNINGS) $(STANDARD)
LDFLAGS =

.PHONY : all run debug clean

build:
	$(CPP) $(CFLAGS) $(SIMPLE_OPTIMIZATION) $(OPTIMIZATION_OFF) -c main.cpp -o main.o
	$(LD) main.o -o $(CUR_PROG) $(LDFLAGS)

run: build
	./$(CUR_PROG) $(ARGS)

callgrind_debug: all
	valgrind  -s --dump-instr=yes --tool=callgrind  ./$(CUR_PROG) $(ARGS)
	
debug: all
	valgrind --track-origins=yes ./$(CUR_PROG) $(ARGS)	

clean:
	rm *.o

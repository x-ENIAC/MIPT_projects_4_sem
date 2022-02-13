CUR_PROG = numbers
ARGS = 

CPP = g++
LD = g++

WARNINGS = 
STANDARD = 
OPTIMIZATION = -O0 -Wno-reorder -fno-elide-constructors

CFLAGS = $(WARNINGS) $(STANDARD) $(OPTIMIZATION)
LDFLAGS =

.PHONY : all run debug clean

all: my_int.o int_dumping.o int_signals.o calling_trace.o console_colours.o console.o testing.o
	$(CPP) $(CFLAGS) -c main.cpp -o main.o
	$(LD) my_int.o int_dumping.o int_signals.o calling_trace.o console_colours.o console.o testing.o main.o -o $(CUR_PROG) $(LDFLAGS)

testing.o: Tests/testing.cpp Tests/testing.h
	$(CPP) $(CFLAGS) -c Tests/testing.cpp -o testing.o
	
int_signals.o: Int/int_signals.cpp Int/int_signals.h
	$(CPP) $(CFLAGS) -c Int/int_signals.cpp -o int_signals.o

my_int.o: Int/my_int.cpp Int/my_int.h
	$(CPP) $(CFLAGS) -c Int/my_int.cpp -o my_int.o

int_dumping.o: Dumper/int_dumping.cpp Dumper/int_dumping.h
	$(CPP) $(CFLAGS) -c Dumper/int_dumping.cpp -o int_dumping.o

calling_trace.o: Dumper/calling_trace.cpp Dumper/calling_trace.h
	$(CPP) $(CFLAGS) -c Dumper/calling_trace.cpp -o calling_trace.o

console.o: Dumper/console.cpp Dumper/console.h
	$(CPP) $(CFLAGS) -c Dumper/console.cpp -o console.o

console_colours.o: Tools/console_colours.cpp Tools/console_colours.h
	$(CPP) $(CFLAGS) -c Tools/console_colours.cpp -o console_colours.o

run: all
	./$(CUR_PROG) $(ARGS)

callgrind_debug: all
	valgrind  -s --dump-instr=yes --tool=callgrind  ./$(CUR_PROG) $(ARGS)
	
debug: all
	valgrind --track-origins=yes ./$(CUR_PROG) $(ARGS)	

clean:
	rm *.o

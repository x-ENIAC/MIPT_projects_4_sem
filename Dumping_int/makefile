CUR_PROG = numbers
ARGS = 

CPP = g++ -std=c++11
LD = g++

WARNINGS = 
STANDARD =
SIMPLE_OPTIMIZATION = -O1
OPTIMIZATION_ON = -fno-elide-constructors
OPTIMIZATION_OFF = -felide-constructors

CFLAGS = $(WARNINGS) $(STANDARD)
LDFLAGS =

.PHONY : all run debug clean

all_optimize_on: my_int.o int_dumping.o int_signals.o calling_trace.o console_colours.o html_listing.o graph_dumper.o console.o testing.o
	$(CPP) $(CFLAGS) $(SIMPLE_OPTIMIZATION) $(OPTIMIZATION_ON) -c main.cpp -o main.o
	$(LD) my_int.o int_dumping.o int_signals.o calling_trace.o console_colours.o console.o html_listing.o graph_dumper.o testing.o main.o -o $(CUR_PROG) $(LDFLAGS)
	
all_optimize_off: my_int.o int_dumping.o int_signals.o calling_trace.o console_colours.o html_listing.o graph_dumper.o console.o testing.o
	$(CPP) $(CFLAGS) $(SIMPLE_OPTIMIZATION) $(OPTIMIZATION_OFF) -c main.cpp -o main.o
	$(LD) my_int.o int_dumping.o int_signals.o calling_trace.o console_colours.o console.o html_listing.o graph_dumper.o testing.o main.o -o $(CUR_PROG) $(LDFLAGS)

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

html_listing.o: Dumper/html_listing.cpp Dumper/html_listing.h
	$(CPP) $(CFLAGS) -c Dumper/html_listing.cpp -o html_listing.o

graph_dumper.o: Dumper/graph_dumper.cpp Dumper/graph_dumper.h
	$(CPP) $(CFLAGS) -c Dumper/graph_dumper.cpp -o graph_dumper.o

run_optimize_on: all_optimize_on
	./$(CUR_PROG) $(ARGS)
	
run_optimize_off: all_optimize_off
	./$(CUR_PROG) $(ARGS)

callgrind_debug: all
	valgrind  -s --dump-instr=yes --tool=callgrind  ./$(CUR_PROG) $(ARGS)
	
debug: all
	valgrind --track-origins=yes ./$(CUR_PROG) $(ARGS)	

clean:
	rm *.o

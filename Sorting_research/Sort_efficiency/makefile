CUR_PROG = graphical_editor
ARGS = 

CPP = g++
LD = g++

WARNINGS = 
STANDARD = 
OPTIMIZATION = -O1 -Wno-reorder

CFLAGS = $(WARNINGS) $(STANDARD) $(OPTIMIZATION)
LDFLAGS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -L.

.PHONY : all run debug clean

all: sorts.o app.o colour.o point.o canvas.o view_manager.o
	$(CPP) $(CFLAGS) -c ./src/main.cpp -o main.o
	$(LD) -Llib/ sorts.o app.o colour.o point.o canvas.o view_manager.o main.o -ldl -o $(CUR_PROG) $(LDFLAGS)
	
app.o: ./src/app.cpp ./src/app.h
	$(CPP) $(CFLAGS) -c ./src/app.cpp -o app.o

colour.o: ./src/Utils/colour.cpp ./src/Utils/colour.h
	$(CPP) $(CFLAGS) -c ./src/Utils/colour.cpp -o colour.o
	
point.o: ./src/Utils/point.cpp ./src/Utils/point.h
	$(CPP) $(CFLAGS) -c ./src/Utils/point.cpp -o point.o
	
canvas.o: ./src/Editor/canvas.cpp ./src/Editor/canvas.h
	$(CPP) $(CFLAGS) -c ./src/Editor/canvas.cpp -o canvas.o
	
view_manager.o: ./src/Editor/view_manager.cpp ./src/Editor/view_manager.h
	$(CPP) $(CFLAGS) -c ./src/Editor/view_manager.cpp -o view_manager.o	

sorts.o: ./src/sorts.cpp ./src/sorts.h
	$(CPP) $(CFLAGS) -c ./src/sorts.cpp -o sorts.o	

run: all
	./$(CUR_PROG) $(ARGS)

callgrind_debug: all
	valgrind  -s --dump-instr=yes --tool=callgrind  ./$(CUR_PROG) $(ARGS)
	
debug: all
	valgrind --track-origins=yes ./$(CUR_PROG) $(ARGS)	

clean:
	rm *.o

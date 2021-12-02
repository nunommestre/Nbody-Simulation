CC = g++
C_FLAGS = -std=c++11 -c -g -Og -Wall -Werror -pedantic
OBJECTS = Nbody.o main.o
DEPS = Nbody.h
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
EXE = Nbody

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXE) $(LIBS)
%.o: %.cpp $(DEPS)
	$(CC) $(C_FLAGS) -o $@ $<
clean:
	rm $(OBJECTS) $(EXE)

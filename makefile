CXX=g++
CXXFLAGS=-std=c++14 -g -Wall
LSFMLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

SD=Tree.hpp # You mentioned this, but .hpp files are not compiled, you might mean something else?
ST=

# Convert your .cpp file names to .o file names
OD=$(SD:.cpp=.o)
OT=$(ST:.cpp=.o)

.PHONY: all run demo test valgrind_test valgrind_demo clean

all: demo test

run_test: test
	./$^

tree: demo
	./$^

demo: demo.o $(OD)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LSFMLFLAGS)

test: TestCounter.o test.o $(OT)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LSFMLFLAGS)

valgrind_test: test
	valgrind --leak-check=full ./test

valgrind_demo: demo
	valgrind --leak-check=full ./demo

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o demo test

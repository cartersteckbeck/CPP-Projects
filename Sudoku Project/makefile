CXXFLAGS = -std=c++11 -Wall -Werror -Wextra

all: sudoku

sudoku: sudokuboard.o sudoku.o stack.o
	g++ -o sudoku sudokuboard.o sudoku.o stack.o

sudoku.o: sudoku.cc sudokuboard.h stack.h
	g++ $(CXXFLAGS) -c sudoku.cc

stack.o: stack.h stack.cc
	g++ $(CXXFLAGS) -c stack.cc

sudokuboard.o: sudokuboard.cc sudokuboard.h
	g++ $(CXXFLAGS) -c sudokuboard.cc

clean:
	rm -f *.o *~ sudoku

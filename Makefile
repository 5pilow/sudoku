all : sudoku
	
sudoku : main.o
	g++ main.cpp -lrt -o sudoku
	
clean:
	rm -f *.o


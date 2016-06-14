sudoku: main.o sudoku.o
	g++ -g main.o sudoku.o -o sudoku

main.o: main.cpp sudoku.h
	g++ -Wall -c -g main.cpp

sudoku.o: sudoku.cpp sudoku.h
	g++ -Wall -c -g sudoku.cpp

clean:
	rm -f *.o sudoku


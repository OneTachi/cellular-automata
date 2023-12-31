all: automata

automata: cell.hh dungeon.hh main.cpp
	g++ -std=c++11 main.cpp -o automata

clean: 
	/bin/rm -rf *.o *~ automata

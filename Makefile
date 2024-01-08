all: automata

automata: dungeon.hh main.cpp
	g++ -std=c++11 main.cpp -o automata

clean: 
	/bin/rm -rf *.o *~ automata

test: dungeon.hh test.cpp
	 g++ -std=c++11 test.cpp -o automata
	./automata

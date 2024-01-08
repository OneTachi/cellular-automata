#include "dungeon.hh"
#include <iostream>
#include <cassert>
#include <string.h>

using namespace std;

void test_compare();

int main()
{
	/*
	Dungeon dungeon(10, 10, 1);
	dungeon.noise_grid(10, 50);
	dungeon.print();
	dungeon.make_maze();
	dungeon.print();
	*/
	test_compare();
	return 0;	
}

void test_compare()
{
	Dungeon dungeon(10, 10, 1);
	Dungeon result(10, 10, 1);
	assert( dungeon.str_maze().compare(result.str_maze()) ? 0 : 1 );
}

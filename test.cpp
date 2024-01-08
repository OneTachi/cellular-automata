#include "dungeon.hh"
#include <iostream>

using namespace std; 
int main()
{
	Dungeon dungeon(10, 10, 1);
	dungeon.noise_grid(10, 50);
	dungeon.print();
	dungeon.make_maze();
	dungeon.print();
	return 0;	
}

#include "dungeon.hh"
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		Dungeon dun(100, 100, 5, 20, 50);
	}
	return 1;
}

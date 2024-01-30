#include "dungeon.hh"
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		Dungeon dun(50, 50, 200, 25, 50);
	}
	return 1;
}

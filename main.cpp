#include "dungeon.hh"
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		Dungeon dun(50, 50, 20, 50, 50);
		return 1;
	}
	if (argc < 6 || argc > 7)
	{
		cout << "Enter 6 arguments, 7 for debug." << endl;
		return 0;
	}

	int rows = atoi(argv[1]);
	int cols = atoi(argv[2]);
	int generations = atoi(argv[3]);
	int noise_size = atoi(argv[4]);
	int ratio = atoi(argv[5]);
	bool pretty_print = true;
	
	if (argc == 7) { pretty_print = atoi(argv[6]); }
	Dungeon dun(rows, cols, generations, noise_size, ratio, pretty_print);
	
	return 1;
}

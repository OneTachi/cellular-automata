#include "dungeon.hh"
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		Dungeon dun(100, 100, 500, 1, 0);
		return 1;
	}
	if (argc < 6 || argc > 7)
	{
		cout << "Enter 6 arguments, 7 for debug." << endl;
		return 0;
	}
	


	return 1;
}

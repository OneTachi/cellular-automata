/**
* Siddharth Lokula 
* created: December 25, 2023
*/

#ifndef DUNGEON_HH
#define DUNGEON_HH

#include <vector>

using namespace std;

class Dungeon
{
public:	
	Dungeon(int, int);
	void setTile(pair<int, int>, int);
	int getTile(pair<int, int>);
	void print();
	
private:
	vector<int><int> dungeon; // Row then column for access
	int num_rows;
	int num_cols;
}

Dungeon::Dungeon(int rows, int cols)
{
	num_rows = rows;
	num_cols = cols;
	
	// If we get invalid input, we will assume least possible number of rows/columns
	if (rows < 1) { num_rows = 1; }
	if (cols < 1) { num_cols = 1; }	
	
	// Set dungeon size
	dungeon = vector<vector<int>>(num_rows, vector<int>(num_cols));
}

void Dungeon::setTile(pair<int, int> coords, int value) { dungeon[coords.first][coords.second] = value; }
int Dungeon::getTile(pair<int, int> coords) { return dungeon[coords.first][coords.second]; }




#endif

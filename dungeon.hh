/**
* Siddharth Lokula 
* created: December 25, 2023
*/

#ifndef DUNGEON_HH
#define DUNGEON_HH

#include <vector>

using namespace std;
// :) 
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

	// Add cells into each index
	

	// Put references in for each cell/neighborhood
}

void Dungeon::setTile(pair<int, int> coords, int value) { dungeon[coords.first][coords.second] = value; }
int Dungeon::getTile(pair<int, int> coords) { return dungeon[coords.first][coords.second]; }

//TODO 
// print()
// getNeighborhood (includes diagonals, 8 surroundings) PUT IN CELL CLASS for now -- gets value of neighborhood
// Every index should have a cell (class) in them
// Cell class - they should contain some value, 0 for floor, 1 for rock, 2 for wall (might need to change in future for rules to work), function to get the value of neighborhood (getneighborhood?)
// make basic functions for rules, only looks at individual cell! No calling iterively etc.
// Makefile

#endif

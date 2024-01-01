/**
* Siddharth Lokula 
* created: December 25, 2023
*/

#ifndef DUNGEON_HH
#define DUNGEON_HH

#include <vector>

//The value each cell starts with
int startingCellValue = 0;

using namespace std; 
class Dungeon
{
public:	
	Dungeon(int, int);
	void setTile(pair<int, int>, int);
	int getTile(pair<int, int>);
	int getNeighborhood(int, int);
	void print();
	
private:
	vector<vector<int>> dungeon; // Row then column for access
	int num_rows;
	int num_cols;
};

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
	for(int i=0, i<num_rows, i++)
	{
		for(int j=0, j<num_cols, j++)
		{
			Cell startCell = new Cell(startingCellValue);
			dungeon[i][j].push_back(startCell);
		}
	}

	// Put references in for each cell/neighborhood
}

void Dungeon::setTile(pair<int, int> coords, int value) { dungeon[coords.first][coords.second] = value; }
int Dungeon::getTile(pair<int, int> coords) { return dungeon[coords.first][coords.second]; }

int getNeighborhood(int rowIndex, int colIndex)
{
	int neighborhoodValue = 0;
	Cell temp = getTile(rowIndex, colIndex);
	bool topValid = false;
	bool bottomValid = false;
	
	//Cases where index of cell is at edge of dungeon
	if(rowIndex > 0)
	{
		//Gets node directly above the starting node
		temp = getTile(rowIndex-1, colIndex);
		neighborhoodValue += temp->getCellValue();
		//States the top is possibly valid
		topValid = true;
	}
	if(rowIndex < num_rows)
	{
		//Gets node directly above the starting node
		temp = getTile(rowIndex+1, colIndex);
		neighborhoodValue += temp->getCellValue();
		//Says bottom is possibly valid
		bottomValid = true;
	}
	if(colIndex > 0)
	{
		//Gets node directly left of the starting node
		temp = getTile(rowIndex, colIndex-1);
		neighborhoodValue += temp->getCellValue();
		//Checks for the top left node 
		if(topValid)
		{
			temp = getTile(rowIndex-1, colIndex-1);
			neighborhoodValue += temp->getCellValue();
		}
		//Checks for the bottom left node 
		if(bottomValid)
		{
			temp = getTile(rowIndex+1, colIndex-1);
			neighborhoodValue += temp->getCellValue();
		}
	}
	if(rowIndex < num_cols)
	{
		//Gets node directly right of the starting node
		temp = getTile(rowIndex, colIndex+1);
		neighborhoodValue += temp->getCellValue();
		//Checks for the top right node 
		if(topValid)
		{
			temp = getTile(rowIndex-1, colIndex+1);
			neighborhoodValue += temp->getCellValue();
		}
		//Checks for the bottom right node 
		if(bottomValid)
		{
			temp = getTile(rowIndex+1, colIndex+1);
			neighborhoodValue += temp->getCellValue();
		}
	}
	
	return neighborhoodValue;
}

//TODO 
// print() -- Sidd
// getNeighborhood (includes diagonals, 8 surroundings) PUT IN Dungeon class -- Rory
// Every index should have a cell (class) in them
// Cell class - they should contain some value, 0 for floor, 1 for rock, 2 for wall (might need to change in future for rules to work), function to get the value of neighborhood (getneighborhood?) -- Rory
// make basic functions for rules, only looks at individual cell! No calling iterively etc. -- Sidd
// Makefile -- Sidd

#endif

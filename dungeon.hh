/**
* Siddharth Lokula 
* created: December 25, 2023
*/

#ifndef DUNGEON_HH
#define DUNGEON_HH

#include <vector>

//The value each cell starts with
const int startingCellValue = 0;

const int FLOOR = 0;
const int ROCK = 1;
const int WALL = 2;

using namespace std; 
class Dungeon
{
public:	
	Dungeon(int, int);
	void set_tile(pair<int, int>, int);
	int get_tile(pair<int, int>);
	int get_neighborhood(int, int, int);
	void print();
	void apply_rule(pair<int, int>);
	
private:
	vector<vector<int>> dungeon; // Row then column for access
	int num_rows;
	int num_cols;
	int time = 0;
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
	/*
	for(int i=0; i<num_rows; i++)
	{
		for(int j=0; j<num_cols; j++)
		{
			dungeon[i][j] = startingCellValue;
		}
	}
	*/

	// Put references in for each cell/neighborhood
}

void Dungeon::set_tile(pair<int, int> coords, int value) { dungeon[coords.first][coords.second] = value; }
int Dungeon::get_tile(pair<int, int> coords) { return dungeon[coords.first][coords.second]; }
//If val = 0 return isNextToFloor, else return neighborhoodTotalValue
int Dungeon::get_neighborhood(int val, int rowIndex, int colIndex) 
{
	int neighborhoodValue = 0;
	int temp;
	bool topValid = false;
	bool bottomValid = false;
	int isNextToFloor = 0;
	//Cases where index of cell is at edge of dungeon
	if(rowIndex > 0)
	{
		//Gets node directly above the starting node
		temp = get_tile(pair<int, int>(rowIndex-1, colIndex));
		neighborhoodValue += temp;
		//States the top is possibly valid
		topValid = true;
		if(temp == 0)
		{
			isNextToFloor = 1;
		}
	}
	if(rowIndex < num_rows)
	{
		//Gets node directly above the starting node
		temp = get_tile(pair<int, int>(rowIndex+1, colIndex));
		neighborhoodValue += temp;
		//Says bottom is possibly valid
		bottomValid = true;
		if(temp == 0)
		{
			isNextToFloor = 1;
		}
	}
	if(colIndex > 0)
	{
		//Gets node directly left of the starting node
		temp = get_tile(pair<int, int>(rowIndex, colIndex-1));
		neighborhoodValue += temp;
		if(temp == 0)
		{
			isNextToFloor = 1;
		}
		//Checks for the top left node 
		if(topValid)
		{
			temp = get_tile(pair<int, int>(rowIndex-1, colIndex-1));
			neighborhoodValue += temp;
			if(temp == 0)
			{
				isNextToFloor = 1;
			}
		}
		//Checks for the bottom left node 
		if(bottomValid)
		{
			temp = get_tile(pair<int, int>(rowIndex+1, colIndex-1));
			neighborhoodValue += temp;
			if(temp == 0)
			{
				isNextToFloor = 1;
			}
		}
	}
	if(rowIndex < num_cols)
	{
		//Gets node directly right of the starting node
		temp = get_tile(pair<int, int>(rowIndex, colIndex+1));
		neighborhoodValue += temp;
		if(temp == 0)
		{
			isNextToFloor = 1;
		}
		//Checks for the top right node 
		if(topValid)
		{
			temp = get_tile(pair<int, int>(rowIndex-1, colIndex+1));
			neighborhoodValue += temp;
			if(temp == 0)
			{
				isNextToFloor = 1;
			}
		}
		//Checks for the bottom right node 
		if(bottomValid)
		{
			temp = get_tile(pair<int, int>(rowIndex+1, colIndex+1));
			neighborhoodValue += temp;
			if(temp == 0)
			{
				isNextToFloor = 1;
			}	
		}
	}
	//If val = 0 return isNextToFloor, else return neighborhoodTotalValue
	if(val == 0)
	{
		return neighborhoodValue;
	}
	return isNextToFloor;
}

void Dungeon::apply_rule(pair<int, int> coords)
{
	int neighborhood = get_neighborhood(coords.first, coords.second);
	
	// If the neighborhood is greater than generation, set this tile to rock. Otherwise, set this tile to floor
	if (neighborhood >= time) { set_tile(coords, ROCK); }
	else { set_tile(coords, FLOOR); }	

	// If rock cell and floor nearby, turn this into wall? Or do we turn floor into wall?
	// TODO
}



//TODO 
// print() -- Sidd
// make basic functions for rules, only looks at individual cell! No calling iterively etc. -- Sidd
// Repurpose get_neighborhood so that based on a integer given, gives either neighborhood or if there are any floors -- Rory 
// Iterative thing -- FIGURE OUT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Both
#endif

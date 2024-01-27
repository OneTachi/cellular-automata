/**
* Siddharth Lokula 
* created: December 25, 2023
*/

#ifndef DUNGEON_HH
#define DUNGEON_HH

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string.h>
//The value each cell starts with
const int startingCellValue = 0;

// We will keep this simple, a floor and a wall. 1 & 0 will allow us to easily calculate the moore's neighborhood and determine # of floors/walls
const int FLOOR = 1; 
const int WALL = 0;

using namespace std; 
class Dungeon
{
public:	
	Dungeon(int, int, int);
	Dungeon(string); // Create fixed dungeon (Debug)
	
	void set_tile(pair<int, int>, int);
	void set_temp_tile(pair<int, int>, int); // Set tile for temporary grid
	void set_generations(int);
	int get_tile(pair<int, int>);
	int get_temp_tile(pair<int, int>);
	int get_generations();

	int get_neighborhood(int, int, int); // Get Moore Neighborhood
	bool is_in_bounds(int, int);
	void print();
	void apply_rule(pair<int, int>);
	void calculate_generation();
	void noise_grid(int, int);
	void make_maze();

	string str_maze(); // Get maze as string

private:
	vector<vector<int>> dungeon; // Row then column for access
	vector<vector<int>> temp_dungeon; // Our temporary grid for each generation
	int num_rows;
	int num_cols;
	int time = 0; // The current generation we are on
	int generations = 0; // Number of generations we would like to go up to
};

/*
 * Constructor is used for debugging. 
 * Creates a fixed maze based on string --> For example: "11 10" creates 
 * 1 1
 * 1 0
 * Note: Do not add a space at the end of the string. Spaces indicate new row to insert into. 
 */
Dungeon::Dungeon(string maze)
{
	dungeon = vector<vector<int>>(1, vector<int>()); // Since I don't know the size of the dungeon, I'll dynamically allocate it
	int col = 0;
	int row = 0;
	// Iterate through string
	for (int character = 0; character < maze.length(); character++, col++)
	{
		// If its a space character, start inserting onto the next row. Otherwise, put value into dungeon.
		if (maze[character] != ' ')
		{
			dungeon[row].push_back(maze[character] - '0'); // Assumes you use the right wall/floor integers.	
		}
		else
		{
			dungeon.push_back(vector<int>());
			row++;
			col = -1;
		}
	}
	num_rows = row + 1;
	num_cols = col;
	temp_dungeon = vector<vector<int>>(num_rows, vector<int>(num_cols));
}

Dungeon::Dungeon(int rows, int cols, int generationGoal)
{
	num_rows = rows;
	num_cols = cols;
	generations = generationGoal;
	
	// If we get invalid input, we will assume least possible number of rows/columns
	if (rows < 1) { num_rows = 1; }
	if (cols < 1) { num_cols = 1; }	
	
	// Set dungeon size
	dungeon = vector<vector<int>>(num_rows, vector<int>(num_cols));
	temp_dungeon = vector<vector<int>>(num_rows, vector<int>(num_cols));
	//Sets all tiles in the dungeon to WALLs
	for(int i=0; i<num_rows; i++)
	{
		for(int j=0; j<num_cols; j++)
		{
			set_tile(pair<int,int>(i,j), WALL);
		}
	}
	
	//make_maze()
}

/*
 * Utility function that outputs the maze as a string.
 * Numbers grouped together indicate a row. Spaces indicate the next row in the dungeon. 
 * If we returned "10 01" this is equivalent to the dungeon:
 * 1 0
 * 0 1 
 */
string Dungeon::str_maze()
{
	string result = "";
	for (int row = 0; row < num_rows; row++)
	{
		for (int col = 0; col < num_cols; col++)
		{
			char tile = '0' + get_tile(pair<int, int>(row, col));
			result += tile;
		}
		result += " ";
	}
	return result;
}


// Getters and Setters
void Dungeon::set_tile(pair<int, int> coords, int value) { dungeon[coords.first][coords.second] = value; }
void Dungeon::set_temp_tile(pair<int, int> coords, int value) { temp_dungeon[coords.first][coords.second] = value; }
void Dungeon::set_generations(int gen) {generations = gen; }
int Dungeon::get_tile(pair<int, int> coords) { return dungeon[coords.first][coords.second]; }
int Dungeon::get_temp_tile(pair<int, int> coords) { return temp_dungeon[coords.first][coords.second]; }
int Dungeon::get_generations() {return this->generations; }

//Returns true if the given (x,y) coords are in the bounds of the dungeon, false otherwise
bool Dungeon::is_in_bounds(int x, int y)
{
	if(x>=0 && x<num_rows && y>=0 && y<num_cols)
	{
		return true;
	}
	return false;
}
//If val = 0 return isNextToFloor, else return neighborhoodValue
int Dungeon::get_neighborhood(int val, int rowIndex, int colIndex) 
{
	//Note: Out of bounds will be considered a wall / not a floor 
	int neighborhoodValue = 0;
	int isNextToFloor = 0;
	int temp = 0;
	//Row loop starting from above row going to below row
	for(int i=(rowIndex-1); i<=(rowIndex+1); i++)
	{
		//Column loop starting from above col going to below col
		for(int j=(colIndex-1); j<=(colIndex+1); j++)
		{
			//Checks if index is in bounds
			if(is_in_bounds(i,j))
			{
				//Makes sure is not counting the tile in its own neighborhood
				if(i != rowIndex || j != colIndex)
				{
					//Gets the tile at the index, adds its value to the total, checks if it is a floor
					temp = get_tile(pair<int, int>(i, j));
					neighborhoodValue += temp;
					if(temp == FLOOR)
					{
						isNextToFloor = 1;
					}
				}
			}
			else
			{
				//Considers out of bounds to be walls (currently adds 0, here in case we need to change what we consider out of bounds)
				neighborhoodValue += WALL;
			}
		}
	}
	//If val = 0 return isNextToFloor, else return neighborhoodValue
	if(val == 0)
	{
		//Returns 0 if false, 1 if true
		return isNextToFloor;
	}
	else if (val == 1)
	{
		return neighborhoodValue;
	}
	else 
	{
		return -1;
	}
}

//Generated the starting noise for the dungeon map 
void Dungeon::noise_grid(int size, int ratio)
{
	//Expecting: Size>=0, Ratio between 1 and 100 
	int comparer = 0;
	//Makes sure the size is in bounds for both the rows and columns
	if(size >= num_rows)
	{
		size = num_rows-1;
	}
	if(size >= num_cols)
	{
		size = num_cols-1;
	}
	//Loops through given size cube and created noise based on the given ratio 
	for(int i=0; i <= size; i++)
	{
		for(int j=0; j <= size; j++)
		{
			//If (random number from 1-100 is >= ratio), then make tile floor 
			comparer = rand() % (100+1);
			if(comparer >= ratio)
			{
				set_tile(pair<int, int>(i, j), FLOOR);
			}
		}
	}
}

/**
 * This is the ruleset we will apply to the current tile. It makes its changes onto a temporary grid
 * Things to consider forward: Do we want to use time for our rules? 
 */
void Dungeon::apply_rule(pair<int, int> coords)
{
	int neighborhood = get_neighborhood(1, coords.first, coords.second);
	cout << neighborhood << " ";
	// If current tile has less than or equal to 4 neighboring floors, it will be a floor tile. Otherwise, it will be a wall tile.	
	if (neighborhood <= 4) { set_temp_tile(coords, FLOOR); }
	else { set_temp_tile(coords, WALL); }	
}

void Dungeon::calculate_generation()
{
	// Iterate through grid one by one and apply rule for temp grid
	for (int row = 0; row < num_rows; row++)
	{
		for (int col = 0; col < num_cols; col++)
		{
			apply_rule(pair<int, int>(row, col));
		}
	}

	// Copy temp grid to dungeon grid
    for (int row = 0; row < num_rows; row++)
    {
        for (int col = 0; col < num_cols; col++)
        {
			int value = get_temp_tile(pair<int, int>(row, col)); // Get value from temporary grid
            set_tile(pair<int, int>(row, col), value); // Put value above into the dungeon grid
        }
    }
}

void Dungeon::make_maze()
{
	// Temporarily setting noise grid to by 10 x 10
//	noise_grid(10, 50);

	// Continue to create the next generation till the maximum amount
	for (; time < generations; time++)
	{
		calculate_generation();
	}
}

void Dungeon::print()
{
	for (int row = 0; row < num_rows; row++)
	{
		for (int col = 0; col < num_cols; col++)
		{
			int value = get_tile(pair<int, int>(row, col));
			cout << value << " ";
		}
		cout << endl;
	}
}



//TODO 
// Main calling Dungeon appropriately and terminal things ./automata length width #ofgenerations lengthOfNoiseGrid=halfOfLength -- Sidd 
// Testing -- Both, Test other person's functions! 
//
// Later: 
// More cool custom stuff with apply_rule (more tiles, cooler ruleset)
// Calculate runtime with Big O Notation and its actual runtime (f function)
// Make maze print prettier
#endif

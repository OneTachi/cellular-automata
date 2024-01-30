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
//Used for extended Unicoe (possibly, not in use currently)
// #include <io.h>
//#include <fcntl.h>
//#include <stdio.h>

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
	Dungeon(int, int, int, int, int, bool);	

	void set_tile(pair<int, int>, int);
	void set_temp_tile(pair<int, int>, int); // Set tile for temporary grid
	void set_generations(int);
	int get_tile(pair<int, int>);
	int get_temp_tile(pair<int, int>);
	int get_generations();

	int get_neighborhood(int, int, int); // Get Moore Neighborhood
	bool is_in_bounds(int, int);
	void print(bool);
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
/*
 * General Constructor 
 * Takes in the size of the dungeon in two ints, and how long to generate the dungeon
 * Each dungeon is at least 1x1 in size 
 * Makes every tile a wall
*/
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
}
/*
 * General Constructor 
 * Takes in the size of the dungeon in two ints, how long to generate the dungeon, how big to make the noise grid, and the noise ratio
 * Each dungeon is at least 1x1 in size 
 * Makes every tile a wall to start
 * Generates random noise in the dungon using the noise_size and ratio 
 * Then makes the maze and prints it 
*/
Dungeon::Dungeon(int rows, int cols, int generationGoal, int noise_size, int ratio, bool pretty = true)
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
	noise_grid(noise_size, ratio);
	make_maze();
	print(pretty);
}
/*
 * Utility function that outputs the maze as a string.
 * Numbers grouped togetiher indicate a row. Spaces indicate the next row in the dungeon. 
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
/*
 * Takes coords of a tile in the dungeon 
 * If val = 0 return isNextToFloor, else return neighborhoodValue
 * Is next to floor checks if the tile is next to a floor tile, if true return 1, else return false
 * Neighborhood value returns the total value of the neighborhood of a cell
*/
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
/*
 * Generates the starting noise for the dungeon map 
 * Starts at 0,0 and creates a square of noise based on the size
 * Can only be as large as the smallest size of grid (length or width)
 * The ratio is the rough percentage of noise added to the grid
 * Expecting: Size>=0, Ratio between 1 and 100 
 * Higher ratio = More Walls 	Lower Ratio = More Floors 
 * (Ratio of 101 == All Walls)	(Ratio of 0 == All Floors)
*/
void Dungeon::noise_grid(int size, int ratio)
{
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
	for(int i=0; i < size; i++)
	{
		for(int j=0; j < size; j++)
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
 * Takes a tile and checks its neighborhood 
 * If it has 0 neighbors, nothing happens, between 1 and 4 neighbors, becomes a Floor, 5 to 8 neighbors and it becomes a wall
 */
void Dungeon::apply_rule(pair<int, int> coords)
{
	int neighborhood = get_neighborhood(1, coords.first, coords.second);
	//cout << neighborhood << " ";
	// If current tile has less than or equal to 4 neighboring floors, it will be a floor tile. Otherwise, it will be a wall tile.	
	if (neighborhood <= 4) 
	{ 
		if(neighborhood > 0) //Change to == 3 for mazelike generations 
		{
			set_temp_tile(coords, FLOOR); 
		}
	}
	else { set_temp_tile(coords, WALL); }	
	//cout << "" << endl;
}
/*
 * Applys the rule to every cell in the dungeon 
 * Puts the new tile values in a temporary grid, then copies the temp grid to the original 
*/
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
//Calls calculate generation for 'generations' amount of times
void Dungeon::make_maze()
{
	// Continue to create the next generation till the maximum amount
	for (; time < generations; time++)
	{
		calculate_generation();
	}
}
/*
 * Prints the maze in a grid 
 * Defaults to pretty print, contains a print of just 1 and 0 for debugging 
 * Possible change in future: Make pretty print use a full box character and work on linux and windows 
 * 
*/
void Dungeon::print(bool pretty)
{
	if(pretty)
	{
		for (int row = 0; row < num_rows; row++)
		{
			for (int col = 0; col < num_cols; col++)
			{
				int value = get_tile(pair<int, int>(row, col));
				if(value == WALL)
				{
					//Extended ASCII table code for filled in box
					//cout << (char)254u;
					cout << "+";
				}
				else if(value == FLOOR)
				{
					cout << " ";
				}
			}
			cout << endl;
		}
	}
	else
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
	
}



//TODO 
// Main calling Dungeon appropriately and terminal things ./automata length width #ofgenerations lengthOfNoiseGrid=halfOfLength -- Sidd 
// Pretty_print(): Make the resulting dungeon look more like a dungeon when printed out. Do not make a new function, instead have print() accept a boolean that is default to true, if bool = true do pretty_print. If false, goes to 
// already established print() -- Rory
// Test bigger dungeons and see if they look like dungeons! -- Both
// Comments / Readme / Pretty Print
//
// Later: 
// More cool custom stuff with apply_rule (more tiles, cooler ruleset)
// Calculate runtime with Big O Notation and its actual runtime (f function)
// Choose where noise grid does its noise grid stuff (coordinates/general location etc.)
#endif

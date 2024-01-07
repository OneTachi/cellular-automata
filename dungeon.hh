/**
* Siddharth Lokula 
* created: December 25, 2023
*/

#ifndef DUNGEON_HH
#define DUNGEON_HH

#include <vector>

//The value each cell starts with
const int startingCellValue = 0;

// We will keep this simple, a floor and a wall. 1 & 0 will allow us to easily calculate the moore's neighborhood and determine # of floors/walls
const int FLOOR = 1; 
const int WALL = 0;

using namespace std; 
class Dungeon
{
public:	
	Dungeon(int, int);
	
	void set_tile(pair<int, int>, int);
	void set_temp_tile(pair<int, int>, int); // Set tile for temporary grid
	int get_tile(pair<int, int>);
	int get_temp_tile(pair<int, int>);

	int get_neighborhood(int, int, int); // Get Moore Neighborhood
	void print();
	void apply_rule(pair<int, int>);
	void calculate_generation();
	
private:
	vector<vector<int>> dungeon; // Row then column for access
	vector<vector<int>> temp_dungeon; // Our temporary grid for each generation
	int num_rows;
	int num_cols;
	int time = 0; // The current generation we are on
	int generations = 0; // Number of generations we would like to go up to
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
	temp_dungeon = vector<vector<int>>(num_rows, vector<int>(num_cols));
	// make_maze()
}


// Getters and Setters
void Dungeon::set_tile(pair<int, int> coords, int value) { dungeon[coords.first][coords.second] = value; }
void Dungeon::set_temp_tile(pair<int, int> coords, int value) { temp_dungeon[coords.first][coords.second] = value; }
int Dungeon::get_tile(pair<int, int> coords) { return dungeon[coords.first][coords.second]; }
int Dungeon::get_temp_tile(pair<int, int> coords) { return temp_dungeon[coords.first][coords.second]; }

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
		if(temp == FLOOR)
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

/**
 * This is the ruleset we will apply to the current tile. It makes its changes onto a temporary grid
 * Things to consider forward: Do we want to use time for our rules? 
 */
void Dungeon::apply_rule(pair<int, int> coords)
{
	int neighborhood = get_neighborhood(coords.first, coords.second);
	
	// If neighborhood has 4 or more walls, the current tile is a floor. Otherwise, it will be a wall.	
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

	// Copy temp grid to dungeon grid TODO
	
}





//TODO 
// print() -- Sidd
// Finish calculate_generation -- Sidd
// make_maze() -- Sidd 
// Main calling Dungeon appropriately and terminal things ./automata length width #ofgenerations lengthOfNoiseGrid=halfOfLength -- Sidd 
// Add to Dungeon constructor (generation + call make_maze, all values of starting grid will be WALL) -- Rory 
// Make get_neighborhood consider out of bounds as walls -- Rory
// noise_grid(length, ratio) | grid will always spawn top left & don't forget about considering too big of a noise grid | If want fancy fancy, put location in center -- Rory
//
// Later: 
// More cool custom stuff with apply_rule (more tiles, cooler ruleset)
#endif

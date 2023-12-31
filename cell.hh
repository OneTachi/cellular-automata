

#ifndef CELL_HH
#define CELL_HH

#include <vector>

using namespace std;

// Cell class - they should contain some value, 0 for floor, 1 for rock, 2 for wall (might need to change in future for rules to work), function to get the value of neighborhood (getneighborhood?)

class Cell
{
public:
	Cell(int);
	void setCellValue(int);
	int getCellValue();
	void print();
	
private:
	int value;
};
//Constructor
Cell::Cell(int valueGiven)
{
	value = valueGiven;
}
//Getter and Setter for value
void Cell::setCellValue(int newVal)
{
	value = newVal;
}
int Cell::getCellValue()
{
	return value;
}

#endif

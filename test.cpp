#include "dungeon.hh"
#include <iostream>
#include <cassert>
#include <string.h>

using namespace std;

void test_compare();
void test_fixed_dungeon();
void test_in_bounds();
void test_greater_out_bounds();
void test_less_out_bounds();
void test_in_first_bound();
void test_in_last_bound();

int main()
{
	/*	
	Dungeon dungeon(10, 10, 2);
	dungeon.noise_grid(10, 50);
	cout << endl;
	dungeon.print();
	cout << endl;
	dungeon.make_maze();
	cout << endl;
	dungeon.print();
	*/

//	test_compare();
	test_fixed_dungeon();
	test_in_bounds();
	test_greater_out_bounds();
	test_less_out_bounds();
	test_in_first_bound();
	test_in_last_bound();
	return 0;	
}

void test_compare()
{
	Dungeon dungeon(10, 10, 1);
	Dungeon result(10, 10, 1);
	assert( dungeon.str_maze().compare(result.str_maze()) ? 0 : 1 );
}

void test_fixed_dungeon()
{
	Dungeon test("10 01");
	test.print();
}

void test_in_bounds()
{
	Dungeon dun("111 111 111");
	assert(dun.is_in_bounds(1, 1));
}

void test_greater_out_bounds()
{
	Dungeon dun("11 11");
	assert(!dun.is_in_bounds(3, 0));
}

void test_less_out_bounds()
{
	Dungeon dun("11 11");
	assert(!dun.is_in_bounds(-1, 0));
}

void test_in_first_bound()
{
	Dungeon dun("00 00");
	assert(dun.is_in_bounds(0,0));
}
void test_in_last_bound()
{
	Dungeon dun("00 00");
	assert(dun.is_in_bounds(1, 1));
}


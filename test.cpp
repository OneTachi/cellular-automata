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

void test_neigh_no_floor();
void test_neigh_up_floor();
void test_neigh_all_floor();
void test_neigh_bounds();
void test_neigh_tile();

void test_apply_rule();

int main()
{
	cout <<"Starting Testing!"<<endl;
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

	test_neigh_no_floor();
	test_neigh_up_floor();
	test_neigh_all_floor();
	test_neigh_bounds();
	test_neigh_tile(); 
	
	test_apply_rule();
	
	cout <<"Finished Testing!"<<endl;
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
void test_neigh_no_floor()
{
	Dungeon dun("000 000 000");
	assert(dun.get_neighborhood(1, 1, 1) == 0);
}
void test_neigh_up_floor()
{
	Dungeon dun("010 000 000");
        assert(dun.get_neighborhood(1, 1, 1) == 1);
}
void test_neigh_all_floor()
{
        Dungeon dun("111 101 111");
        assert(dun.get_neighborhood(1, 1, 1) == 8);
}

void test_neigh_bounds()
{
        Dungeon dun("0");
        assert(dun.get_neighborhood(1, 0, 0) == 0);
}
void test_neigh_tile()
{
        Dungeon dun("1");
        assert(dun.get_neighborhood(1, 0, 0) == 0);
}



void test_apply_rule()
{
	
	Dungeon test1("0");
	test1.set_generations(1);
	test1.make_maze();
	assert(test1.get_tile(pair<int, int>(0,0)) == 1);
	
	Dungeon test2("000 000 000");
	test2.set_generations(1);
	test2.make_maze();
	assert(test2.get_tile(pair<int, int>(0,0)) == 1);
	assert(test2.get_tile(pair<int, int>(0,1)) == 1);
	assert(test2.get_tile(pair<int, int>(0,2)) == 1);
	assert(test2.get_tile(pair<int, int>(1,0)) == 1);
	assert(test2.get_tile(pair<int, int>(1,1)) == 1);
	assert(test2.get_tile(pair<int, int>(1,2)) == 1);
	assert(test2.get_tile(pair<int, int>(2,0)) == 1);
	assert(test2.get_tile(pair<int, int>(2,1)) == 1);
	assert(test2.get_tile(pair<int, int>(2,2)) == 1);
	
	Dungeon test3("111 111 111");
	test3.set_generations(1);
	test3.make_maze();
	assert(test3.get_tile(pair<int, int>(0,0)) == 1);
	assert(test3.get_tile(pair<int, int>(0,1)) == 0);
	assert(test3.get_tile(pair<int, int>(0,2)) == 1);
	assert(test3.get_tile(pair<int, int>(1,0)) == 0);
	assert(test3.get_tile(pair<int, int>(1,1)) == 0);
	assert(test3.get_tile(pair<int, int>(1,2)) == 0);
	assert(test3.get_tile(pair<int, int>(2,0)) == 1);
	assert(test3.get_tile(pair<int, int>(2,1)) == 0);
	assert(test3.get_tile(pair<int, int>(2,2)) == 1);
	
}

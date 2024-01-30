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

// Does not completely test all cardinal directions.
void test_nextto_all_floor();
void test_nextto_no_floor();
void test_nextto_no_isfloor();
void test_nextto_diagonal_floor();

void test_noise_all();
void test_noise_one();

void test_apply_rule();
void test_print();

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

	test_nextto_all_floor();
	test_nextto_no_floor();
	test_nextto_no_isfloor();
	test_nextto_diagonal_floor();
	
	test_noise_all();
	test_noise_one();

	test_apply_rule();
	test_print();
	
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
	test.print(0);
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
void test_nextto_all_floor()
{
	Dungeon dun("111 101 111");
	assert(dun.get_neighborhood(0, 1, 1) == 1);
}
void test_nextto_no_floor()
{
        Dungeon dun("000 000 000");
        assert(dun.get_neighborhood(0, 1, 1) == 0);
}
void test_nextto_no_isfloor()
{
        Dungeon dun("000 010 000");
        assert(dun.get_neighborhood(0, 1, 1) == 0);
}
void test_nextto_diagonal_floor()
{
        Dungeon dun("100 000 000");
        assert(dun.get_neighborhood(0, 1, 1) == 1);
}
void test_noise_all()
{
	Dungeon dun(3, 3, 0);
	dun.noise_grid(3, 0);
	assert(dun.get_tile(pair<int, int>(0, 0)) == 1);
    	assert(dun.get_tile(pair<int, int>(2, 2)) == 1);
}
void test_noise_one()
{
        Dungeon dun(3, 3, 1);
        dun.noise_grid(1, 0);
        assert(dun.get_tile(pair<int, int>(0, 0)) == 1);
}

void test_apply_rule()
{
	
	Dungeon test1("0");
	test1.set_generations(1);
	test1.make_maze();
	assert(test1.get_tile(pair<int, int>(0,0)) == 0);
	
	Dungeon test2("000 000 000");
	test2.set_generations(1);
	test2.make_maze();
	assert(test2.get_tile(pair<int, int>(0,0)) == 0);
	assert(test2.get_tile(pair<int, int>(0,1)) == 0);
	assert(test2.get_tile(pair<int, int>(0,2)) == 0);
	assert(test2.get_tile(pair<int, int>(1,0)) == 0);
	assert(test2.get_tile(pair<int, int>(1,1)) == 0);
	assert(test2.get_tile(pair<int, int>(1,2)) == 0);
	assert(test2.get_tile(pair<int, int>(2,0)) == 0);
	assert(test2.get_tile(pair<int, int>(2,1)) == 0);
	assert(test2.get_tile(pair<int, int>(2,2)) == 0);
	
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
void test_print()
{
	cout << "Maze 1: " << endl;
	Dungeon testPrint1("000 000 000");
	testPrint1.print(1);
	cout << "Maze 2: " << endl;
	Dungeon testPrint2("111 111 111");
	testPrint2.print(1);
	cout << "Maze 3: " << endl;
	Dungeon testPrint3("000 111 000");
	testPrint3.print(1);
	cout << "Maze 4: " << endl;
	Dungeon testPrint4("111 000 111");
	testPrint4.print(1);
	cout << "Maze 5: " << endl;
	Dungeon testPrint5("111 101 111");
	testPrint5.print(1);
	cout << "Maze 6: " << endl;
	Dungeon testPrint6("000 010 000");
	testPrint6.print(1);
	cout << "Maze 7: " << endl;
	Dungeon testPrint7("00000 01110 01010 01110 00000");
	testPrint7.print(1);
}

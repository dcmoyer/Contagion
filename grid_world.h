#ifndef GRID_WORLD_H
#define GRID_WORLD_H

#include "world.h"

class grid_point;

class grid_world : public world{
	
	grid_world();
	
	grid_point the_grid[CELL_LENGTH][CELL_LENGTH];
	
};

class grid_point{
	
	double value;
	
	double up_cost;
	double down_cost;
	double left_cost;
	double right_cost;
	
};


#endif
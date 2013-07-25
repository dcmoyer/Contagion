#ifndef GRID_WORLD_H
#define GRID_WORLD_H

#include "constants.h"
#include "agent.h"
#include "wall.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstddef>
#include <cmath>


class grid_point;
class grid_iter;


class grid_world{
private:
	
	vector<agent*> agents_master;
	vector<static_agent*> static_agents_master;
	grid_point* the_grid[RESOLUTION][RESOLUTION];
	
public:
	grid_world();
	~grid_world();
	
	friend class grid_point;
	friend class grid_iter;
	
};

class grid_point{
private:
	double value;
	double up_cost;
	double down_cost;
	double left_cost;
	double right_cost;
	
	grid_point* up;
	grid_point* down;
	grid_point* left;
	grid_point* right;
	
	bool goal_flag;
	bool impass_flag;
	
public:
	
	grid_point();
	
	void intialize_static_field();
	
	void add_to_value(double v);
	void set_value(double v);
	
	friend class grid_world;
	friend class grid_iter;
	
};

class grid_iter{
private:
	grid_point* current;
	
public:
	
	friend class grid_point;
	friend class grid_world;
	
};


#endif
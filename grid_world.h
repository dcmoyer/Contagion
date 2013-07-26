#ifndef GRID_WORLD_H
#define GRID_WORLD_H

#include "constants.h"
#include "grid_agent.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstddef>
#include <cmath>
#include <queue>


class grid_point;
class grid_iter;


class grid_world{
private:
	
	vector<grid_agent*> agents_master;
	vector<static_agent*> static_agents_master;
	grid_point* the_grid[RESOLUTION_HEIGHT][RESOLUTION_WIDTH];
	
public:
	grid_world();
	~grid_world();
	
	void update_forward_accel();
	void initialize_static_field();
	void place_fire(double x, double y, double (*p)(double), double (* v_s)(double, double, double, double) );
	void place_goal(double x, double y, double (*p)(double));
	void place_agent(double x, double y, double (*p)(double), double (* v_s)(double, double, double, double) );
	void print_csv(std::string filename);
	void print_static_csv();
	
	void euler_update();
	void ab4_update();
	
	friend class grid_point;
	friend class grid_iter;
	
};

class grid_point{
private:
	double value;
	/*double up_cost;
	double down_cost;
	double left_cost;
	double right_cost;*/
	
	double cost[4];
	
	/*grid_point* up;
	grid_point* down;
	grid_point* left;
	grid_point* right;*/
	
	grid_point* direction[4];
	
	bool goal_flag;
	bool impass_flag;
	
public:
	
	grid_point();
		
	void add_to_value(double v);
	void set_value(double v);
	
	friend class grid_world;
	friend class grid_iter;
	
};

struct edge{
	grid_point* from;
	grid_point* to;
	double cardinality;
	double value;
}

bool edge_comp(edge a, edge b){
	return a.value > b.value;
}

class grid_iter{
private:
	grid_point* current;
	
public:
	
	friend class grid_point;
	friend class grid_world;
	
};


#endif
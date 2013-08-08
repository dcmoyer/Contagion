#ifndef GRID_WORLD_H
#define GRID_WORLD_H

#include "constants.h"
#include "grid_agent.h"
#include "static_agent.h"
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
	
	std::vector<grid_agent*> agents_master;
	std::vector<static_agent*> static_agents_master;
	grid_point* the_grid[RESOLUTION_HEIGHT][RESOLUTION_WIDTH];
	
public:
	
	double global_max;
	grid_world();
	~grid_world();
	
	void update_forward_accel();
	void initialize_static_field();
	void place_fire(double x, double y, double (*p)(double, double, static_agent*), double (* v_s)(double, double, static_agent*) );
	void place_goal(double x, double y, double (*p)(double, double, static_agent*));
	void place_agent(double x, double y, double (*p)(double, double, grid_agent*), double (* v_s)(double, double, grid_agent*) );
	void place_wall(double x, double y, double n_x, double n_y, double length ,double (*p)(double, double, static_agent*), double (* v_s)(double, double, static_agent*));
	void print_csv(std::string filename);
	void print_static_csv();
	void print_static_wall_csv();
	void print_field();
	
	void update_agent_pos_euler();
	void update_agent_pos_ab4();
	
	friend class grid_point;
	
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
	
	int i;
	int j;
	
public:
	
	grid_point();
		
	void add_to_value(double v);
	void set_value(double v);
	
	friend class grid_world;
	
};

struct edge{
	grid_point* from;
	grid_point* to;
	int cardinality;
	int cardinality2;
	double value;
	
	edge(grid_point* f =0, grid_point* t = 0, int c=0, int c2=0, double v=0)
	{
		from = f;
		to = t;
		cardinality = c;
		cardinality2 = c2;
		value = v;
	}
		
	/*edge& operator= (const edge& right){
		from = right.from;
		to = right.to;
		cardinality = right.cardinality;
		value = right.value;
		return *this;
	}*/
	
	/*edge(const edge& right){
		from = right.from;
		to = right.to;
		cardinality = right.cardinality;
		value = right.value;
	}*/
};

class edge_comp2{
public:
	bool operator () (edge a, edge b){
		return a.value > b.value;
	}
	
};


#endif
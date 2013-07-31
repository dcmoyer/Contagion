#ifndef STATIC_AGENT_H
#define STATIC_AGENT_H

#include <cmath>

class static_agent{
private:
	double x_pos;
	double y_pos;
	
	int node_pos_x;
	int node_pos_y;
	
	int agent_type;
public:
	static_agent();
	static_agent(double x, double y, int t, double (* p)(double, double, static_agent*), double (* vb)(double,double,double,double));
	
	double (* potential)(double, double, static_agent* );
	double (* velocity_block)(double, double, double, double);
	
	double get_x_pos();
	double get_y_pos();
	int get_x_node_pos();
	int get_y_node_pos();
	
	int get_agent_type();
};

class static_wall : public static_agent {

	
public:
	double normal_x;
	double normal_y;
	double length;
	static_wall(double center_x, double center_y, int t, double n_x, double n_y, double len, double (* p)(double, double, static_agent*) , double (* vb)(double, double, double, double));
		
};

#endif
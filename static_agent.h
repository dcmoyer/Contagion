#ifndef STATIC_AGENT_H
#define STATIC_AGENT_H

#include <cmath>

class static_agent{
private:
	double x_pos;
	double y_pos;
	
	int node_pos_x;
	int node_pos_y;
public:
	
	static_agent(double x, double y, (* p)(double), (* vb)(double,double,double,double));
	
	double (* potential)(double);
	double (* velocity_block)(double, double, double, double);
	
	double get_x_pos();
	double get_y_pos();
	int get_x_node_pos();
	int get_y_node_pos();
	
}

#endif
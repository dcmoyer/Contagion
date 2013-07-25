#include "static_agent.h"

static_agent::static_agent(double x, double y, (* p)(double), (* vb)(double,double,double,double)){

	x_pos = x;
	y_pos = y;
	
	node_pos_x = round(x);
	node_pos_y = round(y);
	
	potential = p;
	velocity_block = b;

}


double static_agent::get_x_pos(){
	return x_pos;
}
double static_agent::get_y_pos(){
	return y_pos;
}
int static_agent::get_x_node_pos(){
	return node_pos_x;
}
int static_agent::get_y_node_pos(){
	return node_pos_y;
}
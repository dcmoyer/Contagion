#include "static_agent.h"

static_agent::static_agent(){
	x_pos = 0;
	y_pos = 0;
	node_pos_x = 0;
	node_pos_y = 0;
	potential = NULL;
	velocity_block = NULL;
	
	agent_type = 0;

}

static_agent::static_agent(double x, double y, int t, double (* p)(double, double, static_agent*), double (* vb)(double,double,static_agent*)){

	x_pos = x;
	y_pos = y;
	
	node_pos_x = round(x);
	node_pos_y = round(y);
	
	potential = p;
	velocity_block = vb;
	
	agent_type = t;
	
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
int static_agent::get_agent_type(){
	return agent_type;	
}

static_wall::static_wall(double center_x, double center_y, int t, double n_x, double n_y, double len, 
double (* p)(double ,double, static_agent*), double (* vb)(double, double, static_agent*)) :
 static_agent(center_x, center_y, t, p, vb) {
	
	double n_mag = sqrt(n_x*n_x + n_y*n_y);
	
	normal_x = n_x/n_mag;
	normal_y = n_y/n_mag;
	
	length = len;
		
}	

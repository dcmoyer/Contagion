#include "wall.h"

wall::wall(double center_x, double center_y, double n_x, double n_y, double len,  void (* up)(agent*,agent*)){

	x_coord = center_x;
	y_coord = center_y;
	
	double n_mag = sqrt(pow(n_x,2) + pow(n_y,2));
	
	n_x = n_x / n_mag;
	n_y = n_y / n_mag;
	
	normal_x = n_x;
	normal_y = n_y;
	length = len;
	
	update = up;
	
    for(int i = 0; i < HIST_LENGTH; i++)
        x_veloc[i] = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        x_accel[i] = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        y_veloc[i] = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        y_accel[i] = 0;
	
    q_mag = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        q_change[i] = 0;
	
    NearestNeighbor_count = 0;
    
    agent_type = 2;
    
    alive = true;
	

}

void wall::drag(){
    return;
}

int wall::get_heading()
{
	double xx = normal_x * normal_x;
	double yy = normal_y * normal_y;
	if(yy == 1)
		return 1;
	else if(xx == 1)
		return 2;
	else
		return 0;

}
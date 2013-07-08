#include "predator.h"
#include <cstdlib>

predator::predator(double x, double y, void (* up)(agent*,agent*)) {
  //Assign Coordinates
	    x_coord = x;
	    for(int i = 0; i < HIST_LENGTH; i++)
	        x_veloc[i] = 0;
	    for(int i = 0; i < HIST_LENGTH; i++)
	        x_accel[i] = 0;
	    
	    y_coord = y;
	    for(int i = 0; i < HIST_LENGTH; i++)
	        y_veloc[i] = 0;
	    for(int i = 0; i < HIST_LENGTH; i++)
	        y_accel[i] = 0;
	    
	    z_coord = 0;
	    for(int i = 0; i < HIST_LENGTH; i++)
	        z_veloc[i] = 0;
	    for(int i = 0; i < HIST_LENGTH; i++)
	        z_accel[i] = 0;
	    
	    //Assign Contagion
	    q_mag = 0;
	    for(int i = 0; i < HIST_LENGTH; i++)
	        q_change[i] = 0;
	    
	    //Assign NN
	    NearestNeighbor_count = 0;
	    
	    agent_type = 'p';
	    
	    update = up; //NULL 
	    
	    alive = true;
	    
}
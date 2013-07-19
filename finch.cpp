#include "finch.h"

 finch::finch(double x, double y, void (* up)(agent*,agent*)) {
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
	    
	    //Assign Contagion
	    q_mag = 0;
	    for(int i = 0; i < HIST_LENGTH; i++)
	        q_change[i] = 0;
	    
	    //Assign NN
	    NearestNeighbor_count = 0;
	    agent_type = 0;
	    update = up;
	    alive = true;
		NearestPred_count = 0;
		q_change_prey = 0;
		q_change_pred = 0;
		x_accel_pred = 0;
		y_accel_pred = 0;
	
		x_accel_prey = 0;
		y_accel_prey = 0;

		for(int i = 0; i < 7; i++)
		{
			params[i] = rand()% 256;
		}

		gamma =  params[0] / 255.0;
		adrenaline = params[1] / 255.0;
		fear_decay = params[2] / 255.0;
		empathy = params[3] / 255.0;
		emote_pdpy_ratio = params[4] / 255.0;
		motion_pdpy_ratio = params[5] / 255.0;
		attr_align_ratio = params[6] / 255.0;

} 
 
 finch::finch(double x, double y, void (* up)(agent*,agent*), unsigned char genes[7]) {
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
	    
	    //Assign Contagion
	    q_mag = 0;
	    for(int i = 0; i < HIST_LENGTH; i++)
	        q_change[i] = 0;
	    
	    //Assign NN
	    NearestNeighbor_count = 0;
	    agent_type = 0;
	    update = up;
	    alive = true;
		NearestPred_count = 0;
		q_change_prey = 0;
		q_change_pred = 0;
		x_accel_pred = 0;
		y_accel_pred = 0;
	
		x_accel_prey = 0;
		y_accel_prey = 0;

		for(int i = 0; i < 7; i++)
		{
			params[i] = genes[i];
		}

		gamma =  params[0] / 255.0;
		adrenaline = params[1] / 255.0;
		fear_decay = params[2] / 255.0;
		empathy = params[3] / 255.0;
		emote_pdpy_ratio = params[4] / 255.0;
		motion_pdpy_ratio = params[5] / 255.0;
		attr_align_ratio = params[6] / 255.0;

} 

 void finch::normalize_accel()
{
	if(NearestNeighbor_count != 0)
      {
        x_accel_prey =  (x_accel_prey / (double) NearestNeighbor_count);
		y_accel_prey =  (y_accel_prey / (double) NearestNeighbor_count);
		q_change_prey = (q_change_prey / (double) NearestNeighbor_count);
	}

	if(NearestPred_count != 0)
	{
		x_accel_pred =  (x_accel_pred / (double) NearestPred_count);
		y_accel_pred =  (y_accel_pred / (double) NearestPred_count);
	}

	x_accel[0] +=  motion_pdpy_ratio * x_accel_prey + (1- motion_pdpy_ratio) * x_accel_pred;
	y_accel[0] +=  motion_pdpy_ratio * y_accel_prey + (1- motion_pdpy_ratio) * y_accel_pred;
	q_change[0] = emote_pdpy_ratio * q_change_prey + (1 - emote_pdpy_ratio) *q_change_pred;

	x_accel_prey =  0;
	y_accel_prey = 0;
	x_accel_pred =  0;
	y_accel_pred = 0;

	q_change_prey = 0;
	q_change_pred = 0;

}

 void finch::drag()
{
    double veloc_mag = x_veloc[0]*x_veloc[0] + y_veloc[0]*y_veloc[0];
	double A = alpha_1*4*pow((q_mag - q_mag * adrenaline + adrenaline), 2);
	x_accel[0] += (A - veloc_mag)*x_veloc[0];
	y_accel[0] += (A - veloc_mag)*y_veloc[0];
	q_change[0] += -q_mag * fear_decay;
    NearestNeighbor_count = 0;
} 


void finch::iterate_NearestPred(){
    
    NearestPred_count++;
    
}

void finch::add_to_x_accel_prey(double add_to_accel){
    
    x_accel_prey += add_to_accel;
    
}

void finch::add_to_y_accel_prey(double add_to_accel){
    
    y_accel_prey += add_to_accel;
    
}

void finch::add_to_x_accel_pred(double add_to_accel){
    
    x_accel_pred += add_to_accel;
    
}

void finch::add_to_y_accel_pred(double add_to_accel){
    
    y_accel_pred += add_to_accel;
    
}


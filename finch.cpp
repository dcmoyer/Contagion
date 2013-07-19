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

		gamma = 0;
		v_align_mag = 0;
		pred_repel = 0;
		py_pd_kinetic = 0;
		py_pd_emote = 0;
		scs = 0;
		decay = 0;

} 
 
 void finch::normalize_accel()
{
	if(NearestNeighbor_count != 0)
      {
        x_accel_prey =  (x_accel_prey / (double) NearestNeighbor_count);
		y_accel_prey =  (y_accel_prey / (double) NearestNeighbor_count);
		x_accel_pred =  (x_accel_pred / (double) NearestPred_count);
		y_accel_pred =  (y_accel_pred / (double) NearestPred_count);


		q_change_prey = (q_change_prey / (double) NearestNeighbor_count);


		x_accel[0] =  py_pd_kinetic * x_accel_prey + (1- py_pd_kinetic) * x_accel_pred;
		y_accel[0] =  py_pd_kinetic * y_accel_prey + (1- py_pd_kinetic) * y_accel_pred;
		
		q_change[0] = py_pd_emote * q_change_prey + (1 - py_pd_emote) *q_change_pred;
   }

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
	double A = alpha_1*4*pow((q_mag - q_mag * scs + scs), 2);
	x_accel[0] += (A - veloc_mag)*x_veloc[0];
	y_accel[0] += (A - veloc_mag)*y_veloc[0];
	q_change[0] += -q_mag * decay;
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



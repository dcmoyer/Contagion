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
		wall_accel_x = 0;
		wall_accel_y = 0;

		for(int i = 0; i < 9; i++)
		{
			params[i] = rand()% 256;
		}

	
	
		gamma_v = params[0] / 255.0;
		adrenaline = params[1] / 255.0;
		fear_decay = params[2] / 255.0;
		if(EX){
            empathy = EMPATHY;
        }else{
            empathy = params[3] / 255.0;
        }
		emote_pdpy_ratio = params[4] / 255.0;
		motion_pdpy_ratio = params[5] / 255.0;
		attr_align_ratio = params[6] / 255.0;
        gamma_emo_prey = params[7] / 255.0;
        gamma_emo_pred = params[8] / 255.0;

} 
 
 finch::finch(double x, double y, void (* up)(agent*,agent*), unsigned char genes[9]) {
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

		wall_accel_x = 0;
		wall_accel_y = 0;

		for(int i = 0; i < 9; i++)
		{
			params[i] = genes[i];
		}

		gamma_v = params[0] / 255.0;
		adrenaline = params[1] / 255.0;
		fear_decay = params[2] / 255.0;
		if(EX){
            empathy = EMPATHY;
        }else{
            empathy = params[3] / 255.0;
        }
		emote_pdpy_ratio = params[4] / 255.0;
		motion_pdpy_ratio = params[5] / 255.0;
		attr_align_ratio = params[6] / 255.0;
        gamma_emo_prey = params[7] / 255.0;
        gamma_emo_pred = params[8] / 255.0;

} 

 void finch::normalize_accel()
{
	if(NearestNeighbor_count != 0)
      {
        x_accel_prey =  x_accel_prey * (1 / (double) NearestNeighbor_count);
		y_accel_prey = y_accel_prey *  (1 / (double) NearestNeighbor_count);
		q_change_prey = q_change_prey * (1 / (double) NearestNeighbor_count);
	}

	if(NearestPred_count != 0)
	{
		x_accel_pred *=  (1 / (double) NearestPred_count);
		y_accel_pred *=  (1 / (double) NearestPred_count);
	}

	x_accel[0] =  2*motion_pdpy_ratio * x_accel_prey + (1- motion_pdpy_ratio) * x_accel_pred  + wall_accel_x;
	y_accel[0] =  2*motion_pdpy_ratio * y_accel_prey + (1- motion_pdpy_ratio) * y_accel_pred + wall_accel_y;
	q_change[0] = empathy*(emote_pdpy_ratio * q_change_prey + (1 - emote_pdpy_ratio) *q_change_pred);

	x_accel_prey =  0;
	y_accel_prey = 0;
	x_accel_pred =  0;
	y_accel_pred = 0;

	q_change_prey = 0;
	q_change_pred = 0;

	wall_accel_x = 0;
	wall_accel_y = 0;

}

 void finch::drag()
{
    double veloc_mag = x_veloc[0]*x_veloc[0] + y_veloc[0]*y_veloc[0];
	double fear_factor = q_mag - q_mag * adrenaline + adrenaline;
	double A = ALPHA*4*fear_factor*fear_factor;
	x_accel[0] = x_accel[0] + (A - BETA * veloc_mag)*x_veloc[0];
	y_accel[0] = y_accel[0] + (A - BETA * veloc_mag)*y_veloc[0];
	q_change[0] = q_change[0] - q_mag * fear_decay;
    NearestNeighbor_count = 0;
} 

 void finch::ab4_update()
{
    assert(HIST_LENGTH >= 4);
    
    double forward_v_x = x_veloc[0] +
                ( (STEP_SIZE * (1.0/24.0)) * 
                 ((55 * x_accel[0]) -
                  (59 * x_accel[1]) +
                  (37 * x_accel[2]) -
                  (9  * x_accel[3])));
    
    double forward_v_y = y_veloc[0] +
                ( (STEP_SIZE * (1.0/24.0)) * 
                 ((55 * y_accel[0]) -
                  (59 * y_accel[1]) +
                  (37 * y_accel[2]) -
                  (9  * y_accel[3])));

    

    x_coord = x_coord +
                ( (STEP_SIZE * (1.0/24.0)) * 
                  ((55 * forward_v_x) -
                   (59 * x_veloc[0]) +
                   (37 * x_veloc[1]) -
                   (9  * x_veloc[2])));
    
    y_coord = y_coord +
                ( (STEP_SIZE * (1.0/24.0)) *
                  ((55 * forward_v_y) -
                   (59 * y_veloc[0]) +
                   (37 * y_veloc[1]) -
                   (9  * y_veloc[2])));

	q_mag = q_mag +
                ( (STEP_SIZE * (1.0/24.0)) *
                  ((55 * q_change[0]) -
                   (59 * q_change[1]) +
                   (37 * q_change[2]) -
                   (9  * q_change[3])));
    
    //Move history forward.
    
    for(int i = HIST_LENGTH - 1; i > 0; --i){
        
        x_veloc[i] = x_veloc[i-1];
        x_accel[i] = x_accel[i-1];
        y_veloc[i] = y_veloc[i-1];
        y_accel[i] = y_accel[i-1];
		
        q_change[i] = q_change[i-1];

    }
    
    x_veloc[0] = forward_v_x;
    y_veloc[0] = forward_v_y;
    x_accel[0] = 0;
    y_accel[0] = 0;

	q_change[0] = 0;
    
	//std::cout << "\n NOW MY FEAR IS   " << q_mag << "\n";
	if(q_mag < 0 || q_mag > 1)
	{
		q_mag = 1;
		std::cout << "err";
	}
}

void finch::euler_update()
{
    double forward_v_x = x_veloc[0] + (STEP_SIZE * x_accel[0]);
    
    double forward_v_y = y_veloc[0] + (STEP_SIZE * y_accel[0]);
    
	
    x_coord = x_coord +
        (STEP_SIZE * forward_v_x);
    
    y_coord = y_coord +
        (STEP_SIZE * forward_v_y);

    q_mag = (q_mag + (STEP_SIZE * q_change[0]));

    for(int i = HIST_LENGTH - 1; i > 0; --i){
        
        x_veloc[i] = x_veloc[i-1];
        x_accel[i] = x_accel[i-1];
        y_veloc[i] = y_veloc[i-1];
        y_accel[i] = y_accel[i-1];
        
		q_change[i] = q_change[i-1];

    }
    
    x_veloc[0] = forward_v_x;
    y_veloc[0] = forward_v_y;
    x_accel[0] = 0;
    y_accel[0] = 0;
    
	q_change[0] = 0;

	//std::cout << "\n NOW MY FEAR IS   " << q_mag << "\n";
	if(q_mag < 0 || q_mag > 1)
	{
		q_mag = 1;
		std::cout << "err";
	}
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

void finch::add_to_q_change_prey(double q_c){
    
   
        q_change_prey += q_c;
    
}

void finch::add_to_q_change_pred(double q_c){
    
   
        q_change_pred += q_c;
    
}


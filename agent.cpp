#include "agent.h"

//Default Constructor.
agent::agent(){
  //Assign Coordinates
    x_coord = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        x_veloc[i] = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        x_accel[i] = 0;
    
    y_coord = 0;
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
    
    //Assign Type
    agent_type = 0;
    
    //Assign Update Rull
    update = 0; //NULL 
    
    alive = true;
	
}

//Constructor with x,y, and update rule
agent::agent(double x, double y, void (* up)(agent*,agent*) ){
    //Assign Coordinates
    x_coord = x;
    for(int i = 0; i < HIST_LENGTH; i++)
        x_veloc[i] = 0.0;
    for(int i = 0; i < HIST_LENGTH; i++)
        x_accel[i] = 0.0;
    
    y_coord = y;
    for(int i = 0; i < HIST_LENGTH; i++)
        y_veloc[i] = 0.0;
    for(int i = 0; i < HIST_LENGTH; i++)
        y_accel[i] = 0.0;
    
    //Assign Contagion
    q_mag = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        q_change[i] = 0;
    
    //Assign NN
    NearestNeighbor_count = 0;
    
    //Assign Type
    agent_type = 0;
    
    //Assign Update Rull
    update = up; //NULL 
    
    alive = true;
    
}

////Constructor with x,y, and velocities
agent::agent(double x, double y, double v_x[HIST_LENGTH], double v_y[HIST_LENGTH]){
    x_coord = x;
    for(int i = 0; i < HIST_LENGTH; i++)
        x_veloc[i] = v_x[i];
    for(int i = 0; i < HIST_LENGTH; i++)
        x_accel[i] = 0;
    
    y_coord = y;
    for(int i = 0; i < HIST_LENGTH; i++)
        y_veloc[i] = v_y[i];
    for(int i = 0; i < HIST_LENGTH; i++)
        y_accel[i] = 0;
    
    //Assign Contagion
    q_mag = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        q_change[i] = 0;
    
    //Assign NN
    NearestNeighbor_count = 0;
    
    //Assign Type
    agent_type = 0;
    
    //Assign Update Rull
    update = 0; //NULL
    alive = true;
    
}

//Constructor with x,y, velocities, emotion, type, and update rule
agent::agent(double x, double y, double v_x[HIST_LENGTH], double v_y[HIST_LENGTH], 
	     double q, int a_type, void (* up)(agent*,agent*) ){

    //Assign Coordinates
    x_coord = x;
    for(int i = 0; i < HIST_LENGTH; i++)
        x_veloc[i] = v_x[i];
    for(int i = 0; i < HIST_LENGTH; i++)
        x_accel[i] = 0;
    
    y_coord = y;
    for(int i = 0; i < HIST_LENGTH; i++)
        y_veloc[i] = v_y[i];
    for(int i = 0; i < HIST_LENGTH; i++)
        y_accel[i] = 0;
    
    //Assign Contagion
    q_mag = q;
    for(int i = 0; i < HIST_LENGTH; i++)
        q_change[i] = 0;
    
    //Assign NN
    NearestNeighbor_count = 0;
    
    //Assign Type
    agent_type = a_type;
    
    //Assign Update Rull
    update = up; //NULL
    alive = true;
    
}

void agent::ab4_update()
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
    
}

void agent::euler_update()
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

}

void agent::normalize_accel()
{
	if(NearestNeighbor_count != 0)
      {
        x_accel[0] =  (x_accel[0] / (double) NearestNeighbor_count);
		y_accel[0] =  (y_accel[0] / (double) NearestNeighbor_count);
		q_change[0] = (q_change[0] / (double) NearestNeighbor_count);
    }
}

void agent::drag()
{
	//MUST CALL DRAG AFTER ALL NEIGHBOR INTERACTIONS HAVE BEEN CALCULATED INTO X_ACCEL
    double veloc_mag = x_veloc[0]*x_veloc[0] + y_veloc[0]*y_veloc[0];
	double A = ALPHA*4*pow((0.5-0.5*q_mag+q_mag),2);
	x_accel[0] += (A - BETA * veloc_mag)*x_veloc[0];
	y_accel[0] += (A - BETA * veloc_mag)*y_veloc[0];
	q_change[0] += -q_mag/100;
    NearestNeighbor_count = 0;
} 

void agent::kill() {
	double p = (double)rand()/(double)RAND_MAX;
	if (p < PRECISION) {
		alive = false;
	}
}
/*
void agent::move_inside(int proj_x, int proj_y){
	if(!alive){
		return;
	}
	double EPSILON = 0.0001;
	if(proj_x < 0){
		set_x_coord(EPSILON);
	} else if(proj_x > DOMAIN_DIM_1){
		set_x_coord((DOMAIN_DIM_1*CELL_LENGTH) - EPSILON );
	}
	if(proj_y < 0){
		set_y_coord(EPSILON);
	} else if(proj_y > DOMAIN_DIM_2){
		set_y_coord((DOMAIN_DIM_2*CELL_LENGTH) - EPSILON );
	}
	
	
}*/

void agent::iterate_NearestNeighbor(){
    
    NearestNeighbor_count++;
    
}


//Accessor Functions
int agent::cell_num_dim1() {
	if (x_coord < 0) {
		return -1;
	} else {
		return (int) (x_coord)/CELL_LENGTH;
	}
}

int agent::cell_num_dim2() {
	if (y_coord < 0) {
		return -1;
	}else{
	return (int) (y_coord)/CELL_LENGTH;
	}
}

int agent::get_heading()
{
	if(agent_type == 1)
	{
	if(abs(x_veloc[0]) > abs(y_veloc[0]))
	{
		if(x_veloc[0] > 0)
		{
			return 2;
		}
		else
		{
			return 4;
		}
	}
	else
	{
		if(y_veloc[0] > 0)
		{
			return 1;
		}
		else
		{
			return 3;
		}
	}
	}
	else
	{
		return 0;
	}
}

double agent::get_x_coord(){
    
    return x_coord;
    
}

double agent::get_y_coord(){
    
    return y_coord;
    
}

double* agent::get_x_veloc(){
    
    return &x_veloc[0];
    
}

double* agent::get_y_veloc(){
    
    return &y_veloc[0];
    
}

double agent::get_x_veloc_index(int index){
    
    assert(index < HIST_LENGTH && index > -1);
    return x_veloc[index];
    
}

double agent::get_y_veloc_index(int index){
    
    assert(index < HIST_LENGTH && index > -1);
    return y_veloc[index];
    
}

double* agent::get_x_accel(){
    
    return &x_accel[0];
    
}

double* agent::get_y_accel(){
    
    return &y_accel[0];
    
}

double agent::get_x_accel_index(int index){
    
    assert(index < HIST_LENGTH && index > -1);
    return x_accel[index];
    
}

double agent::get_y_accel_index(int index){
    
    assert(index < HIST_LENGTH && index > -1);
    return y_accel[index];
    
}

double agent::get_q_mag(){
    
    return q_mag;
    
}

double* agent::get_q_change(){
    
    return &q_change[0];
    
}

double agent::get_q_change_index(int index)
{
	assert(index < HIST_LENGTH && index > -1);
    return q_change[index];
}

int agent::get_type() {
	
	return agent_type;
}

bool agent::is_alive() {
	
	return alive;
}


//Mutator Functions
 void agent::set_x_coord(double x){
    
     x_coord = x;
    
 }

 void agent::set_y_coord(double y){
    
     y_coord = y;
    
 }

 void agent::set_x_veloc(double v_x){
    
    x_veloc[0] = v_x;
    for(int i = 1; i < HIST_LENGTH; i++)
        x_veloc[i] = 0.0;
    
 }

 void agent::set_y_veloc(double v_y){
    
    y_veloc[0] = v_y;
    for(int i = 1; i < HIST_LENGTH; i++)
        y_veloc[i] = 0.0;
    
 }

void agent::set_x_veloc(double v_x[HIST_LENGTH]){
    for(int i = 0; i < HIST_LENGTH; i++)
        x_veloc[i] = v_x[i];

}

void agent::set_y_veloc(double v_y[HIST_LENGTH]){
    
    for(int i = 0; i < HIST_LENGTH; i++)
        y_veloc[i] = v_y[i];
    
}

void agent::set_x_accel(double new_accel){
    
    x_accel[0] = new_accel;
    
}

void agent::set_y_accel(double new_accel){
    
    y_accel[0] = new_accel;
    
}

void agent::add_to_x_accel(double add_to_accel){
    
    x_accel[0] += add_to_accel;
    
}

void agent::add_to_y_accel(double add_to_accel){
    
    y_accel[0] += add_to_accel;
    
}

void agent::set_q_mag(double q){
    
    q_mag = q;
    
}

void agent::add_to_q_change(double q_c){
    
   
        q_change[0] += q_c;
    
}
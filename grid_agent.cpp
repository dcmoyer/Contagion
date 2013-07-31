#include "grid_agent.h"

//Default Constructor.
grid_agent::grid_agent(double x, double y, int t, double (*p)(double, double, grid_agent*), double (*vb)(double, double, double, double)){
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
    
    //Assign Type
    agent_type = 0;
    
	//It lives!
	alive = true;
	
	potential = p;
	velocity_block = vb;
	
	agent_type = t;
}

void grid_agent::ab4_update()
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

void grid_agent::euler_update()
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

void grid_agent::drag()
{
	//MUST CALL DRAG AFTER ALL NEIGHBOR INTERACTIONS HAVE BEEN CALCULATED INTO X_ACCEL
    double veloc_mag = x_veloc[0]*x_veloc[0] + y_veloc[0]*y_veloc[0];
	double A = ALPHA*4*pow((0.5-0.5*q_mag+q_mag),2);
	x_accel[0] += -x_veloc[0];
	y_accel[0] += -y_veloc[0];
	//q_change[0] += -q_mag/100;
	
}

void grid_agent::kill(){
	
	alive = false;
	
}

double grid_agent::get_x_coord(){
    
    return x_coord;
    
}

double grid_agent::get_y_coord(){
    
    return y_coord;
    
}

double grid_agent::get_x_node_pos(){
	
	return round(x_coord);
	
}
double grid_agent::get_y_node_pos(){
	
	return round(y_coord);
	
}

double* grid_agent::get_x_veloc(){
    
    return &x_veloc[0];
    
}

double* grid_agent::get_y_veloc(){
    
    return &y_veloc[0];
    
}

double grid_agent::get_x_veloc_index(int index){
    
    assert(index < HIST_LENGTH && index > -1);
    return x_veloc[index];
    
}

double grid_agent::get_y_veloc_index(int index){
    
    assert(index < HIST_LENGTH && index > -1);
    return y_veloc[index];
    
}

double* grid_agent::get_x_accel(){
    
    return &x_accel[0];
    
}

double* grid_agent::get_y_accel(){
    
    return &y_accel[0];
    
}

double grid_agent::get_x_accel_index(int index){
    
    assert(index < HIST_LENGTH && index > -1);
    return x_accel[index];
    
}

double grid_agent::get_y_accel_index(int index){
    
    assert(index < HIST_LENGTH && index > -1);
    return y_accel[index];
    
}

double grid_agent::get_q_mag(){
    
    return q_mag;
    
}

double* grid_agent::get_q_change(){
    
    return &q_change[0];
    
}

double grid_agent::get_q_change_index(int index)
{
	assert(index < HIST_LENGTH && index > -1);
    return q_change[index];
}

int grid_agent::get_type() {
	
	return agent_type;
}

bool grid_agent::is_alive(){
	return alive;
}


//Mutator Functions
 void grid_agent::set_x_coord(double x){
    
     x_coord = x;
    
 }

 void grid_agent::set_y_coord(double y){
    
     y_coord = y;
    
 }

 void grid_agent::set_x_veloc(double v_x){
    
    x_veloc[0] = v_x;
    for(int i = 1; i < HIST_LENGTH; i++)
        x_veloc[i] = 0.0;
    
 }

 void grid_agent::set_y_veloc(double v_y){
    
    y_veloc[0] = v_y;
    for(int i = 1; i < HIST_LENGTH; i++)
        y_veloc[i] = 0.0;
    
 }

void grid_agent::set_x_veloc(double v_x[HIST_LENGTH]){
    for(int i = 0; i < HIST_LENGTH; i++)
        x_veloc[i] = v_x[i];

}

void grid_agent::set_y_veloc(double v_y[HIST_LENGTH]){
    
    for(int i = 0; i < HIST_LENGTH; i++)
        y_veloc[i] = v_y[i];
    
}

void grid_agent::set_x_accel(double new_accel){
    
    x_accel[0] = new_accel;
    
}

void grid_agent::set_y_accel(double new_accel){
    
    y_accel[0] = new_accel;
    
}

void grid_agent::add_to_x_accel(double add_to_accel){
    
    x_accel[0] += add_to_accel;
    
}

void grid_agent::add_to_y_accel(double add_to_accel){
    
    y_accel[0] += add_to_accel;
	
}

void grid_agent::set_q_mag(double q){
    
    q_mag = q;
    
}

void grid_agent::add_to_q_change(double q_c){
    
   
        q_change[0] += q_c;
    
}
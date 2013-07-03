/* 

    This is the agent class implemenation for the Contagion Project, UCLA REU 2013.

062413 1341 Created (DM).
062513 1200 Retro Post. Added Imp. for Accessor and Mutator Functions.
062513 1448 Added Z dim. and fixed bugs. Compiles.


*/

#include "agent.h"
#include <cassert>

/*
 Default Constructor.
*/

agent::agent(){
    //Assign Coordinates
    x_coord = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        x_veloc[i] = 0;
    y_coord = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        y_veloc[i] = 0;
    z_coord = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        z_veloc[i] = 0;
    
    //Assign Contagion
    q_mag = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        q_change[i] = 0;
    
    //Assign Forward Values
    forward_v_x = 0;
    forward_v_y = 0;
    forward_v_z = 0;
    forward_q_c = 0;
    
    //Assign NN
    NearestNeighbor_count = 0;
    
    //Assign Type
    agent_type = 'd';
    
    //Assign Update Rull
    update = 0; //NULL 
    
    position_update_flag = 0;
    
}

/*
 Test Constructor. Unused integer.
 */

agent::agent(int TEST){
    //Assign Coordinates
    x_coord = TEST;
    for(int i = 0; i < HIST_LENGTH; i++)
        x_veloc[i] = TEST;
    y_coord = TEST;
    for(int i = 0; i < HIST_LENGTH; i++)
        y_veloc[i] = TEST;
    z_coord = TEST;
    for(int i = 0; i < HIST_LENGTH; i++)
        z_veloc[i] = TEST;
    
    //Assign Contagion
    q_mag = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        q_change[i] = 0;
    
    //Assign Forward Values
    forward_v_x = 0;
    forward_v_y = 0;
    forward_v_z = 0;
    forward_q_c = 0;
    
    //Assign NN
    NearestNeighbor_count = 0;
    
    //Assign Type
    agent_type = 'd';
    
    //Assign Update Rull
    update = 0; //NULL
    position_update_flag = 0;

    
}   

/* Constructor.  Contains arguments for position */

agent::agent(double x, double y){
    //Assign Coordinates
    x_coord = x;
    for(int i = 0; i < HIST_LENGTH; i++)
        x_veloc[i] = 0;
    y_coord = y;
    for(int i = 0; i < HIST_LENGTH; i++)
        y_veloc[i] = 0;
    z_coord = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        z_veloc[i] = 0;
    
    //Assign Contagion
    q_mag = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        q_change[i] = 0;
    
    //Assign Forward Values
    forward_v_x = 0;
    forward_v_y = 0;
    forward_v_z = 0;
    forward_q_c = 0;
    
    //Assign NN
    NearestNeighbor_count = 0;
    
    //Assign Type
    agent_type = 'd';
    
    //Assign Update Rull
    update = 0; //NULL 
    
    position_update_flag = 0;

    
}

/* Constructor.  Contains arguments for position */

agent::agent(double x, double y, double z){
    //Assign Coordinates
    x_coord = x;
    for(int i = 0; i < HIST_LENGTH; i++)
        x_veloc[i] = 0;
    y_coord = y;
    for(int i = 0; i < HIST_LENGTH; i++)
        y_veloc[i] = 0;
    z_coord = z;
    for(int i = 0; i < HIST_LENGTH; i++)
        z_veloc[i] = 0;
    
    //Assign Contagion
    q_mag = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        q_change[i] = 0;
    
    //Assign Forward Values
    forward_v_x = 0;
    forward_v_y = 0;
    forward_v_z = 0;
    forward_q_c = 0;
    
    //Assign NN
    NearestNeighbor_count = 0;
    
    //Assign Type
    agent_type = 'd';
    
    //Assign Update Rull
    update = 0; //NULL 
    position_update_flag = 0;

    
}


/*
Constructor. Contains arguements for position and velocity. 
*/

agent::agent(double x, double y, double v_x[HIST_LENGTH], double v_y[HIST_LENGTH]){
    x_coord = x;
    for(int i = 0; i < HIST_LENGTH; i++)
        x_veloc[i] = v_x[i];
    y_coord = y;
    for(int i = 0; i < HIST_LENGTH; i++)
        y_veloc[i] = v_y[i];
    z_coord = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        z_veloc[i] = 0;
    
    //Assign Contagion
    q_mag = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        q_change[i] = 0;
    
    //Assign Forward Values
    forward_v_x = 0;
    forward_v_y = 0;
    forward_v_z = 0;
    forward_q_c = 0;
    
    //Assign NN
    NearestNeighbor_count = 0;
    
    //Assign Type
    agent_type = 'd';
    
    //Assign Update Rull
    update = 0; //NULL
    
    position_update_flag = 0;

    
}

/*
Constructor. Contains arguements for position and velocity. 
*/

agent::agent(double x, double y, double z, 
	     double v_x[HIST_LENGTH], double v_y[HIST_LENGTH], double v_z[HIST_LENGTH])
{
    x_coord = x;
    for(int i = 0; i < HIST_LENGTH; i++)
        x_veloc[i] = v_x[i];
    y_coord = y;
    for(int i = 0; i < HIST_LENGTH; i++)
        y_veloc[i] = v_y[i];
    z_coord = z;
    for(int i = 0; i < HIST_LENGTH; i++)
        z_veloc[i] = v_z[i];
    
    //Assign Contagion
    q_mag = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        q_change[i] = 0;
    
    //Assign Forward Values
    forward_v_x = 0;
    forward_v_y = 0;
    forward_v_z = 0;
    forward_q_c = 0;
    
    //Assign NN
    NearestNeighbor_count = 0;
    
    //Assign Type
    agent_type = 'd';
    
    //Assign Update Rull
    update = 0; //NULL
    
    position_update_flag = 0;
    
}

/* 
Constructor. Contains arguments for position, velocity, and contagion.
*/

agent::agent(double x, double y, double v_x[HIST_LENGTH], double v_y[HIST_LENGTH], 
	     double q, char a_type, void (* up)(agent*,agent*) ){

    //Assign Coordinates
    x_coord = x;
    for(int i = 0; i < HIST_LENGTH; i++)
        x_veloc[i] = v_x[i];
    y_coord = y;
    for(int i = 0; i < HIST_LENGTH; i++)
        y_veloc[i] = v_y[i];
    z_coord = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        z_veloc[i] = 0;
    
    //Assign Contagion
    q_mag = q;
    for(int i = 0; i < HIST_LENGTH; i++)
        q_change[i] = 0;
    
    //Assign Forward Values
    forward_v_x = 0;
    forward_v_y = 0;
    forward_v_z = 0;
    forward_q_c = 0;
    
    //Assign NN
    NearestNeighbor_count = 0;
    
    //Assign Type
    agent_type = 'd';
    
    //Assign Update Rull
    update = up; //NULL
    
    position_update_flag = 0;

    
}

agent::agent(double x, double y, double z, double v_x[HIST_LENGTH], double v_y[HIST_LENGTH], double v_z[HIST_LENGTH], double q, char a_type, void (* up)(agent*,agent*) ){

     //Assign Coordinates
     x_coord = x;
     for(int i = 0; i < HIST_LENGTH; i++)
       x_veloc[i] = v_x[HIST_LENGTH];
     y_coord = y;
     for(int i = 0; i < HIST_LENGTH; i++)
         y_veloc[i] = v_y[HIST_LENGTH];
     z_coord = z;
     for(int i = 0; i < HIST_LENGTH; i++)
         z_veloc[i] = v_z[HIST_LENGTH];
    
     //Assign Contagion
     q_mag = q;
     for(int i = 0; i < HIST_LENGTH; i++)
         q_change[i] = 0;
    
     //Assign Forward Values
     forward_v_x = 0;
     forward_v_y = 0;
     forward_v_z = 0;
     forward_q_c = 0;
    
     //Assign NN
     NearestNeighbor_count = 0;
    
     //Assign Type
     agent_type = 'd';
    
     //Assign Update Rull
     update = 0; //NULL
    
    position_update_flag = 0;

    
 }


void agent::ab4_update()
{
    assert(HIST_LENGTH == 3);
    
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
    
    //Move history forward.
    x_veloc[2] = x_veloc[1];
    y_veloc[2] = y_veloc[1];
    
    x_veloc[1] = x_veloc[0];
    y_veloc[1] = y_veloc[0];
    
    x_veloc[0] = forward_v_x;
    x_veloc[0] = forward_v_y;
    
    forward_v_x = 0;
    forward_v_y = 0;
    
    /*
    double vx [HIST_LENGTH];
    double vy [HIST_LENGTH];
    double vz [HIST_LENGTH];
    
    double* px = get_x_veloc();
    for (int i = 0; i < HIST_LENGTH; i++)
    {
        vx[i] = *(px + i);
    }
    
    double* py = get_y_veloc();
    for (int i = 0; i < HIST_LENGTH; i++)
    {
        vy[i] = *(py + i);
    }
    
    double* pz = get_z_veloc();
    for (int i = 0; i < HIST_LENGTH; i++)
    {
        vz[i] = *(pz + i);
    }
    
    
    double new_x = get_x_coord() + STEP_SIZE / 24 * (55 * vx[0] - 59 * vx[1] + 37 * vx[2] - 9 * vx[3]);
    double new_y = get_y_coord() + STEP_SIZE / 24 * (55 * vy[0] - 59 * vy[1] + 37 * vy[2] - 9 * vy[3]);
    double new_z = get_z_coord() + STEP_SIZE / 24 * (55 * vz[0] - 59 * vz[1] + 37 * vz[2] - 9 * vz[3]);
    
    set_x_coord(new_x);
    set_y_coord(new_y);
    set_z_coord(new_z);*/
}

void agent::euler_update()
{
    
    x_coord = x_coord +
        (STEP_SIZE * forward_v_x);
    
    y_coord = y_coord +
        (STEP_SIZE * forward_v_y);
    
    x_veloc[2] = x_veloc[1];
    y_veloc[2] = y_veloc[1];
    
    x_veloc[1] = x_veloc[0];
    y_veloc[1] = y_veloc[0];
    
    x_veloc[0] = forward_v_x;
    x_veloc[0] = forward_v_y;
    
    forward_v_x = 0;
    forward_v_y = 0;
    
    /*
    
    double* px = get_x_veloc();
    double* py = get_y_veloc();
    double* pz = get_z_veloc();
    
    double new_x = get_x_coord() + STEP_SIZE  * (*px);
    double new_y = get_y_coord() + STEP_SIZE  * (*py);
    double new_z = get_z_coord() + STEP_SIZE  * (*pz);
    
    set_x_coord(new_x);
    set_y_coord(new_y);
    set_z_coord(new_z);
     */
}

void agent::drag(){
    
    forward_v_x = /*(forward_v_x / (double) NearestNeighbor_count) +*/ x_veloc[0] - (DRAG * x_veloc[0]);
    
}

 /* 
 
  Mutator Functions
 
  */
 void agent::set_x_coord(double x){
    
     x_coord = x;
    
 }

 void agent::set_y_coord(double y){
    
     y_coord = y;
    
 }

 void agent::set_z_coord(double z){
    
     z_coord = z;
    
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

 void agent::set_z_veloc(double v_z){
    
    z_veloc[0] = v_z;
    for(int i = 1; i < HIST_LENGTH; i++)
        z_veloc[i] = 0.0;
    
 }

 void agent::set_x_veloc(double v_x[HIST_LENGTH]){
    for(int i = 0; i < HIST_LENGTH; i++)
        x_veloc[i] = v_x[i];

}

void agent::set_y_veloc(double v_y[HIST_LENGTH]){
    
    for(int i = 0; i < HIST_LENGTH; i++)
        y_veloc[i] = v_y[i];
    
}

void agent::set_z_veloc(double v_z[HIST_LENGTH]){
    
    for(int i = 0; i < HIST_LENGTH; i++)
        z_veloc[i] = v_z[i];
    
}

void agent::set_q_mag(double q){
    
    q_mag = q;
    
}

void agent::set_q_change(double q_c[HIST_LENGTH]){
    
    for(int i = 0; i < HIST_LENGTH; i++)
        q_change[i] = q_c[i];
    
}

void agent::set_forward_v_x(double for_v_x){
 
    forward_v_x = for_v_x;
    
}

void agent::set_forward_v_y(double for_v_y){
    
    forward_v_y = for_v_y;
    
}

void agent::set_forward_v_z(double for_v_z){
    
    forward_v_z = for_v_z;
    
}

void agent::set_forward_q_c(double for_q_c){
    
    forward_q_c = for_q_c;
    
}

/*
 
 Accessor Functions
 
 */
double agent::get_x_coord(){
    
    return x_coord;
    
}

double agent::get_y_coord(){
    
    return y_coord;
    
}

double agent::get_z_coord(){
    
    return z_coord;
    
}

double* agent::get_x_veloc(){
    
    return &x_veloc[0];
    
}

double* agent::get_y_veloc(){
    
    return &y_veloc[0];
    
}

double* agent::get_z_veloc(){
    
    return &z_veloc[0];
    
}

double agent::get_x_veloc_index(int index){
    
    assert(index < HIST_LENGTH && index > -1);
    return x_veloc[index];
    
}

double agent::get_y_veloc_index(int index){
    
    assert(index < HIST_LENGTH && index > -1);
    return y_veloc[index];
    
}

double agent::get_z_veloc_index(int index){
    
    assert(index < HIST_LENGTH && index > -1);
    return z_veloc[index];
    
}

double agent::get_q_mag(){
    
    return q_mag;
    
}

double* agent::get_q_change(){
    
    return &q_change[0];
    
}

double agent::get_forward_v_x(){
    
    return forward_v_x;
    
}

double agent::get_forward_v_y(){
    
    return forward_v_y;
    
}

double agent::get_forward_v_z(){
    
    return forward_v_z;
    
}

double agent::get_forward_q_c(){
    
    return forward_q_c;
    
}

int agent::cell_num_dim1() {
	
	return (int) (x_coord)/CELL_LENGTH;
}

int agent::cell_num_dim2() {

	return (int) (y_coord)/CELL_LENGTH;
}


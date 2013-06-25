/* 

    This is the agent class implemenation for the Contagion Project, UCLA REU 2013.

062413 1341 Created (DM).
062513 1200 Retro Post. Added Imp. for Accessor and Mutator Functions.

*/

#include "agent.h"

/*
 
 Default Constructor.
 
 */
agent::agent(){
    x_coord = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        x_veloc[i] = 0;
    y_coord = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        y_veloc[i] = 0;
    q_mag = 0;
}

/*
 
 Test Constructor. Unused integer.
 
 */
agent::agent(int TEST){
    x_coord = TEST;
    for(int i = 0; i < HIST_LENGTH; i++)
        x_veloc[i] = TEST;
    y_coord = TEST;
    for(int i = 0; i < HIST_LENGTH; i++)
        y_veloc[i] = TEST;
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
    q_mag = 0;
    for(int i = 0; i < HIST_LENGTH; i++)
        q_change[i] = 0;
}

/*
 
 Constructor. Contains arguments for position, velocity, and contagion.
 
 */
agent::agent(double x, double y, double v_x[HIST_LENGTH], double v_y[HIST_LENGTH], double q, double q_c[HIST_LENGTH]){
    x_coord = x;
    for(int i = 0; i < HIST_LENGTH; i++)
        x_veloc[i] = v_x[i];
    y_coord = y;
    for(int i = 0; i < HIST_LENGTH; i++)
        y_veloc[i] = v_y[i];
    q_mag = q;
    for(int i = 0; i < HIST_LENGTH; i++)
        q_change[i] = q_c[i];
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
void agent::set_x_veloc(double v_x[HIST_LENGTH]){
    
    for(int i = 0; i < HIST_LENGTH; i++)
        x_veloc[i] = v_x[i];

}
void agent::set_y_veloc(double v_y[HIST_LENGTH]){
    
    for(int i = 0; i < HIST_LENGTH; i++)
        y_veloc[i] = v_y[i];
    
}
void agent::set_q_mag(double q){
    
    q_mag = q;
    
}
void agent::set_q_change(double q_c[HIST_LENGTH]){
    
    for(int i = 0; i < HIST_LENGTH; i++)
        q_change[i] = q_c[i];
    
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
double* agent::get_x_veloc(){
    
    return &x_veloc[0];
    
}
double* agent::get_y_veloc(){
    
    return &y_veloc[0];
    
}
double agent::get_q_mag(){
    
    return q_mag;
    
}

double* agent::get_q_change(){
    
    return &q_change[0];
    
}


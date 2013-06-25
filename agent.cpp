/* 

    This is the agent class implemenation for the Contagion Project, UCLA REU 2013.

062413 1341 Created (DM).

*/

#include "agent.h"

/*
 
 Default Constructor.
 
 */
agent::agent(){
    x_coord = 0;
    x_veloc = 0;
    y_coord = 0;
    y_veloc = 0;
    q_mag = 0;
}

/*
 
 Test Constructor. Unused integer.
 
 */
agent::agent(int TEST){
    x_coord = TEST;
    x_veloc = TEST;
    y_coord = TEST;
    y_veloc = TEST;
}   

/*
 
Constructor. Contains arguements for position and velocity. 
 
 */
agent::agent(double x, double y, double v_x, double v_y){
    x_coord = x;
    x_veloc = v_x;
    y_coord = y;
    y_coord = v_y;
    q_mag = 0;
}

/*
 
 Constructor. Contains arguments for position, velocity, and contagion.
 
 */
agent::agent(double x, double y, double v_x, double v_y, double q){
    x_coord = x;
    y_coord = y;
    x_veloc = v_x;
    y_veloc = v_y;
    q_mag = q;
}

/* 
 
 Mutator Functions
 
 */
void set_x_coord(double x){
    
    x_coord = x;
    
}
void set_y_coord(double y){
    
    y_coord = y;
    
}
void set_x_veloc(double v_x[HIST_LENGTH]){
    
    for(int i  = 0, i < HIST_LENGTH, i++)
        x_veloc[i] = v_x[i];

}
void set_y_veloc(double v_y[HIST_LENGTH]){
    
    for(int i  = 0, i < HIST_LENGTH, i++)
        y_veloc[i] = v_y[i];
    
}
void set_q_mag(double q){
    
    q_mag = q;
    
}
void set_q_change(double q_c[HIST_LENGTH]){
    
    for(int i  = 0, i < HIST_LENGTH, i++)
        q_change[i] = q_c[i];
    
}

/*
 
 Accessor Functions
 
 */
double get_x_coord(){
    
    return x_coord;
    
}
double get_y_coord(){
    
    return y_coord;
    
}
double* get_x_veloc(){
    
    return &x_veloc;
    
}
double* get_y_veloc(){
    
    return &y_veloc;
    
}
double get_q_mag(){
    
    return q_mag;
    
}

double* get_q_change(){
    
    return &q_change;
    
}

#endif


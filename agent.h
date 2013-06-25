/*

This is the agent class for the Contagion Project, UCLA REU 2013.

062413 1153 Created. (DM)
062513 0957 Added accessor functions and second constructor.
062513 1200 Retro Post. Added History Length.
 
*/

#ifndef AGENT_H
#define AGENT_H

#include "constants.h"

class agent{
//private: //THIS IS BAD PRACTICE. WILL CHANGE LATER? Sorry, don't do at home. (DM)
public:
    double x_coord;
    double x_veloc[HIST_LENGTH];
    double y_coord;
    double y_veloc[HIST_LENGTH];
    double q_mag;
    double q_change[HIST_LENGTH];
//#ifdef 3D
//  double z_coord;
//  double z_veloc;
//#endif

//public:

    agent();
    agent(int TEST);
    agent(double x, double y, double v_x, double v_y);
    agent(double x, double y, double v_x, double v_y, double q);
    
    //Mutator Functions:
    void set_x_coord(double x);
    void set_y_coord(double y);
    void set_x_veloc(double v_x[HIST_LENGTH]);
    void set_y_veloc(double v_y[HIST_LENGTH]);
    void set_q_mag(double q);
    void set_q_change(double q_c[HIST_LENGTH]);
    
    //Accessor Functions:
    double get_x_coord();
    double get_y_coord();
    double* get_x_veloc();//See Note
    double* get_y_veloc();//See Note
    double get_q_mag();
    double* get_q_change();//See Note
    /*
     NOTE: Because an array cannot be returned, a double pointer is returned instead.
     */
};

#endif

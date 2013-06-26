/*

This is the agent class for the Contagion Project, UCLA REU 2013.

062413 1153 Created. (DM)
062513 0957 Added accessor functions and second constructor.
062513 1200 Retro Post. Added History Length.
062513 1448 Added Z dim. and fixed bugs. Compiles.
 
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
    double z_coord;
    double z_veloc[HIST_LENGTH];
    double q_mag;
    double q_change[HIST_LENGTH];
    
    double forward_v_x;
    double forward_v_y;
    double forward_v_z;
    double forward_q_c;
    double NearestNeighbor_count;
    
    /*
     agent_type is a character defining which type of agent this is:
        d - default
     
     */
    char agent_type;
    
    double (* update)(agent*, agent*);

//public:

    agent();
    agent(int TEST);
    agent(double x, double y, double v_x[HIST_LENGTH], double v_y[HIST_LENGTH]);
    agent(double x, double y, double z, double v_x[HIST_LENGTH], double v_y[HIST_LENGTH], double v_z[HIST_LENGTH], double q, double q_c[HIST_LENGTH], char a_type, double (* up)(agent*,agent*) );
    
    //Mutator Functions:
    void set_x_coord(double x);
    void set_y_coord(double y);
    void set_z_coord(double z);
    void set_x_veloc(double v_x[HIST_LENGTH]);
    void set_y_veloc(double v_y[HIST_LENGTH]);
    void set_z_veloc(double v_z[HIST_LENGTH]);
    void set_q_mag(double q);
    void set_q_change(double q_c[HIST_LENGTH]);
    
    void set_forward_v_x(double for_v_x);
    void set_forward_v_y(double for_v_y);
    void set_forward_v_z(double for_v_z);
    void set_forward_q_c(double for_q_c);
    
    //Accessor Functions:
    double get_x_coord();
    double get_y_coord();
    double get_z_coord();
    double* get_x_veloc();//See Note
    double* get_y_veloc();//See Note
    double* get_z_veloc();//See Note
    double get_x_veloc_index(int index);
    double get_y_veloc_index(int index);
    double get_z_veloc_index(int index);
    
    double get_q_mag();
    double* get_q_change();//See Note
    double get_q_change_index(int index);
    /*
     NOTE: Because an array cannot be returned, a double pointer is returned instead.
     */
    
    double get_forward_v_x();
    double get_forward_v_y();
    double get_forward_v_z();
    double get_forward_q_c();
    
};

#endif

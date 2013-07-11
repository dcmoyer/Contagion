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
    double x_accel[HIST_LENGTH];
    double y_coord;
    double y_veloc[HIST_LENGTH];
    double y_accel[HIST_LENGTH];
    double z_coord;
    double z_veloc[HIST_LENGTH];
    double z_accel[HIST_LENGTH];
    double q_mag;
    double q_change[HIST_LENGTH];
    
    double NearestNeighbor_count;
    bool alive;

    bool position_update_flag;
    
    /*
     agent_type is a character defining which type of agent this is:
        0 - default
		1- predator
     */
    char agent_type;
    
    void (* update)(agent*, agent*);
    
//public:

    agent();
    agent(int TEST);
    agent(double x, double y);
    agent(double x, double y, double z);
    agent(double x, double y, void (* up)(agent*,agent*));
    agent(double x, double y, double z, void (* up)(agent*,agent*));
    agent(double x, double y, double v_x[HIST_LENGTH], double v_y[HIST_LENGTH]);
    agent(double x, double y, double z, 
	  double v_x[HIST_LENGTH], double v_y[HIST_LENGTH], double v_z[HIST_LENGTH]);
    agent(double x, double y, double v_x[HIST_LENGTH], double v_y[HIST_LENGTH], 
	  double q, char a_type, void (* up)(agent*,agent*) );
    agent(double x, double y, double z, 
	  double v_x[HIST_LENGTH], double v_y[HIST_LENGTH], double v_z[HIST_LENGTH], 
	  double q, char a_type, void (* up)(agent*,agent*) );
	  
    //Mutator Functions:
    void set_x_coord(double x);
    void set_y_coord(double y);
    void set_z_coord(double z);
    void set_x_veloc(double v_x);
    void set_y_veloc(double v_y);
    void set_z_veloc(double v_z);
    
    void set_x_accel(double new_accel);
    void set_y_accel(double new_accel);
    void set_z_accel(double new_accel);
    
    void add_to_x_accel(double add_to_accel);
    void add_to_y_accel(double add_to_accel);
    void add_to_z_accel(double add_to_accel);
    
    void set_x_veloc(double v_x[HIST_LENGTH]);
    void set_y_veloc(double v_y[HIST_LENGTH]);
    void set_z_veloc(double v_z[HIST_LENGTH]);
    void set_q_mag(double q);
    void set_q_change(double q_c[HIST_LENGTH]);
	void set_q_change_0(double q_c);
    
    //Accessor Functions:
    double get_x_coord();
    double get_y_coord();
    double get_z_coord();
    double* get_x_veloc();//See Note
    double* get_y_veloc();//See Note
    double* get_z_veloc();//See Note
    
    double* get_x_accel();//See Note
    double* get_y_accel();//See Note
    double* get_z_accel();//See Note
    
    double get_x_veloc_index(int index);
    double get_y_veloc_index(int index);
    double get_z_veloc_index(int index);
    
    double get_x_accel_index(int index);
    double get_y_accel_index(int index);
    double get_z_accel_index(int index);
    
    double get_q_mag();
    double* get_q_change();//See Note
    double get_q_change_index(int index);
    
    void iterate_NearestNeighbor();
    /*
     NOTE: Because an array cannot be returned, a double pointer is returned instead.
     */
    
	void ab4_update();
	void euler_update();
    virtual void normalize_accel();
	virtual void drag(); 

    
    int cell_num_dim1();
    int cell_num_dim2();
    char get_type();
    bool is_alive();
    void kill();
};

#endif

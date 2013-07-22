#ifndef AGENT_H
#define AGENT_H

#include "constants.h"
#include <cassert>
#include <cmath>
#include <cstdlib>



class agent{

public:
//variables
    double x_coord;
    double x_veloc[HIST_LENGTH];
    double x_accel[HIST_LENGTH];
    double y_coord;
    double y_veloc[HIST_LENGTH];
    double y_accel[HIST_LENGTH];
    double q_mag;
    double q_change[HIST_LENGTH];
    double NearestNeighbor_count;
    int agent_type; //default = 0; predator = 1;
    void (* update)(agent*, agent*);
    bool alive;

//functions:

    agent();
    agent(double x, double y, void (* up)(agent*,agent*));
    agent(double x, double y, double v_x[HIST_LENGTH], double v_y[HIST_LENGTH]);
    agent(double x, double y, double v_x[HIST_LENGTH], double v_y[HIST_LENGTH], 
	  double q, int a_type, void (* up)(agent*,agent*) );

	virtual void ab4_update();
	virtual void euler_update();
    virtual void normalize_accel();
	virtual void drag(); 

	void kill();
	void die();
	void move_inside(int proj_x, int proj_y);
	void iterate_NearestNeighbor();

	//Accessor Functions:
	int cell_num_dim1();
    int cell_num_dim2();
	int get_heading();

    double get_x_coord();
    double get_y_coord();
   
    double* get_x_veloc();//See Note
    double* get_y_veloc();//See Note
    double get_x_veloc_index(int index);
    double get_y_veloc_index(int index);

	double* get_x_accel();//See Note
    double* get_y_accel();//See Note
    
    double get_x_accel_index(int index);
    double get_y_accel_index(int index);
    
    double get_q_mag();
    double* get_q_change();//See Note
    double get_q_change_index(int index);

	int get_type();
	bool is_alive();

    //Mutator Functions:
    void set_x_coord(double x);
    void set_y_coord(double y);
    
    void set_x_veloc(double v_x);
    void set_y_veloc(double v_y);
    
    void set_x_veloc(double v_x[HIST_LENGTH]);
    void set_y_veloc(double v_y[HIST_LENGTH]);
   
    void set_x_accel(double new_accel);
    void set_y_accel(double new_accel);
    
    void add_to_x_accel(double add_to_accel);
    void add_to_y_accel(double add_to_accel);
   
    void set_q_mag(double q);

	void add_to_q_change(double q_c);

};

#endif

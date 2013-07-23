#ifndef FINCH_H
#define FINCH_H

#include "constants.h"
#include "agent.h"
#include <cmath>
#include <cassert> 
#include <cstdlib>
#include <iostream>

class finch : public agent {
private:
        
public:
    double NearestPred_count;
	double q_change_prey;
	double q_change_pred;
	double x_accel_pred;
	double y_accel_pred;
	
	double x_accel_prey;
	double y_accel_prey;


	unsigned char params[7];
	double gamma;
	double adrenaline;
	double fear_decay;
	double empathy;
	double emote_pdpy_ratio;
	double motion_pdpy_ratio;
	double attr_align_ratio;

	finch(double x, double y, void (* up)(agent*,agent*));
	finch(double x, double y, void (* up)(agent*,agent*), unsigned char genes[7]);
	
	virtual void normalize_accel();
	virtual void drag();
	virtual void ab4_update();
	virtual void euler_update();

	virtual void print_genome();
	void iterate_NearestPred();

	void add_to_x_accel_prey(double add_to_accel);
    void add_to_y_accel_prey(double add_to_accel);
	void add_to_x_accel_pred(double add_to_accel);
    void add_to_y_accel_pred(double add_to_accel);

	void add_to_q_change_prey(double q_c);
	void add_to_q_change_pred(double q_c);
};
#endif 

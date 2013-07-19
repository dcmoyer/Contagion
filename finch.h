#ifndef FINCH_H
#define FINCH_H

#include "constants.h"
#include "agent.h"
#include <cmath>
#include <cassert> 
#include <cstdlib>

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

	double gamma;
	double v_align_mag;
	double pred_repel;
	double py_pd_kinetic;
	double py_pd_emote;
	double scs;
	double decay;
	
	finch(double x, double y, void (* up)(agent*,agent*));
	
	virtual void normalize_accel();
	virtual void drag();

	
	void iterate_NearestPred();

	void add_to_x_accel_prey(double add_to_accel);
    void add_to_y_accel_prey(double add_to_accel);
	void add_to_x_accel_pred(double add_to_accel);
    void add_to_y_accel_pred(double add_to_accel);
};
#endif 

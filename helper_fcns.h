#ifndef HELPER_FCNS
#define HELPER_FCNS

#include "constants.h"
#include "static_agent.h"
#include "grid_agent.h"
#include <cmath>

double fire_potential(double dx, double dy, static_agent* target);
double exit_potential(double dx, double dy, static_agent* target);
double wall_potential(double dx, double dy, static_agent* target);


//basic attraction, repulsion, alignment model
/*void prey(agent* me, agent* you);
void predator_model(agent* me, agent* you);
void swarm1(agent* me, agent* you);
void swarm1_fear(agent* me, agent* you);
void swarm_attract(agent* me, agent* you);
void go_left_test(agent* me, agent* you);
void predator_2012( agent* me, agent* you);
void prey_2012_nofear(agent* me, agent* you);
void prey_2012_fear(agent* me, agent* you);
void wall_interaction(agent* me_fake, agent* you);
void finch1(agent* me_cast, agent* you);
void velocity_wall_interaction(agent* me_fake, agent* you);*/
#endif

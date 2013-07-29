#ifndef HELPER_FCNS
#define HELPER_FCNS

#include "constants.h"
#include "agent.h"
#include "predator.h"
#include "finch.h"
#include "wall.h"
#include <cmath>

extern double h_gamma_r[256][76];
extern double exp_hund[76];
extern double exp_half[76];

//basic attraction, repulsion, alignment model
void prey(agent* me, agent* you);
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
void velocity_wall_interaction(agent* me_fake, agent* you);
#endif

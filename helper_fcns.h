#ifndef HELPER_FCNS
#define HELPER_FCNS

#include "constants.h"
#include "agent.h"

//basic attraction, repulsion, alignment model
void prey(agent* me, agent* you);
void predator(agent* me, agent* you);
void swarm1(agent* me, agent* you);
void swarm_attract(agent* me, agent* you);
void go_left_test(agent* me, agent* you);
#endif

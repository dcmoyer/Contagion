#ifndef HELPER_FCNS
#define HELPER_FCNS

#include "constants.h"
#include "agent.h"



//calculates next position for agent based on its current and previous velocities
void ab4_update(agent smith);

// used for the first 4 iterations when there are not enough data points yet to use ab4
void euler_update(agent smith);
#endif
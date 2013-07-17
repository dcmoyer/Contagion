/*

This is a header for global constants for the Contagion Project, UCLA REU 2013.

062413 1447 Created (DM).
062513 1200 Retro post. Added HIST_LENGTH.
 

*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define NUM_OF_AGENTS   2
#define DOMAIN_DIM_1    1
#define DOMAIN_DIM_2    1
#define DOMAIN_DIM_3    0
#define CELL_LENGTH   75
#define STEP_SIZE 0.005
#define HIST_LENGTH 4


//strengths and lengths of attraction and repulsion
//C_R > C_A
#define C_A 20.0
#define C_R 50.0
//L_R < L_A
#define L_A 100.0
#define L_R 2.0

#define c1 C_R/C_A
#define l1 L_R/L_A


//self-propulsion and friction
#define ALPHA .07
#define BETA  .05  
#define alpha_1 ALPHA*BETA*L_A*L_A



//constants for alignment model
#define SIGMA 1
#define GAMMA .45
#define KAPPA 0.5

//2012 Predator Speed
#define PRED_2012_SP .1
//Probability of kill
#define PRECISION .5

//Wall Power
#define WALL_PWR 50

#endif

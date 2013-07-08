/*

This is a header for global constants for the Contagion Project, UCLA REU 2013.

062413 1447 Created (DM).
062513 1200 Retro post. Added HIST_LENGTH.
 

*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define NUM_OF_AGENTS   2
#define DOMAIN_DIM_1    2
#define DOMAIN_DIM_2    2
#define DOMAIN_DIM_3    0
#define CELL_LENGTH   60
#define STEP_SIZE 0.001
#define HIST_LENGTH 4


//strengths and lengths of attraction and repulsion
//C_R > C_A
#define C_A 20
#define C_R 50
//L_R < L_A
#define L_A 100
#define L_R 20

//self-propulsion and friction
#define ALPHA .07
#define BETA  .05  

//constants for alignment model
#define SIGMA 1
#define GAMMA .45
#define KAPPA 0


#endif

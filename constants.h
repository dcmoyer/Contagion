/*

This is a header for global constants for the Contagion Project, UCLA REU 2013.

062413 1447 Created (DM).
062513 1200 Retro post. Added HIST_LENGTH.
 

*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define NUM_OF_AGENTS   2
#define DOMAIN_DIM_1    2
#define DOMAIN_DIM_2    3
#define DOMAIN_DIM_3    0
#define CELL_LENGTH   60
#define STEP_SIZE 0.0001
#define HIST_LENGTH 4


//strengths and lengths of attraction and repulsion
//C_R > C_A
#define C_A 25
#define C_R 40
//L_R < L_A
#define L_A 100
#define L_R 15

#define DRAG        -1

//constants for alignment model
#define SIGMA 1
#define GAMMA .45
#define KAPPA 1


#endif

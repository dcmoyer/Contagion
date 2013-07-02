/*

This is a header for global constants for the Contagion Project, UCLA REU 2013.

062413 1447 Created (DM).
062513 1200 Retro post. Added HIST_LENGTH.
 

*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define NUM_OF_AGENTS   2
#define DOMAIN_DIM_1    2
#define DOMAIN_DIM_2    1
#define DOMAIN_DIM_3    0
#define CELL_LENGTH   60
#define STEP_SIZE .1
#define HIST_LENGTH 1


//strengths and lengths of attraction and repulsion
#define C_A 2
#define C_R 3
#define L_A 3
#define L_R 2

#define DRAG        -1

//constants for alignment model
#define SIGMA 1
#define GAMMA .45
#define KAPPA 1


#endif

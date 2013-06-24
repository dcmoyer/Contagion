/* 

    This is the agent class implemenation for the Contagion Project, UCLA REU 2013.

062413 1341 Created (DM).

*/


#include "agent.h"


agent::agent(){
    x_coord = 0;
    x_veloc = 0;
    y_coord = 0;
    y_veloc = 0;
    q_mag = 0;
}

agent::agent(int TEST){
    x_coord = 1;
    x_veloc = 1;
    y_coord = 1;
    y_veloc = 1;
}   

agent::agent(double x, double y, double v_x, double v_y){
    x_coord = x;
    x_veloc = v_x;
    y_coord = y;
    y_coord = v_y;
    q_mag = 0;
}

#endif


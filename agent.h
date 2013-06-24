/*

This is the agent class for the Contagion Project, UCLA REU 2013.

062413 1153 Created. (DM)

*/

#ifndef AGENT_H
#define AGENT_H

include:

class agent{
//private:
public:
    double x_coord;
    double x_veloc;
    double y_coord;
    double y_veloc;
    double q_mag;
//#ifdef 3D
//  double z_coord;
//  double z_veloc;
//#endif

//public:

    agent();
    agent(int TEST);
    agent(double x, double y, double v_x, double v_y);

};

#endif

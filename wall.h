#ifndef WALL_H
#define WALL_H

#include "constants.h"
#include "agent.h"
#include <cmath>

class wall : public agent {
	//private:
        
public:
	
    wall(double center_x, double center_y, double n_x, double n_y, double len,  void (* up)(agent*,agent*));
    virtual ~wall(){;}
	virtual void drag();
	
	double normal_x;
	double normal_y;
	double length; //The Length of a wall is not guarenteed effective past the length of a cell =( 
	
};
#endif 

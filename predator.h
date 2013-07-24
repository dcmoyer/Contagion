#ifndef PREDATOR_H
#define PREDATOR_H

#include "constants.h"
#include "agent.h"

class predator : public agent {
private:
        
public:
    predator(double x, double y, void (* up)(agent*,agent*));
    virtual ~predator(){;}
	virtual void drag();
    
    double get_running_r();
    double running_r;
	

};
#endif 

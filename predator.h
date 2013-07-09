#ifndef PREDATOR_H
#define PREDATOR_H

#include "constants.h"
#include "agent.h"

class predator : public agent {
private:
    double running_r;
    
public:
  predator(double x, double y, void (* up)(agent*,agent*));
};
#endif 

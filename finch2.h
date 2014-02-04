#ifndef FINCH2_H
#define FINCH2_H

#include "constants.h"
#include "finch.h"

class finch2 : public finch {
private:
    
public:
    finch2(double x, double y, void (* up)(agent*,agent*), void (* util_up)(double , double , double , double, finch2* ));
	finch2(double x, double y, void (* up)(agent*,agent*), void (* util_up)(double , double , double , double, finch2* ), unsigned char genes[9]);
    
    void add_to_util(double u){util += u;}
    
    double util;
    void (* util_update) (double , double , double , double, finch2* );
    // Update of util occurs in the update function in helper_fcns.cpp
};

#endif
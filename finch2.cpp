#include "finch2.h"


finch2::finch2(double x, double y, void (* up)(agent*,agent*), void (* util_up)(double , double , double , double, finch2* )) : finch(x,y,up){
    util = 0;
    util_update = util_up;
}

finch2::finch2(double x, double y, void (* up)(agent*,agent*), void (* util_up)(double , double , double , double, finch2* ), unsigned char genes[9]) : finch(x,y,up,genes){
    util = 0;
    util_update = util_up;
}


#ifndef EVOPROB_H
#define EVOPROB_H

#include "constants.h"
#include <cmath>

//TODO: Remove in favor of inplace sort.
#include <vector>
#include <cstdlib>
#include <algorithm>

void evo_prob(unsigned char oldparams [STUDYSIZE][9], int number_prev_gen);


#endif
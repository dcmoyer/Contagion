/*
 
 This is the World class header for the Contagion Project, UCLA REU 2013.
 
 062413 1150 Created. (DM)
 
 
 */


#ifndef WORLD_H
#define WORLD_H

#include "constants.h"
#include "agent.h"
#include "cell.h"

class world {
public:
    vector<agent*> agents_master[NUM_OF_AGENTS];
    cell  cellList[DOMAIN_DIM_1][DOMAIN_DIM_2];
    void print();
	void add_agent();
	void add_agent(double x, double y);
	void add_agent(double x, double y, double z);
	void populate();
	void populate_rand();
private:
    void refresh();
};


#endif


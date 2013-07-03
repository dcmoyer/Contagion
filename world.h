/*
 
 This is the World class header for the Contagion Project, UCLA REU 2013.
 
 062413 1150 Created. (DM)
 
 
 */


#ifndef WORLD_H
#define WORLD_H

#include "constants.h"
#include "agent.h"
#include "cell.h"
#include <vector>
#include "helper_fcns.h"
#include <iostream>
#include <fstream>

void ab4_update(agent smith);
void euler_update(agent &smith);

class world {
public:
    std::vector<agent*> agents_master;
    cell* cellList[DOMAIN_DIM_1][DOMAIN_DIM_2];
    
    cell* theLonelyIsland; //no agent is an island.

	world();
    ~world();
    
    void print(std::ostream& strm);
    void print_csv(std::ostream& out)
	void add_agent();
	void add_agent(double x, double y);
	void add_agent(double x, double y, double z, void (* up)(agent*,agent*));
	void populate();
	void populate_rand();
	void populate(int n);
	void populate_rand(int n);
	void refresh_ab4();
	void refresh_eul();
	void move_to_cell();
    
    void update_forward_velocs();
    void update_agent_pos();
private:
    bool world_pos_update_flag; //This bool is to be checked against to see if an agent has been updated or not.
    
};


#endif


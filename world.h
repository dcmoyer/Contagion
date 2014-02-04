/*
 
 This is the World class header for the Contagion Project, UCLA REU 2013.
 
 062413 1150 Created. (DM)
 
 
 */


#ifndef WORLD_H
#define WORLD_H

#include "constants.h"
#include "agent.h"
#include "predator.h"
#include "finch.h"
#include "cell.h"
#include "wall.h"
#include "finch2.h"
#include <vector>
//#include "helper_fcns.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstddef>
#include <cmath>
#include <algorithm>

void ab4_update(agent smith);
void euler_update(agent &smith);


using std::vector;

class world {
public:
    world();
    ~world();
	vector<agent*> agents_master;
    cell* cellList[DOMAIN_DIM_1][DOMAIN_DIM_2];
    cell* theLonelyIsland; //no agent is an island.
	int death_count;
    
    void add_agent(double x, double y, void (* up)(agent*,agent*));
    void add_predator(double x, double y, void (* up)(agent*,agent*));
	void add_wall(double c_x, double c_y, double n_x, double n_y, double len, void (* up)(agent*,agent*));
	void add_boundary(void (* up)(agent*,agent*));	
	void add_finch_rand(double x, double y, void (* up)(agent*,agent*));
	void add_finch(double x, double y, void (* up)(agent*,agent*), unsigned char params[7]);
	void add_finch2(double x, double y, void (* up)(agent*,agent*), void (* util_up)(double , double , double , double, finch2* ), unsigned char params[7]);
	void add_finch2_rand(double x, double y, void (* up)(agent*,agent*), void (* util_up)(double , double , double , double, finch2* ));
    
    

	void populate(int n, vector<double>& xpos, vector<double>& ypos, void (* up)(agent*,agent*));
    void populate_rand(int n, void (* up)(agent*,agent*));
    void populate_predator_rand(int n, void (* up)(agent*,agent*));
	void populate_finches_rand(int n, void (* up)(agent*,agent*));
	void populate_finches_std(int n, void (* up)(agent*,agent*));
    void populate_finches2_rand(int n, void (* up)(agent*, agent*), void (* util_up)(double , double , double , double, finch2* ));
    
	void repopulate1(void (* up)(agent*,agent*), std::ostream& gen_out);
	void repopulate2(void (* up)(agent*,agent*), std::ostream& strm);
    void repopulate_CS_util(void (* up)(agent*, agent*), void (* util_up)(double , double , double , double, finch2* ), std::ostream& gen_out);
    

	void run(std::ostream& strm, int print_every, int iterations);
	void run_evolution(std::ostream& strm);
    void run_evolution_2(std::ostream& strm);

    cell* get_cell(int i, int j);
    int is_empty(int i, int j);
    

	void update_forward_velocs();
    void update_agent_pos_euler();
    void update_agent_pos_ab4();
	void euler_evolve();
    void ab4_evolve();
    void update_utility();
	
	void move_to_cell();
	void move_to_cell_evo();
	void print(std::ostream& strm);
	void print_csv(std::string filename);
	void print_parameter(std::ostream& strm);

 private:
    
};


#endif


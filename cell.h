/*

 This is the header for the cell class for the Contagion Project, REU 2013.
 
 062413 1457 Created (DM)
 062413 1649 Added constructors, accessors, and mutators for cell_node, and a
    default constructor for cell. (DM)
 
*/
#ifndef CELL_H
#define CELL_H

#include "agent.h"
#include <vector>

/*
 CELL:
 Main Class. It's so classy.
 
*/
class cell{
//private:

public:
    cell_node* top; //WILL BE LINKED LIST LATER
    std::vector<cell*>;
    
    double center_x;
    double center_y;
    
    cell();
    cell(vector<cell*> &neighbors, vector<agents*> &agents);
    
    void set_neighbors(vector<cell*> );
    
    friend class cell_node; //Yes, bad practice, but they're tied. Don't do this at home kids.
};


/*
 CELL_NODE:
 This is a two way linked list. It is intended to allow a cell to pass agents easily.
 
 AFTER UPDATE, for epsilon remove a node from list or remove it as a possibility from being checked by anyone.
 
 */
class cell_node{
private:
    cell_node* toward_top;
    cell_node* away_from_top;
    agent* target_agent;
    
    cell_node();
    cell_node(agent* target);
    
    void set_toward_top(cell_node* &up);
    void set_away_from_top(cell_node* &down);
    void set_target_agent(agent* &target);
    
    cell_node* get_toward_top();
    cell_node* get_away_from_top();
    agent* get_target_agent();
    
    friend class cell; //Yes, bad practice, but they're tied. Don't do this at home kids.
    
};

#endif

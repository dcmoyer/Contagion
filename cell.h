/*

 This is the header for the cell class for the Contagion Project, REU 2013.
 
 062413 1457 Created (DM)
 062413 1649 Added constructors, accessors, and mutators for cell_node, and a
    default constructor for cell. (DM)

 THE COPY CONSTRUCTOR, ASSIGNMENT OPERATOR AND DESTRUCTOR ARE MISSING!
 
*/
#ifndef CELL_H
#define CELL_H

#include "agent.h"
#include <vector>

/*
 CELL:
 Main Class. It's so classy. It's implemented as a singly-linked list of agent pointers.
 
*/
class cell{
//private:

public:
    cell_node* top; 
	cell_node* current; 

    std::vector<cell*> neighbors; 
    
    double center_x;
    double center_y; 
    
	/*
	Default constructor
	*/
    cell();

	/*
	Fancy constructor
	*/
    cell(vector<agents*> &agents);
    
	/*
	Set neighbors
	*/
    void set_neighbors(vector<cell*> &neighbors); 
    
	/*
	Add to the beginning of the list
	*/
	void add_top(cell_node new_node);

	/*
	Remove the first node in the list
	*/
	void remove_top();

	/*
	Get the first node in the list
	*/
	cell_node get_top();

	/*
	Move the current pointer to the next node
	*/
	void next();

	/*
	Reset current pointer to the top
	*/
	void reset_current();

    friend class cell_node; //Yes, bad practice, but they're tied. Don't do this at home kids.
};


/*
 CELL_NODE:
 AFTER UPDATE, for epsilon remove a node from list or remove it as a possibility from being checked by anyone.
 
 */
class cell_node{
private:
    cell_node* next;
    agent* target_agent;
    
	/*
	Default constructor
	*/
    cell_node();

	/*
	Fancy constructor
	*/
    cell_node(agent* target);

	/*
	Set the next node
	*/
    void set_next(cell_node* &next_node);

	/*
	Set the agent 
	*/
    void set_agent(agent* &target);
    
	/*
	Return the next node
	*/
    cell_node* get_next();

	/*
	Return the agent
	*/
    agent* get_agent();
    
    friend class cell; //Yes, bad practice, but they're tied. Don't do this at home kids.
    
};

#endif

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
 Main Class. It's so classy. It's implemented as a singly-linked list of agent pointers.
 
*/
class cell{

private:
	cell_node* top;
	double center_x;
    double center_y; 

public:
    cell_node* top; 
    
	/*
	Default constructor
	*/
    cell();
    
	/*
	Destructor
	*/
	~cell();

	/*
	Copy constructor
	*/
	cell(const cell& rhs);

	/*
	Assignment operator
	*/
	const cell& operator=(const cell& rhs);

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
	cell_node get_top() const;

	/*
	Check whether the list is empty
	*/
	bool is_empty();

    friend class cell_node; 
};


/*
 CELL_NODE:
 AFTER UPDATE, for epsilon remove a node from list or remove it as a possibility from being checked by anyone.
 
 */
class cell_node{

private:
    cell_node* next;
    agent* target_agent;

public:
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
    agent* get_agent() const;
    
    friend class cell; 
    
};

#endif

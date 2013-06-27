/*

 This is the header for the cell class for the Contagion Project, REU 2013.
 
 062413 1457 Created (DM)
 062413 1649 Added constructors, accessors, and mutators for cell_node, and a
    default constructor for cell. (DM)
<<<<<<< HEAD
 062513 1457 Changed get_top and remove_top return values to node pointers.
 
 THE COPY CONSTRUCTOR, ASSIGNMENT OPERATOR AND DESTRUCTOR ARE MISSING!
 
=======

>>>>>>> 8f90395b1ed96062d7bfd11ac3b867035334557d
*/
#ifndef CELL_H
#define CELL_H

#include "agent.h"
#include <vector>

//Sign In.
class cell;
class cell_node;
class cell_node_iterator;

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
<<<<<<< HEAD

    std::vector<cell*> neighbors; 
    
    double center_x;
    double center_y; 
=======
>>>>>>> 8f90395b1ed96062d7bfd11ac3b867035334557d
    
	/*
     
	Default constructor
	
     */
    cell();
    
	/*
	Destructor
	*/
	~cell();

	/*
<<<<<<< HEAD
     
	Fancy constructor
	
     */
    cell( std::vector<agent*> &agents);
    
    /*
     
     Destructor
     
     */
    
    ~cell();
    
    
	/*
     
	Set neighbors
	
     */
    void set_neighbors(std::vector<cell*> &neigh); 
    
=======
	Copy constructor
	*/
	cell(const cell& rhs);

	/*
	Assignment operator
	*/
	const cell& operator=(const cell& rhs);

>>>>>>> 8f90395b1ed96062d7bfd11ac3b867035334557d
	/*
     
	Add to the beginning of the list
	
     */
	void add_top(cell_node* new_node);

    /*
     
    Add a new node to the beginning of a list;
     
     */
    
    void add_top(agent* target);
    
	/*
     
	Remove the first node in the list
	
     */
	cell_node* remove_top();

	/*
     
	Get the first node in the list
<<<<<<< HEAD
	
     */
	cell_node* get_top();
    
    /*
     
     Check if list is empty.
     
     */
    
    void move_top(cell* target);
    
    bool isempty();
    
    friend class cell_node; //Yes, bad practice, but they're tied. Don't do this at home kids.
    friend class cell_node_iterator;
=======
	*/
	cell_node get_top() const;

	/*
	Check whether the list is empty
	*/
	bool is_empty();

    friend class cell_node; 
>>>>>>> 8f90395b1ed96062d7bfd11ac3b867035334557d
};


/*
 CELL_NODE:
 AFTER UPDATE, for epsilon remove a node from list or remove it as a possibility from being checked by anyone.
 
 
 MUST DELETE AGENT ELSEWHERE!
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
    cell_node(agent &target);

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
    agent get_agent() const;
    
<<<<<<< HEAD
    friend class cell; //Yes, bad practice, but they're tied. Don't do this at home kids.
    friend class cell_node_iterator;
};

class cell_node_iterator{
public:
    
    cell* home_cell; //pointer to the mother ship
    cell_node* current; //pointer to the link we're at
    
    /*
     
     Constructor
    
     */
    cell_node_iterator();
    
    cell_node_iterator(cell* home);
    
	/*
     
     Move the current pointer to the next node
     
     */
	void next();
    
	/*
     
     Reset current pointer to the top
     
     */
	void reset_current();
=======
    friend class cell; 
>>>>>>> 8f90395b1ed96062d7bfd11ac3b867035334557d
    
    agent* get_current();
};

#endif

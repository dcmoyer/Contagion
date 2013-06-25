/*
 
 This is the cell class for the Contagion Project, UCLA REU 2013.
 
 062413 1503 Created (DM)
 062413 1649 Added constructors, accessors, and mutators for cell_node, and a
    default constructor for cell. (DM)
 
 */

#include "cell.h"

/*
 
 Default constructor for cell.
 
 */
cell::cell(){
    
    top = NULL;
 current = NULL;
	neighbors = NULL;
    center_x = 0;
    center_y = 0;
    
}

/*
 
 Constructor for cells. Takes two vectors, one of pointers to the cell neighbors,
 and one of pointers to the agents of the cell. This is meant to be used in the
 instantiation of the world class.
 
 */
cell::cell(vector<agents*> &agents){
    
	center_x = 0;
	center_y = 0;
	neighbors = NULL;
	top = &agents[0];
	current = top;
	for (int i = 1; i < &agents.size(); i++) {
		add_top(&agents[i]);
	}
	reset_current();
    
}

	/*
	Set neighbors
	*/
    void set_neighbors(vector<cell*>) {
	
		neighbors = neighbors;
	}
    
	/*
	Add to the beginning of the list
	*/
	void add_top(cell_node new_node) {

		new_node.set_next(top);
		*top = new_node;
	}

	/*
	Remove the first node in the list
	*/
	void remove_top() {

		delete *top;
		top = top->get_next();
	}


	/*
	Get the first node in the list
	*/
	cell_node get_top() {

		return *top;
	}

	/*
	Move the current pointer to the next node
	*/
	void next() {

		current = current->get_next();
	}

	/*
	Reset current pointer to the top
	*/
	void reset_current() {

		current = top;
	}


/*
 
 Default constructor for the cell_nodes. 
 
 */
cell_node::cell_node(){
    
    next = NULL;
    target_agent = NULL;
    
}

/*
 
 Constructor for the cell_nodes. Meant to be used only with Cell class.
 
*/

cell_node::cell_node(agent* target){
    
    target_agent = target;
    next = NULL;
    
}

void cell_node::set_next(cell_node* &next_node) {

	next = &next_node;
}

void cell_node::set_agent(agent* &target){
    
    target_agent = target;
    
}

/*
 
 Accessor Functions.
 
 */

cell_node* cell_node::get_next() {

	return next;
}

agent* cell_node::get_agent(){
    
    return target_agent;
    
}


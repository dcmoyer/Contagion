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
    center_x = 0;
    center_y = 0;
    
}

/*
Destructor
*/
cell::~cell() {
	clear();
}

/*
Copy constructor
*/
cell::cell(const cell& rhs) {

	if (rhs.top == NULL) {
		top = NULL;
	} else {
		top = new cell_node(rhs.top->get_agent());

		cell_node* finger = rhs.top->get_next();
		cell_node* current = head;

		while (finger != NULL) {
			current->set_next(new cell_node(finger->get_agent()));
			current = current->get_next();
			finger = finger->get_next();
		}
	}
}

/*
Assignment operator
*/
const cell::cell& operator=(const cell& rhs) {
	if (this != &rhs) {
		clear();

		if (rhs.top == NULL) {
			top == NULL;
		} else {
			top = new cell_node(rhs.top->get_agent());

			cell_node* finger = rhs.top->get_next();
			cell_node* current = head;

			while (finger != NULL) {
				current->set_next(new cell_node(finger->get_agent()));
				current = current->get_next();
				finger = finger->get_next();
			}
		}
	}
	return *this;
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
cell_node get_top() const {

	return *top;
}

bool is_empty() {

	return (top == NULL);
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

cell_node::cell_node(agent &target){
    
    *target_agent = &target;
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

agent cell_node::get_agent() const{
    
    return *target_agent;
    
}

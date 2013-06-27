/*
 
 This is the cell class for the Contagion Project, UCLA REU 2013.
 
 062413 1503 Created (DM)
 062413 1649 Added constructors, accessors, and mutators for cell_node, and a
    default constructor for cell. (DM)

 */

#include "cell.h"

//**********CELL CLASS***********//

/*
 
 Default constructor for cell.
 
 */
cell::cell(){
    
    top = NULL;
    center_x = 0;
    center_y = 0;
    //neighbors is empty
    
}

/*
 
 Constructor for cells. Takes two vectors, one of pointers to the cell neighbors,
 and one of pointers to the agents of the cell. This is meant to be used in the
 instantiation of the world class.
 
 */
cell::cell(std::vector<agent*> &agents){
    
    int len = agents.size();
	center_x = 0;
	center_y = 0;
    top = 0; //NULL
    
    if(len == 0)
        return;
        
    //BUG
	for (int i = 1; i < len; i++) {
		add_top(agents[i]);
	}
    
}

/*
 
 Destructor
 
 */

cell::~cell(){
    
    cell_node* temp;
    
    while(! isempty()){
        temp = top->next;
        delete top;
        top = temp;
    }
    
}

/*
 
 Copy Constructor: This should not be used. But...just incase.
 
 */

cell::cell(const cell& rhs) {
    
    cell_node* temp;
    
    while(! isempty()){
        temp = top->next;
        delete top;
        top = temp;
    }
    
	if (rhs.top == NULL) {
		top = NULL;
	} else {
        temp = rhs.top;
        
		while (temp != NULL) {
			current->set_next(new cell_node(finger->get_agent()));
			current = current->get_next();
			finger = finger->get_next();
		}
	}

}

/*
 
Set neighbors

 */
void cell::set_neighbors(std::vector<cell*> &neigh){

    neighbors = neigh;

}

/*
Add to the beginning of the list
*/
void cell::add_top(cell_node* new_node) {

    new_node->next = top;
    top = new_node;
    
}

void cell::add_top(agent* new_node) {
    
    cell_node* new_top = new cell_node;
    new_top->next = top;
    new_top->target_agent = new_node;
    top = new_top;
    
}

/*
Remove the first node in the list
*/
cell_node* cell::remove_top() {

    cell_node* out = top;
    top = top->next;
    return out;

}

/*
Get the first node in the list
*/
cell_node* cell::get_top(){
    
    return top;

}
/*
 
 Destructor

 
cell::~cell() {
	clear();
}

/*
Copy constructor

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

void add_top(cell_node new_node) {

	new_node.set_next(top);
	*top = new_node;
}

/*
Remove the first node in the list

void remove_top() {

	delete *top;
	top = top->get_next();
}


/*
Get the first node in the list

cell_node get_top() const {

	return *top;
}

bool is_empty() {

	return (top == NULL);
}

/*
 
 Checks if empty.
 
 */

bool cell::isempty(){
    
    return top == 0;
    
}

void cell::move_top(cell* target){
    
    if(isempty())
        return;
    cell_node* temp = top->next;
    target->add_top(top);
    top = temp;
    
}

//**********CELL NODE CLASS***********//

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

cell_node::cell_node(agent* &target){
    
    target_agent = target;
    next = NULL;
    
}

/*
 
 Mutator Functions.
 
 */

void cell_node::set_next(cell_node* &next_node) {

	next = next_node;
    
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
    
//**********CELL NODE ITERATOR CLASS***********//


cell_node_iterator::cell_node_iterator(){
    
    home_cell = 0;
    current = 0;
    
}

cell_node_iterator::cell_node_iterator(cell* home){

    home_cell = home;
    current = home->top;

}

void cell_node_iterator::next(){
    
    current = current->next;
    
}

void cell_node_iterator::reset_current(){
    
    current = home_cell->top;
    
}

agent* cell_node_iterator::get_current(){
    
    return current->target_agent;
    
}

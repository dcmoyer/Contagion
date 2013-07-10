/*
 
 This is the cell class for the Contagion Project, UCLA REU 2013.
 
 062413 1503 Created (DM)
 062413 1649 Added constructors, accessors, and mutators for cell_node, and a
    default constructor for cell. (DM)

 */

#include "cell.h"
#include <cstdlib>

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
cell::cell(vector<agent*> &agents){
    
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
    
    while(!isempty()){
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
            add_top(temp->target_agent);
            temp = temp->next;
		}
	}

}

/*
 
 Assignment Operator
 
 */

cell& cell:: operator=(const cell& rhs) {
    
    cell_node* temp;

	if (this != &rhs) {
        
        while(!isempty()){
            temp = top->next;
            delete top;
            top = temp;
        }
        
		if (rhs.top == NULL) {
			top == NULL;
		} else {
            add_top(rhs.top->target_agent);
            temp = rhs.top->next;
            while( temp != NULL ){
                
                add_top(temp->target_agent);
                temp = temp->next;
                
            }
		}
	}
	return *this;
}

/*
 
Set neighbors

 */
void cell::set_neighbors(vector<cell*> &neigh){

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

cell_node_iterator cell::get_iter(){
    
    return cell_node_iterator(this);
    
}

cell* cell::get_neighbor(int index){
    
    if(index > neighbors.size())
        return NULL;
    
    return neighbors[index];
    
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

bool cell::in_the_cell(agent* target) const {
	double x = target->get_x_coord();
	double y = target->get_y_coord();
	double min_x = center_x - (CELL_LENGTH/2);
	double max_x = center_x + (CELL_LENGTH/2);
	double min_y = center_y - (CELL_LENGTH/2);
	double max_y = center_y + (CELL_LENGTH/2);	
	return (min_x < x && x < max_x && min_y < y && y< max_y);
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

void cell_node::set_next(cell_node* next_node) {

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

agent* cell_node::get_agent() const{
    
    return target_agent;
    
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
*/

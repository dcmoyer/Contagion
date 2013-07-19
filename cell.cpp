

#include "cell.h"
#include <iostream>


//*******************************************CELL*******************************************//

//Default constructor for cell.
cell::cell()
{
	top = NULL;  
	//neighbors is empty
}

//Copy Constructor
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

//Destructor
cell::~cell(){
    
    cell_node* temp;
    
    while(!isempty()){
        temp = top->next;
        delete top;
        top = temp;
    }
    
}

//Assignment Operator
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

//Set neighbors
void cell::set_neighbors(vector<cell*> &neigh){

    neighbors = neigh;

}

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

cell_node* cell::remove_top() {
    cell_node* out = top;
    top = top->next;
    return out;
}

void cell::extract_node_and_add(cell_node* target, cell* new_home){
	if(target == NULL){
		return;
	}
	if(target == top){
		top = target->next;
		new_home->add_top(target);
		return;
	}

	cell_node* temp = top;
	while(temp != NULL){
		
		if(temp->next == target){
		
			temp->next = temp->next->next;
			break;
		}
		temp = temp->next;
	}
	new_home->add_top(target);
}

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



//*****************************************CELL NODE CLASS******************************//


cell_node::cell_node(){
    
    next = NULL;
    target_agent = NULL;
    
}


cell_node::cell_node(agent* &target){
    
    target_agent = target;
    next = NULL;
    
}


//Mutator Functions.

void cell_node::set_next(cell_node* next_node) {

	next = next_node;
    
}

void cell_node::set_agent(agent* &target){
    
    target_agent = target;
    
}


//Accessor Functions.

cell_node* cell_node::get_next() const {

	return next;
}

agent* cell_node::get_agent() const{
    
    return target_agent;
    
}
    
//***************************************CELL NODE ITERATOR CLASS********************//


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

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
 
 Constructor for cells. Takes two vectors, one of pointers to the cell neighbors,
 and one of pointers to the agents of the cell. This is meant to be used in the
 instantiation of the world class.
 
 */
cell::cell(vector<cell*> &neighbors, vector<agents*> &agents){
    
    
    
}

/*
 
 Default constructor for the cell_nodes. 
 
 */
cell_node::cell_node(){
    
    toward_top = NULL;
    away_from_top = NULL;
    target_agent = NULL;
    
}

/*
 
 Constructor for the cell_nodes. Meant to be used only with Cell class.
 
*/

cell_node::cell_node(agent* target){
    
    target_agent = target;
    toward_top = NULL;
    away_from_top = NULL;
    
}

/*
 
 Mutator Functions.
 
 */

void cell_node::set_toward_top(cell_node* &up){

    toward_top = up;
    
}

void cell_node::set_away_from_top(cell_node* &down){
    
    away_from_top = down;
    
}

void cell_node::set_target_agent(agent* &target){
    
    target_agent = target;
    
}

/*
 
 Accessor Functions.
 
 */

cell_node* cell_node::get_toward_top(){
    
    return toward_top;
    
}

cell_node* cell_node::get_away_from(){
    
    return away_from_top;
    
}

agent* cell_node::get_target_agent(){
    
    return target_agent;
    
}

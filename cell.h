#ifndef CELL_H
#define CELL_H

#include "agent.h"
#include <vector>
#include <cstdlib>

using std::vector;

//Sign In.
class cell;
class cell_node;
class cell_node_iterator;

//*******************************************CELL*******************************************//
class cell
{
public:
    cell_node* top; 
    vector<cell*> neighbors; 
    
    cell(); //Default Constructor
    cell(const cell& rhs); //Copy Constructor
    ~cell(); //Destructor
    cell& operator=(const cell& rhs); //Assignment Operator

    void set_neighbors(vector<cell*> &neigh); 
   
    void add_top(cell_node* new_node);
    void add_top(agent* target);
    cell_node* remove_top();
    cell_node* get_top();
    
    cell_node_iterator get_iter();
    
    cell* get_neighbor(int index);
    
    void move_top(cell* target);
    void extract_node_and_add(cell_node* target, cell* new_home);
    void remove_all();
    
    bool isempty();
    
    friend class cell_node; //Yes, bad practice, but they're tied. Don't do this at home kids.
    friend class cell_node_iterator;
    
    cell_node get_top() const;

};


//*****************************************CELL NODE CLASS******************************//
class cell_node{

private:
    cell_node* next;
    agent* target_agent;

public:
   
    cell_node();
    cell_node(agent* &target);
    
    void set_next(cell_node* next_node);
    void set_agent(agent* &target);
    
    cell_node* get_next() const;
    agent* get_agent() const;
    
    friend class cell; //Yes, bad practice, but they're tied. Don't do this at home kids.
    friend class cell_node_iterator;
};

//***************************************CELL NODE ITERATOR CLASS********************//

class cell_node_iterator{
public:
    
    cell* home_cell; //pointer to the mother ship
    cell_node* current; //pointer to the link we're at
    
    cell_node_iterator();
    cell_node_iterator(cell* home);
    
    void next();
    void reset_current();
    
    agent* get_current();
    
    friend class cell; 
};

#endif

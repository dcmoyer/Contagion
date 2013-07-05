// Must reset ALPHA and BETA to 0.0 to run correctly

#include "world.h"
#include "helper_fcns.h"
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;
using std::vector;


int main()
{

  // Make a world with one agent at some initial point, with left constant large velocity
  // Move the agent across and have it print out cell numbers
  // Then add another cell that moves down and do the same thing.
  // Don't call world functions that update velocity

  
  //move the agent to the left

  double speed = (double)CELL_LENGTH/(double)STEP_SIZE;

  double x = 0.0;
  double y = 0.0;

  world w = world();
  w.add_agent(5.0,5.0);
  w.agents_master[0]->set_x_veloc(speed);
  w.agents_master[0]->set_y_veloc(0.0);
  
  //Do this inside for loop after every move (Look at main)
  int dim1 = w.agents_master[0]->cell_num_dim1();
  int dim2 = w.agents_master[0]->cell_num_dim2(); 

  cout << "dim1=" << dim1 << " dim2=" << dim2 << endl;

  assert(w.is_empty(dim1,dim2)==0);

  assert(w.is_empty(1,1)==1);

  for(int i=1; i<DOMAIN_DIM_1;i++)
    {

      w.update_agent_pos();
      w.move_to_cell();

      assert(w.is_empty(dim1,dim2)==1);
      
      dim1 = w.agents_master[0]->cell_num_dim1();
      dim2 = w.agents_master[0]->cell_num_dim2(); 
      
      cout << "dim1=" << dim1 << " dim2=" << dim2 << endl;
      
      assert(w.is_empty(dim1,dim2)==0);
    }

  //agent move downwards

  w.agents_master[0]->set_x_veloc(0.0);
  w.agents_master[0]->set_y_veloc(speed);
  for(int i=1; i<DOMAIN_DIM_2;i++)
    { 
      w.update_agent_pos();
      w.move_to_cell();

      assert(w.is_empty(dim1,dim2)==1);

      dim1 = w.agents_master[0]->cell_num_dim1();
      dim2 = w.agents_master[0]->cell_num_dim2(); 

      assert(w.is_empty(dim1,dim2)==0);

      cout << "dim1=" << dim1 << " dim2=" << dim2 << endl;
    }

  //agent move to the right

  w.agents_master[0]->set_x_veloc(-speed);
  w.agents_master[0]->set_y_veloc(0.0);
  for(int i=1; i<DOMAIN_DIM_1;i++)
    { 
      w.update_agent_pos();
      w.move_to_cell();

      assert(w.is_empty(dim1,dim2)==1);

      dim1 = w.agents_master[0]->cell_num_dim1();
      dim2 = w.agents_master[0]->cell_num_dim2(); 
      
      assert(w.is_empty(dim1,dim2)==0);

      cout << "dim1=" << dim1 << " dim2=" << dim2 << endl;
    }
  
  //agent move upwards

  w.agents_master[0]->set_x_veloc(0.0);
  w.agents_master[0]->set_y_veloc(-speed);
  for(int i=1; i<DOMAIN_DIM_2;i++)
    { 
      w.update_agent_pos();
      w.move_to_cell();

      assert(w.is_empty(dim1,dim2)==1);

      dim1 = w.agents_master[0]->cell_num_dim1();
      dim2 = w.agents_master[0]->cell_num_dim2(); 

      cout << "dim1=" << dim1 << " dim2=" << dim2 << endl;

      assert(w.is_empty(dim1,dim2)==0);
      
    }

  //agent move diagonally

  w.agents_master[0]->set_x_veloc(speed);
  w.agents_master[0]->set_y_veloc(speed);

  for(int i=1; i<DOMAIN_DIM_1;i++) {
      w.update_agent_pos();
      w.move_to_cell();

      assert(w.is_empty(dim1,dim2)==1);

      dim1 = w.agents_master[0]->cell_num_dim1();
      dim2 = w.agents_master[0]->cell_num_dim2(); 
      
      assert(w.is_empty(dim1,dim2)==0);

      cout << "dim1=" << dim1 << " dim2=" << dim2 << endl;
  }
  return 0;
}

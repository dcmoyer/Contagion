#include "world.h"
#include "helper_fcns.h"
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;
using std::vector;


int main()
{
  
  world w = world();
  w.add_agent(3.0,4.0);
  assert(w.agents_master[0]->get_x_coord()==3.0);
  assert(w.agents_master[0]->get_y_coord()==4.0);
  assert(w.agents_master[0]->get_x_veloc()[0]==0.0);  
  assert(w.agents_master[0]->get_y_veloc()[0]==0.0);  
  
  w.add_agent(1.0,2.0,go_left_test);
  assert(w.agents_master[1]->get_x_coord()==1.0);
  assert(w.agents_master[1]->get_y_coord()==2.0);

  world h =world();

  
  vector<double> xpos(10);
  vector<double> ypos(10);

  for (int i = 0; i < 10; i++) {
    xpos[i] = 1.0*i;
    ypos[i] = 2.0*i;
  }
  
  h.populate(10,xpos,ypos,go_left_test);
  assert(h.agents_master[0]->get_x_coord()==0.0);
  assert(h.agents_master[0]->get_y_coord()==0.0);
  assert(h.agents_master[1]->get_x_coord()==1.0);
  assert(h.agents_master[1]->get_y_coord()==2.0);

  
  
 
  

  cout << "Passed all tests" << endl;


  return 0;
}

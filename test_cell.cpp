#include "cell.h"
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;


int main()
{
  
  cell c = cell();
  agent a = agent(3.0,4.0);
  c.add_top(&a);
  
  cell_node* pcn = c.get_top();
  agent* pa = pcn->get_agent();

  assert(pa->get_x_coord()==3.0);
  assert(pa->get_y_coord()==4.0);

  agent b = agent(1.0,2.0);
  c.add_top(&b);
  

  // These two commands do the same thing
  //cell_node_iterator iter(&c);  
  cell_node_iterator iter = c.get_iter();

  pa = iter.get_current();

  assert(pa->get_x_coord()==1.0);
  assert(pa->get_y_coord()==2.0);
  
  iter.next();
  pa = iter.get_current();

  assert(pa->get_x_coord()==3.0);
  assert(pa->get_y_coord()==4.0);

  cout << "Passed all tests" << endl;


  return 0;
}

#include "agent.h"
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;


int main()
{
  agent a = agent(2.0, 5.0);

  assert(a.get_x_coord() == 2.0);
  assert(a.get_y_coord() == 5.0);
	
  agent b = agent();

  b.set_x_coord(6.0);
  assert(b.get_x_coord() == 6.0);
  b.set_y_coord(3.0);
  assert(b.get_y_coord() == 3.0);
  b.set_z_coord(4.0);
  assert(b.get_z_coord() == 4.0);

  agent c = agent();
  c.set_x_veloc(2.0);
  assert(c.get_x_veloc()[0] == 2.0);
  c.set_y_veloc(3.0);
  assert(c.get_y_veloc()[0] == 3.0);

  agent d = agent();
  d.set_q_mag(4.0);
  assert(d.get_q_mag() == 4.0);

  agent e = agent();
  e.set_x_accel(1.0);
  assert(e.get_x_accel_index(0) == 1.0);
  e.set_y_accel(2.0);
  assert(e.get_y_accel_index(0) == 2.0);
  e.set_z_accel(3.0);
  assert(e.get_z_accel_index(0) == 3.0);
  cout << "All agent tests passed" << endl;

  return 0;
}

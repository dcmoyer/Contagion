#include "helper_fcns.h"

void ab4_update(agent smith)
{
  double vx [HIST_LENGTH];
  double vy [HIST_LENGTH];
  double vz [HIST_LENGTH];
  
  double* px = smith.get_x_veloc();
  for (int i = 0; i < HIST_LENGTH; i++)
  {
    vx[i] = *(px + i);
  }
  
  double* py = smith.get_y_veloc();
  for (int i = 0; i < HIST_LENGTH; i++)
  {
    vy[i] = *(py + i);
  }
  
  double* pz = smith.get_z_veloc();
  for (int i = 0; i < HIST_LENGTH; i++)
  {
    vz[i] = *(pz + i);
  }
  
  
  double new_x = smith.get_x_coord() + STEP_SIZE / 24 * (55 * vx[0] - 59 * vx[1] + 37 * vx[2] - 9 * vx[3]);
  double new_y = smith.get_y_coord() + STEP_SIZE / 24 * (55 * vy[0] - 59 * vy[1] + 37 * vy[2] - 9 * vy[3]);
  double new_z = smith.get_z_coord() + STEP_SIZE / 24 * (55 * vz[0] - 59 * vz[1] + 37 * vz[2] - 9 * vz[3]);
  
  smith.set_x_coord(new_x);
  smith.set_y_coord(new_y);
  smith.set_z_coord(new_z);
}

void euler_update(agent smith)
{
 
  
  double* px = smith.get_x_veloc();
  double* py = smith.get_y_veloc();
  double* pz = smith.get_z_veloc();
  
  double new_x = smith.get_x_coord() + STEP_SIZE  * (*px);
  double new_y = smith.get_y_coord() + STEP_SIZE  * (*py);
  double new_z = smith.get_z_coord() + STEP_SIZE  * (*pz);
  
  smith.set_x_coord(new_x);
  smith.set_y_coord(new_y);
  smith.set_z_coord(new_z);
}
#include "helper_fcns.h"
#include <cmath>

void prey(agent* me, agent* you)
{
	
	//get x,y,z coords
	double x1 = me->get_x_coord();
	double y1 = me->get_y_coord();
	//double z1 = (*me).get_z_coord();
	double x2 = you->get_x_coord();
	double y2 = you->get_y_coord();
	//double z2 = (*you).get_z_coord();

	//get component-wise velocity
	double vx1 = me->get_x_veloc_index(0);
	double vy1 = me->get_y_veloc_index(0);
	//double vz1 = (*me).get_z_veloc_index(0);
	double vx2 = you->get_x_veloc_index(0);
	double vy2 = you->get_y_veloc_index(0);
	//double vz2 = (*you).get_z_veloc_index(0);

	//calculate distances
	double dx= x2-x1;
	double dy= y2-y1;
	//double dz= z2-z1;
	double dvx = vx2-vx1;
	double dvy = vy2-vy1;
	//double dvz = vz2-vz1;
	double r = sqrt(dx*dx + dy*dy /*+ dz*dz*/);
	//double sum = std::abs(dx)+std::abs(dy)/*+std::abs(dz)*/;
	
	if (r < 50) {
		if (you->get_type() == 'd') {

			//calculate attraction/repulsion forces
			double u = -C_A * exp(-r / L_A) + C_R * exp(-r / L_R);

			//calculate alignment forces
			double h = KAPPA / pow((SIGMA*SIGMA + r*r), GAMMA);

			//update velocities
			double fx = u*dx/r + h*dvx;
			double fy = u*dy/r + h*dvy;
			//double fz = u*dz/sum + h*dvz;
    
			me->add_to_x_accel(fx);
			me->add_to_y_accel(fy);
		}
	
		if (you->get_type() == 'p') {
			if (r < 5) {
				me->kill();
			} else {
				double u = 10 * C_R * exp(-r / L_R);
				//update velocities
				double fx = u*dx/r;
				double fy = u*dy/r;
				me->add_to_x_accel(fx);
				me->add_to_y_accel(fy);
			}
		}
		me->iterate_NearestNeighbor();
	}
}

void predator(agent* me, agent* you)
{
	
	//get x,y,z coords
	double x1 = me->get_x_coord();
	double y1 = me->get_y_coord();
	//double z1 = (*me).get_z_coord();
	double x2 = you->get_x_coord();
	double y2 = you->get_y_coord();
	//double z2 = (*you).get_z_coord();

	//get component-wise velocity
	double vx1 = me->get_x_veloc_index(0);
	double vy1 = me->get_y_veloc_index(0);
	//double vz1 = (*me).get_z_veloc_index(0);
	double vx2 = you->get_x_veloc_index(0);
	double vy2 = you->get_y_veloc_index(0);
	//double vz2 = (*you).get_z_veloc_index(0);

	//calculate distances
	double dx= x2-x1;
	double dy= y2-y1;
	//double dz= z2-z1;
	double dvx = vx2-vx1;
	double dvy = vy2-vy1;
	//double dvz = vz2-vz1;
	double r = sqrt(dx*dx + dy*dy /*+ dz*dz*/);
	//double sum = std::abs(dx)+std::abs(dy)/*+std::abs(dz)*/;
	
	if (r < 100) {
		if (you->get_type() == 'd') {	

			//calculate attraction/repulsion forces
			double u = -10* C_A * exp(-r / L_A);

			//update velocities
			double fx = u*dx/r; 
			double fy = u*dy/r;
			//double fz = u*dz/sum + h*dvz;
    
			me->add_to_x_accel(fx);
			me->add_to_y_accel(fy);
			me->iterate_NearestNeighbor();
		}
	}
}

void swarm1(agent* me, agent* you)
{
	//get x,y,z coords
	double x1 = me->get_x_coord();
	double y1 = me->get_y_coord();
	//double z1 = (*me).get_z_coord();
	double x2 = you->get_x_coord();
	double y2 = you->get_y_coord();
	//double z2 = (*you).get_z_coord();

	//get component-wise velocity
	double vx1 = me->get_x_veloc_index(0);
	double vy1 = me->get_y_veloc_index(0);
	//double vz1 = (*me).get_z_veloc_index(0);
	double vx2 = you->get_x_veloc_index(0);
	double vy2 = you->get_y_veloc_index(0);
	//double vz2 = (*you).get_z_veloc_index(0);

	//calculate distances
	double dx= x2-x1;
	double dy= y2-y1;
	//double dz= z2-z1;
	double dvx = vx2-vx1;
	double dvy = vy2-vy1;
	//double dvz = vz2-vz1;
	double r = sqrt(dx*dx + dy*dy /*+ dz*dz*/);
	//double sum = std::abs(dx)+std::abs(dy)/*+std::abs(dz)*/;

	//calculate attraction/repulsion forces
	//double u = -C_A * exp(-r / L_A) + C_R * exp(-r / L_R);
	double ugrad = C_A/L_A * exp(-r / L_A) - C_R/L_R * exp(-r / L_R);

	//calculate alignment forces
	double h = KAPPA / pow((SIGMA*SIGMA + r*r), GAMMA);

	//update velocities
	double fx = ugrad*dx/r;// - h*dvx;
	double fy = ugrad*dy/r;// - h*dvy;
	//double fx = -h*dvx;
	//double fy = -h*dvy;
	//double fz = u*dz/sum + h*dvz;
    
    me->add_to_x_accel(fx);
    me->add_to_y_accel(fy);
	/*(*me).set_forward_v_x((*me).get_forward_v_x()+fx);
	(*me).set_forward_v_y((*me).get_forward_v_y()+fy);
	(*me).set_forward_v_z((*me).get_forward_v_z()+fz);*/
	//(*you).set_forward_v_x((*you).get_forward_v_x()+fx);
	//(*you).set_forward_v_y((*you).get_forward_v_y()+fy);
	//(*you).set_forward_v_z((*you).get_forward_v_z()+fz);
    
    me->iterate_NearestNeighbor();


}
void swarm_attract(agent* me, agent* you)
{
	//get x,y coords
	double x1 = (*me).get_x_coord();
	double y1 = (*me).get_y_coord();
	double x2 = (*you).get_x_coord();
	double y2 = (*you).get_y_coord();
	
	//get component-wise velocity
	double vx1 = (*me).get_x_veloc_index(0);
	double vy1 = (*me).get_y_veloc_index(0);
	double vx2 = (*you).get_x_veloc_index(0);
	double vy2 = (*you).get_y_veloc_index(0);
	
	//calculate distances
	double dx= x2-x1;
	double dy= y2-y1;
	double r = sqrt(dx*dx + dy*dy);
	double sum = std::abs(dx)+std::abs(dy);

        //calculate attraction force
	double u = 2*r;

	//update velocities
	double fx = u*dx/(sum + .000001);
	double fy = u*dy/(sum + .000001);
    
    me->add_to_x_accel(fx);
    me->add_to_y_accel(fy);
	//(*me).set_forward_v_x((*me).get_forward_v_x()+fx);
	//(*me).set_forward_v_y((*me).get_forward_v_y()+fy);
	//(*you).set_forward_v_x((*you).get_forward_v_x()+fx);
	//(*you).set_forward_v_y((*you).get_forward_v_y()+fy);
    
    me->iterate_NearestNeighbor();

}
void go_left_test(agent* me, agent* you){

    me->add_to_x_accel( (- 1.0 /*+ me->get_x_veloc_index(0)*/) / (double) NUM_OF_AGENTS);

}

#include "helper_fcns.h"

void prey(agent* me, agent* you)
{
	if(you->get_type() == 2){
		return;
	}
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
	

}

void predator_model(agent* me, agent* you)
{
	if(you->get_type() == 2){
		return;
	}
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
		if (you->get_type() == 0) {	

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
	if(you->get_type() == 2){
		return;
	}
	//get x,y,z coords
	double x1 = me->get_x_coord();
	double y1 = me->get_y_coord();
	//double z1 = (*me).get_z_coord();
	double x2 = you->get_x_coord();
	double y2 = you->get_y_coord();
	//double z2 = (*you).get_z_coord();
	//calculate distances
	double dx= x2-x1;
	double dy= y2-y1;
	//double dz= z2-z1;
	double r = sqrt(dx*dx + dy*dy /*+ dz*dz*/);

	if(r<CELL_LENGTH)
	{
	//get component-wise velocity
	double vx1 = me->get_x_veloc_index(0);
	double vy1 = me->get_y_veloc_index(0);
	//double vz1 = (*me).get_z_veloc_index(0);
	double vx2 = you->get_x_veloc_index(0);
	double vy2 = you->get_y_veloc_index(0);
	//double vz2 = (*you).get_z_veloc_index(0);
	double dvx = vx2-vx1;
	double dvy = vy2-vy1;
	//double dvz = vz2-vz1;
	

	//calculate attraction/repulsion forces
	//double u = -C_A * exp(-r / L_A) + C_R * exp(-r / L_R);
	double ugrad = C_A/L_A * exp(-r / L_A) - C_R/L_R * exp(-r / L_R);

	//calculate alignment forces
	double h = KAPPA / pow((SIGMA*SIGMA + r*r), GAMMA);

	//update velocities
	double fx = ugrad*dx/r + h*dvx;
	double fy = ugrad*dy/r + h*dvy;
	//double fx = -h*dvx;
	//double fy = -h*dvy;
	//double fz = u*dz/sum + h*dvz;
    
    me->add_to_x_accel(fx);
    me->add_to_y_accel(fy);
	//you->add_to_x_accel(-fx);
   // you->add_to_y_accel(-fy);
	/*(*me).set_forward_v_x((*me).get_forward_v_x()+fx);
	(*me).set_forward_v_y((*me).get_forward_v_y()+fy);
	(*me).set_forward_v_z((*me).get_forward_v_z()+fz);*/
	//(*you).set_forward_v_x((*you).get_forward_v_x()+fx);
	//(*you).set_forward_v_y((*you).get_forward_v_y()+fy);
	//(*you).set_forward_v_z((*you).get_forward_v_z()+fz);
    
    me->iterate_NearestNeighbor();
	}

}

void swarm1_fear(agent* me, agent* you)
{
	if(you->get_type() == 2){
		return;
	}
	
	//get x,y,z coords
	double x1 = me->get_x_coord();
	double y1 = me->get_y_coord();
	//double z1 = (*me).get_z_coord();
	double x2 = you->get_x_coord();
	double y2 = you->get_y_coord();
	//double z2 = (*you).get_z_coord();
	//calculate distances
	double dx= x2-x1;
	double dy= y2-y1;
	//double dz= z2-z1;
	double r = sqrt(dx*dx + dy*dy /*+ dz*dz*/);

	if(r<CELL_LENGTH)
	{
	//get component-wise velocity
	double vx1 = me->get_x_veloc_index(0);
	double vy1 = me->get_y_veloc_index(0);
	//double vz1 = (*me).get_z_veloc_index(0);
	double vx2 = you->get_x_veloc_index(0);
	double vy2 = you->get_y_veloc_index(0);
	//double vz2 = (*you).get_z_veloc_index(0);
	double dvx = vx2-vx1;
	double dvy = vy2-vy1;
	//double dvz = vz2-vz1;
	
	//get fear
	double q1 = me->get_q_mag();
	double q2 = you->get_q_mag();
	double dq = q2-q1;

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

//update fear
	double fq;
			
			if (dq > 0)
			{
				 fq = 6*h*dq;
				me->add_to_q_change(fq);
			}
			else
			{
				 fq = 3*h*dq;
				me->add_to_q_change(fq);
			}



	//you->add_to_x_accel(-fx);
   // you->add_to_y_accel(-fy);
	/*(*me).set_forward_v_x((*me).get_forward_v_x()+fx);
	(*me).set_forward_v_y((*me).get_forward_v_y()+fy);
	(*me).set_forward_v_z((*me).get_forward_v_z()+fz);*/
	//(*you).set_forward_v_x((*you).get_forward_v_x()+fx);
	//(*you).set_forward_v_y((*you).get_forward_v_y()+fy);
	//(*you).set_forward_v_z((*you).get_forward_v_z()+fz);
    
    me->iterate_NearestNeighbor();
	}

}

void swarm_attract(agent* me, agent* you)
{
	if(you->get_type() == 2){
		return;
	}
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
	if(you->get_type() == 2){
		return;
	}
	
    me->add_to_x_accel( (- 1.0 /*+ me->get_x_veloc_index(0)*/) / (double) NUM_OF_AGENTS);

}

void predator_2012( agent* me_fake, agent* you){
	if(you->get_type() == 2){
		return;
	}
    predator* me = (predator*) me_fake;
    //get x,y,z coords
	double x1 = me->get_x_coord();
	double y1 = me->get_y_coord();
	//double z1 = (*me).get_z_coord();
	double x2 = you->get_x_coord();
	double y2 = you->get_y_coord();
	//double z2 = (*you).get_z_coord();
    
    //calculate distances
	double dx= x2-x1;
	double dy= y2-y1;
    
    double r = sqrt(dx*dx + dy*dy /*+ dz*dz*/);
    
    if(r < me->running_r){
        if (you->get_type() == 0) {	
        	me->running_r = r;
        	me->set_x_accel( PRED_2012_SP * dx/std::abs(dx));
        	me->set_y_accel( PRED_2012_SP * dy/std::abs(dy));
		}
    }
    
}

void prey_2012_nofear(agent* me, agent* you){
	if(you->get_type() == 2){
		return;
	}
	
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

    me->iterate_NearestNeighbor();
    if (r < CELL_LENGTH) {
		if (you->get_type() == 0) {
            
            double ugrad = C_A/L_A * exp(-r / L_A) - C_R/L_R * exp(-r / L_R);
            
            //calculate alignment forces
            double h = KAPPA / pow((SIGMA*SIGMA + r*r), GAMMA);
            
            //update velocities
            double fx = ugrad*dx/r;// - h*dvx;
            double fy = ugrad*dy/r;// - h*dvy	//double fx = -h*dvx;
            
            me->add_to_x_accel(fx);
            me->add_to_y_accel(fy);
            
		}
        
		if (you->get_type() == 1) {
			if (r < 5) {
				me->kill();
			} else {
				double u = -20 * exp(-r / 10);
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

void prey_2012_fear(agent* me, agent* you){
    
	//wall check
	if(you->get_type() == 2){
		return;
	}
	
	//get x,y,z coords
	double x1 = me->get_x_coord();
	double y1 = me->get_y_coord();
	//double z1 = (*me).get_z_coord();
	double x2 = you->get_x_coord();
	double y2 = you->get_y_coord();
	//double z2 = (*you).get_z_coord();
    //calculate distances
	double dx= x2-x1;
	double dy= y2-y1;
	//double dz= z2-z1;
	double r = sqrt(dx*dx + dy*dy /*+ dz*dz*/);

    
    if (r < CELL_LENGTH) {

		//get component-wise velocity
	double vx1 = me->get_x_veloc_index(0);
	double vy1 = me->get_y_veloc_index(0);
	//double vz1 = (*me).get_z_veloc_index(0);
	double vx2 = you->get_x_veloc_index(0);
	double vy2 = you->get_y_veloc_index(0);
	//double vz2 = (*you).get_z_veloc_index(0);
    
	
	double dvx = vx2-vx1;
	double dvy = vy2-vy1;
	//double dvz = vz2-vz1;

	

		if (you->get_type() == 0) {
            

			//get fear
			double q1 = me->get_q_mag();
			double q2 = you->get_q_mag();
			double dq = q2-q1;

            double ugrad = C_A/L_A * exp(-r / L_A) - C_R/L_R * exp(-r / L_R);
            
            //calculate alignment forces
            double h = KAPPA / pow((SIGMA*SIGMA + r*r), GAMMA);
            
            //update velocities
            double fx = ugrad*dx/r;// - h*dvx;
            double fy = ugrad*dy/r;// - h*dvy	//double fx = -h*dvx;
            
            me->add_to_x_accel(fx);
            me->add_to_y_accel(fy);


			double fq;
			
			if (dq > 0)
			{
				 fq =6*h*dq;
				me->add_to_q_change(fq);
			}
			else
			{
				 fq = 3*h*dq;
				me->add_to_q_change(fq);
			}

            
		}
        
		if (you->get_type() == 1) {
			if (r < 5) {
				me->kill();
			} else {
				double u = - 2/30 *C_R/L_R * exp(-r / (30 * L_R));  
				//update velocities
				double fx = 100*u*dx/r;
				double fy = 120*u*dy/r;
				me->add_to_x_accel(fx);
				me->add_to_y_accel(fy);


				//get fear
				double q1 = me->get_q_mag();
				double q2 = 1;
				double dq = q2-q1;
				
				double h = KAPPA / pow((SIGMA*SIGMA + r*r), GAMMA);
				double fq =40*h*dq;
				me->add_to_q_change(fq);
			}
		}

		me->iterate_NearestNeighbor();
	}
    
}

/*void wall_interaction(agent* me_fake, agent* you){
	//This is the wall function.
	
	wall* me = (wall* ) me_fake;
	double r_x = you->x_coord - me->x_coord;
	double r_y = you->y_coord - me->y_coord;
	r = sqrt(pow(r_x,2) + pow(r_y,2))
	
	double n_dot_r = r_x * (me->normal_x) + r_y * (me->normal_y);
	double p_n_x = n_dot_r * (me->normal_x);
	double p_n_y = n_dot_r * (me->normal_y);
	if( sqrt(pow((r_x - p_n_x),2) + pow((r_y - p_n_y),2)) < (me->length) ){
		
		double u = (double) WALL_PWR / pow(r,5)
		
		double fx = u * r_x / r;
		double fy = u * r_y / r;
		
		you->add_to_x_accel(fx);
		you->add_to_y_accel(fy);
		
	}
	
	
}*/

//void finch1(finch* me_cast, agent* you)
//{
//	    finch* me = (finch*) me_cast;
//    
//	/*
//	//wall check
//	if(you->get_type() == 2){
//		return;
//	}
//	*/
//
//	//get x,y,z coords
//	double x1 = me->x_coord;
//	double y1 = me->get_y_coord();
//	double x2 = you->get_x_coord();
//	double y2 = you->get_y_coord();
//	
//    //calculate distances
//	double dx= x2-x1;
//	double dy= y2-y1;
//	double r = sqrt(dx*dx + dy*dy);
//
//    
//    if (r < CELL_LENGTH) 
//	{
//		if (you->get_type() == 0) \
//		{
//            //get component-wise velocity
//			double vx1 = me->get_x_veloc_index(0);
//			double vy1 = me->get_y_veloc_index(0);
//			double vx2 = you->get_x_veloc_index(0);
//			double vy2 = you->get_y_veloc_index(0);
//			double dvx = vx2-vx1;
//			double dvy = vy2-vy1;
//
//			//get fear
//			double q1 = me->get_q_mag();
//			double q2 = you->get_q_mag();
//			double dq = q2-q1;
//
//			//calculate attraction-repulsion
//            double ugrad = exp(-r ) - c1 * exp(-r / l1);
//            
//            //calculate alignment forces
//            double h = me->v_align_mag / pow((1 + r*r), me->gamma);
//            
//            //update velocities
//            double fx = ugrad*dx/r - h*dvx;
//            double fy = ugrad*dy/r - h*dvy;	//double fx = -h*dvx;
//            
//            me->add_to_x_accel_prey(fx);
//            me->add_to_y_accel_prey(fy);
//
//
//			double fq;
//			
//			if (dq > 0)
//			{
//				 fq = 6*h*dq;
//				me->add_to_q_change(fq);
//			}
//			else
//			{
//				 fq =3*h*dq;
//				me->add_to_q_change(fq);
//			}
//
//
//			me->iterate_NearestNeighbor();
//            
//		}
//        
//		if (you->get_type() == 1) 
//		{
//			if (r < 5) {
//				me->kill();
//			} else {
//				double u = -C_R/L_R * exp(-r / (L_R));  
//				//update velocities
//				double fx = me->pred_repel*u*dx/r;
//				double fy = me->pred_repel*u*dy/r;
//				me->add_to_x_accel_pred(fx);
//				me->add_to_y_accel_pred(fy);
//
//
//				//get fear
//				double q1 = me->get_q_mag();
//				double q2 = 1;
//				double dq = q2-q1;
//				
//				double h = KAPPA / pow((SIGMA*SIGMA + r*r), GAMMA);
//				double fq =  40*h*dq;
//				me->add_to_q_change(fq);
//			}
//
//			me->iterate_NearestPred();
//		}
//
//		
//	}
//    
//}


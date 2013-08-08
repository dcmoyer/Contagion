#include "grid_world.h"

grid_world::grid_world(){
	
	for(int i = 0; i < RESOLUTION_HEIGHT; i++){
		for(int j = 0; j < RESOLUTION_WIDTH; j++){
			
			the_grid[i][j] = new grid_point;
			the_grid[i][j]->i = i;
			the_grid[i][j]->j = j;
		}
	}
	
	//Setting UP
	for(int i = 1; i < RESOLUTION_HEIGHT; i++){
		
		for(int j = 0; j < RESOLUTION_WIDTH; j++){
			
			the_grid[i][j]->direction[0] = the_grid[i-1][j];
			
		}
	}
	//Setting DOWN
	for(int i = 0; i < (RESOLUTION_HEIGHT - 1); i++){
		
		for(int j = 0; j < RESOLUTION_WIDTH; j++){
			
			the_grid[i][j]->direction[1] = the_grid[i+1][j];
			
		}
	}
	//Setting RIGHT
	for(int i = 0; i < RESOLUTION_HEIGHT; i++){
		
		for(int j = 0; j < (RESOLUTION_WIDTH-1); j++){
			
			the_grid[i][j]->direction[2] = the_grid[i][j+1];
			
		}
	}
	//Setting LEFT
	for(int i = 0; i < RESOLUTION_HEIGHT; i++){
		
		for(int j = 1; j < RESOLUTION_WIDTH; j++){
			
			the_grid[i][j]->direction[3] = the_grid[i][j-1];
			
		}
	}
	
}

grid_world::~grid_world(){
	
	for(int i = 0; i < RESOLUTION_HEIGHT; i++){
		for(int j = 0; j < RESOLUTION_WIDTH; j++){
			
			delete the_grid[i][j];
			
		}
	}
	
	double len = agents_master.size();
	for(int i = 0; i < len; i++){
		delete agents_master[i];
	}
	len = static_agents_master.size();
	for(int i = 0; i < len; i++){
		delete static_agents_master[i];
	}
	
}

void grid_world::initialize_static_field(){
	
	double len = static_agents_master.size();
	double running_max = 0;
	
	for(int k = 0; k < len; k++){
		int i = static_agents_master[k]->get_y_node_pos();
		int j = static_agents_master[k]->get_x_node_pos();
		
		//the_grid[i][j]->value = 100000;
		the_grid[i][j]->impass_flag = true;
	}
	
	for(int i = 0; i < RESOLUTION_HEIGHT; i++){
		for(int j = 0; j < RESOLUTION_WIDTH; j++){
			//if( the_grid[i][j]->impass_flag){
				//continue;
			//}
			the_grid[i][j]->value = 0;
			
			for(int k = 0; k < len; k++){
				double y = ((double)i - static_agents_master[k]->get_y_pos());
				double x = ((double)j - static_agents_master[k]->get_x_pos());
				//std::cout << r << "\n";
				the_grid[i][j]->value += static_agents_master[k]->potential( x , y , static_agents_master[k]);
				if(static_agents_master[k]->velocity_block != NULL && static_agents_master[k]->velocity_block(x,y, static_agents_master[k]) >= 1){
					the_grid[i][j]->impass_flag = true;
				}
				
			}
			
			if( !(the_grid[i][j]->impass_flag) && running_max < the_grid[i][j]->value)
				running_max = the_grid[i][j]->value;
			
		}
	}
	
	global_max = running_max;
	
	//Setting UP
	for(int i = 1; i < RESOLUTION_HEIGHT; i++){
		
		for(int j = 0; j < RESOLUTION_WIDTH; j++){
			
			//the_grid[i][j]->up = the_grid[i-1][j];
			the_grid[i][j]->cost[0] = the_grid[i-1][j]->cost[1] = abs(the_grid[i-1][j]->value - the_grid[i][j]->value);
			
		}
	}
	//Setting LEFT
	for(int i = 0; i < RESOLUTION_HEIGHT; i++){
		
		for(int j = 1; j < RESOLUTION_WIDTH; j++){
			
			//the_grid[i][j]->up = the_grid[i-1][j];
			the_grid[i][j]->cost[2] = the_grid[i][j-1]->cost[3] = abs(the_grid[i][j-1]->value - the_grid[i][j]->value);
			
		}
	}	
}

void grid_world::update_forward_accel(){
	double len = agents_master.size();
	double densities[RESOLUTION_HEIGHT][RESOLUTION_WIDTH] = {};
	
#pragma omp parallel for
	for(int i = 0; i < RESOLUTION_HEIGHT; i++){
		for(int j = 0; j < RESOLUTION_WIDTH; j++){
			if(the_grid[i][j]->impass_flag){
				densities[i][j] = 1;
				continue;
			}
			for(int k = 0; k < len; k++){
				if( !(agents_master[k]->is_alive()) )
					continue;
				double y = ((double)i - agents_master[k]->get_y_node_pos());
				double x = ((double)j - agents_master[k]->get_x_node_pos());
				
				if(agents_master[k]->velocity_block != NULL )
					densities[i][j] += agents_master[k]->velocity_block(x,y,agents_master[k]);
				
				if(densities[i][j] > 1)
					densities[i][j] = 1;
				
				for(int m = 0; m < len; m++){
					double mine = agents_master[k]->get_q_mag();
					double yours = agents_master[m]->get_q_mag();
					
					double dx = agents_master[m]->get_x_coord() - agents_master[k]->get_x_coord();
					double dy = agents_master[m]->get_y_coord() - agents_master[k]->get_y_coord();
					
					
					agents_master[k]->add_to_q_change( (yours - mine) * exp(-(dx*dx) - (dy*dy)) );
					
					double r = sqrt(dx* dx + dy*dy);
					if(r == 0){
						continue;
					}
					agents_master[k]->add_to_y_accel(-.25 * exp(-r/.5) * dy / r );
					agents_master[k]->add_to_x_accel(-.25 * exp(-r/.5) * dx / r );
					
				}
				
			}
			
			
		}
	}
	//std::cout << "LOL";
#pragma omp parallel for
	for(int i = 0; i < len; i++){
		
		bool checks[RESOLUTION_HEIGHT][RESOLUTION_WIDTH] = {};
		//skip dead
		if( !(agents_master[i]->is_alive()) )
			continue;
		
		//kill out of bounds
		grid_agent* target = agents_master[i];  
		int y = target->get_y_node_pos();
		int x = target->get_x_node_pos();
		if(x < 0 ||
			x > RESOLUTION_WIDTH ||
			y < 0 ||
			y > RESOLUTION_HEIGHT || the_grid[y][x]->goal_flag){
			
			target->kill();
			break;
		}
		
		//kill those on the goal
		//NOT IMP.
		
		bool break_flag = false;
		int cardinality = 0;
		int cardinality2 = -1;
		std::priority_queue<edge, std::vector<edge>, edge_comp2 > p_q;
		//std::cout << "Position: " << x << " " << y << "\n";
		checks[y][x] = true;
		
		if(the_grid[y][x]->direction[0] != NULL && !(the_grid[y][x]->goal_flag)){
			p_q.push(edge(the_grid[y][x], //from
				the_grid[y][x]->direction[0],//to
				0,//cardinality
				-1,//cardinality2
				(the_grid[y][x]->direction[0]->value + the_grid[y][x]->value)/2));
			//checks[y+1][x] = true;
		}else if(the_grid[y][x]->goal_flag){
			break_flag = true;
			cardinality = 0;
		}
		
		if(!break_flag && the_grid[y][x]->direction[1] != NULL && !(the_grid[y][x]->goal_flag)){
			p_q.push(edge(the_grid[y][x], //from
				the_grid[y][x]->direction[1],//to
				1,//cardinality
				-1,//cardinality2
				(the_grid[y][x]->direction[1]->value + the_grid[y][x]->value)/2));
			//checks[y-1][x] = true;
		}else if(the_grid[y][x]->goal_flag){
			break_flag = true;
			cardinality = 1;
		}
		
		if(!break_flag && the_grid[y][x]->direction[2] != NULL && !(the_grid[y][x]->goal_flag)){
			p_q.push(edge(the_grid[y][x], //from
				the_grid[y][x]->direction[2],//to
				2,//cardinality
				-1,//cardinality2
				(the_grid[y][x]->direction[2]->value + the_grid[y][x]->value)/2));
			//checks[y][x-1] = true;
		}else if(the_grid[y][x]->goal_flag){
			break_flag = true;
			cardinality = 2;
		}
		
		if(!break_flag && the_grid[y][x]->direction[3] != NULL && !(the_grid[y][x]->goal_flag)){
			p_q.push(edge(the_grid[y][x], //from
				the_grid[y][x]->direction[3],//to
				3,//cardinality
				-1,//cardinality2
				(the_grid[y][x]->direction[3]->value + the_grid[y][x]->value)/2));
			//checks[y][x+1] = true;
		}else if(the_grid[y][x]->goal_flag){
			break_flag = true;
			cardinality = 3;
		}
		
		/*std::cout << (the_grid[y][x]->direction[0]->value + the_grid[y][x]->value)/2 << " " <<
				(the_grid[y][x]->direction[1]->value + the_grid[y][x]->value)/2 << " " << 
				(the_grid[y][x]->direction[2]->value + the_grid[y][x]->value)/2 << " " <<
				(the_grid[y][x]->direction[3]->value + the_grid[y][x]->value)/2 << "\n";*/
		
		edge current_edge;
		grid_point* current_point = NULL;
		grid_point* previous_point = NULL;
		int second_step = 0;
		
		double new_x_acc = 0;
		double new_y_acc = 0;
		double magnitude = 0;
		
		
		target->add_to_q_change(4 * densities[y][x] * the_grid[y][x]->value / global_max);
		//int LL = 0;
		while(!p_q.empty()){
			current_edge = p_q.top();
			//std::cout << current_edge.value << "\n";
			//std::cout << current_edge.from;
			p_q.pop();
			
			//LL++;
			//std::cout << LL; 
			
			current_point = current_edge.to;
			if(checks[current_point->i][current_point->j]){
				continue;
			}
			
			/*int placeholder;
			for(int n = 0; n < RESOLUTION_HEIGHT; n++){
				for(int k = 0; k < RESOLUTION_WIDTH; k++){
					if(checks[n][k])
						std::cout << "x";
					else
						std::cout << " ";
				}
				std::cout << "\n";
			}
			std::cout << current_edge.value << "\n";
			usleep(10000);*/
			
			checks[current_point->i][current_point->j] = true;
			
			previous_point = current_edge.from;
			
			for(int dir = 0; dir < 4; dir++){
				if(current_point->direction[dir] == previous_point || current_point->direction[dir] == NULL)
					continue;
				if(current_point->direction[dir]->goal_flag){
					//std::cout << "Found Goal \n";
					break_flag = true;
					cardinality = current_edge.cardinality;
					cardinality2 = current_edge.cardinality2;
					break;
				}
				
				double added_val = 50 * densities[current_point->i][current_point->j]; //CHANGE THIS LATER. This is where we look out for people. Lol.
				if(second_step > 8){
					p_q.push(edge(current_point,
								current_point->direction[dir],
								current_edge.cardinality,
								current_edge.cardinality2,
								(current_point->direction[dir]->value + current_point->value)/2 + current_edge.value + added_val));
				}else{
					if(current_edge.cardinality2 > 0){
						p_q.push(edge(current_point,
								current_point->direction[dir],
								current_edge.cardinality,
								current_edge.cardinality2,
								(current_point->direction[dir]->value + current_point->value)/2 + current_edge.value + added_val));
					}else{ 
						p_q.push(edge(current_point,
									current_point->direction[dir],
									current_edge.cardinality,
									dir,
									(current_point->direction[dir]->value + current_point->value)/2 + current_edge.value + added_val));
						second_step++;
					}
					
				}
				
			}
			if(break_flag)
				break;
		}
		//std::cout << "(" << cardinality << "," << cardinality2 << ") ";
		
		switch (cardinality){
			case 0:
				new_y_acc = -1;
				break;
			case 1:
				new_y_acc = 1;
				break;
			case 2:
				new_x_acc = 1;
				break;
			case 3:
				new_x_acc = -1;
				break;
			default:
				assert(false);
		}
		
		switch (cardinality2){
			case 0:
				new_y_acc--;
				break;
			case 1:
				new_y_acc++;
				break;
			case 2:
				new_x_acc++;
				break;
			case 3:
				new_x_acc--;
				break;
			case -1:
				break;
			default:
				assert(false);
		}
		
		magnitude = sqrt(new_y_acc*new_y_acc + new_x_acc*new_x_acc);
		new_x_acc = new_x_acc/magnitude;
		new_y_acc = new_y_acc/magnitude;
		
		agents_master[i]->add_to_y_accel(new_y_acc);
		agents_master[i]->add_to_x_accel(new_x_acc);
		
		double proj_x = round(x + agents_master[i]->get_x_veloc_index(0) * STEP_SIZE);
		double proj_y = round(y + agents_master[i]->get_y_veloc_index(0) * STEP_SIZE);
		
		agents_master[i]->set_proj_density(densities[(int) proj_x][(int) proj_y]);
		
		new_x_acc = 0;
		new_y_acc = 0;
		magnitude = 0;
		
		/*if(cardinality < 2)
			agents_master[i]->add_to_y_accel( (-1 * cardinality)  +  (1 * (1 - cardinality)) );
		else
			agents_master[i]->add_to_x_accel( (1 * (cardinality % 2))  +  (-1 * (1 - (cardinality % 2))));*/
		
	}
}

void grid_world::place_fire(double x, double y, double (*p)(double, double, static_agent*), double (* v_s)(double, double, static_agent*) ){
	
	static_agents_master.push_back(new static_agent(x, y, 0, p, v_s));
	
}

void grid_world::place_goal(double x, double y, double (*p)(double, double, static_agent*)){
	
	assert(x >= 0 && x < RESOLUTION_WIDTH && y >= 0 && y < RESOLUTION_HEIGHT);
	static_agents_master.push_back(new static_agent(x,y, 1,p, NULL));
	int i = (int)round(y);
	int j = (int)round(x);
	the_grid[i][j]->goal_flag = true;
	
}

void grid_world::place_agent(double x, double y, double (*p)(double, double, grid_agent*), double (* v_s)(double, double, grid_agent*)){
	
	agents_master.push_back(new grid_agent(x,y,2,p,v_s));
	
}

void grid_world::place_wall(double x, double y, double n_x, double n_y, double length , double (*p)(double, double, static_agent*), double (* v_s)(double, double, static_agent*s)){
	
	static_agents_master.push_back((static_agent*) new static_wall(x, y, 0, n_x, n_y, length, p, v_s ));
	
}

void grid_world::print_csv(std::string filename){
    // Output format is 
    // x y v_x v_y type
    
    std::ofstream out;
    out.open(filename.c_str());
    
    int len = (int) agents_master.size();
    for(int i = 0; i < (len - 1); ++i){
        
        out <<  agents_master[i]->get_x_coord()
            << " " << agents_master[i]->get_y_coord()
            << " " << agents_master[i]->get_x_veloc_index(0)
            << " " << agents_master[i]->get_y_veloc_index(0)
            << " " << agents_master[i]->agent_type
			<< " " << agents_master[i]->get_q_mag()  << "\n";
            
    }
    
    out  << agents_master[len - 1]->get_x_coord()
    << " " << agents_master[len - 1]->get_y_coord()
    << " " << agents_master[len - 1]->get_x_veloc_index(0)
    << " " << agents_master[len - 1]->get_y_veloc_index(0)
    << " " << agents_master[len - 1]->agent_type 
	<< " " << agents_master[len - 1]->get_q_mag() << "\n";
    out.close();

}

void grid_world::print_static_csv(){
    // Output format is 
    // x y v_x v_y type
    
    std::ofstream out;
	std::string file = "static_data.txt";
    out.open(file.c_str());
    
    int len = (int) static_agents_master.size();
    for(int i = 0; i < (len - 1); i++){
        //std::cout << len;
        out <<  static_agents_master[i]->get_x_pos()
            << " " << static_agents_master[i]->get_y_pos()
            << " " << static_agents_master[i]->get_agent_type();
		if(static_agents_master[i]->get_agent_type()){
			out << ((static_wall*)static_agents_master[i])->normal_x <<
				((static_wall*)static_agents_master[i])->normal_y << 
				((static_wall*)static_agents_master[i])->length;
		}
		out << "\n";
    }
    	
    out  << static_agents_master[len - 1]->get_x_pos()
    << " " << static_agents_master[len - 1]->get_y_pos()
    << " " << static_agents_master[len - 1]->get_agent_type() << " ";
	if(static_agents_master[len-1]->get_agent_type()){
		out << ((static_wall*)static_agents_master[len-1])->normal_x << " " <<
			((static_wall*)static_agents_master[len-1])->normal_y << " " <<
			((static_wall*)static_agents_master[len-1])->length;
	}
	out << "\n";
	
    out.close();
}

void grid_world::print_static_wall_csv(){
	
	std::ofstream out;
	std::string file = "static_wall_data.txt";
	out.open(file.c_str());
	
	int len = (int) static_agents_master.size();
	for(int i = 0; i < len ; i++){
		if(static_agents_master[i]->get_agent_type() != 0){
			continue;
		}
		double x = static_agents_master[i]->get_x_pos();
		double y = static_agents_master[i]->get_y_pos();
		
		double n_x = ((static_wall*)static_agents_master[i])->normal_x;
		double n_y = ((static_wall*)static_agents_master[i])->normal_y;
		double len = ((static_wall*)static_agents_master[i])->length;
		
		double side_one_x = x + (-n_y * len);
		double side_one_y = y + (n_x * len);
		
		double side_two_x = x + (n_y * len);
		double side_two_y = y + (-n_x * len);
		
		out << side_one_x << " " << side_one_y << "\n" << side_two_x << " " << side_two_y << "\n\n";
		
	}
	
}

void grid_world::print_field(){
	
	std::ofstream out;
	std::string file = "static_field.txt";
	out.open(file.c_str());
	
	for(int i = 0; i < RESOLUTION_HEIGHT; i++){
		for(int j = 0; j < (RESOLUTION_WIDTH); j++){
			
			//double r = the_grid[i][j]->value / 800.0;
			//double b = 0;
			//double g = 0;
			//double alpha = r;
			
			//out << j << " " << i << " " << (int) (r * 255) << " " << (int) (g*255) << " " << (int) (b*255) << " " << (int) (alpha * 255) << "\n";
			out << j << " " << i << " " << the_grid[i][j]->value << "\n";
		}
		//out << "\n";
		//out << the_grid[i][(RESOLUTION_WIDTH - 1)]->value << "\n";
		
	}
	
	out.close();
	
}

void grid_world::update_agent_pos_euler(){
	double len = agents_master.size();
	for(int i = 0; i < len; i++){
		if(!agents_master[i]->is_alive())
			continue;
		agents_master[i]->drag();
		agents_master[i]->euler_update();
	}
}


void grid_world::update_agent_pos_ab4(){
	double len = agents_master.size();
	for(int i = 0; i < len; i++){
		if(!agents_master[i]->is_alive())
			continue;
		agents_master[i]->drag();
		agents_master[i]->ab4_update();
	}
}

grid_point::grid_point(){
	
	value = 0;
	
	for(int i = 0; i < 4; i++)
		cost[i] = 0; //Up, Down, Left, Right
	for(int i = 0; i < 4; i++)
		direction[i] = 0; //Up, Down, Left, Right
	
	
	goal_flag = false;
	impass_flag = false;
	
}

void grid_point::add_to_value(double v){
	
	value += v;
	
}

void grid_point::set_value(double v){
	
	value = v;
	
}
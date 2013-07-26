#include "grid_world.h"

grid_world::grid_world(){
	
	for(int i = 0; i < RESOLUTION_HEIGHT; i++){
		for(int j = 0; j < RESOLUTION_WIDTH; j++){
			
			the_grid[i][j] = new grid_point;
			
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
			
			the_grid[i][j]->direction[3] = the_grid[i-1][j];
			
		}
	}
	
}

grid_world::~grid_world(){
	
	for(int i = 0; i < RESOLUION_HEIGHT; i++){
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
	
	len = static_agents_master.length();
	
	for(int k = 0; k < len; k++){
		int i = static_agents_master[k]->get_y_node_pos();
		int j = static_agents_master[k]->get_x_node_pos();
		
		the_grid[i][j]->value = 1000000;
		the_grid[i][j]->impass_flag = TRUE;
		
	}
	
	for(double i = 0; i < RESOLUTION_HEIGHT; i++){
		for(double j = 0; j < RESOLUTION_WIDTH; j++){
			if(the_grid[i][j]->impass_flag){
				continue;
			}
			the_grid[i][j]->value = 0;
			
			for(int k = 0; k < len; k++){
				double r = sqrt((i - static_agents_master[k]->get_y_pos())*(i - static_agents_master[k]->get_y_pos()) +
								(j - static_agents_master[k]->get_x_pos())*(j - static_agents_master[k]->get_x_pos()));
				the_grid[i][j]->value += static_agents_master[k]->potential( r );
			}
			
		}
	}
	
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
	len = agents_master.size();
	
	for(int i = 0; i < len; i++){
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
			y > RESOLUTION_HEIGHT){
			
			target->kill();
			
		}
		
		
		std::priority_queue<edge, edge_comp> p_q;
		p_q.push(edge(the_grid[y][x], //from
			the_grid[y][x]->direction[0],//to
			0,//cardinality
			std::abs(the_grid[y][x]->direction[0]->value - the_grid[y][x]->value));
		
		p_q.push(edge(the_grid[y][x], //from
			the_grid[y][x]->direction[1],//to
			1,//cardinality
			std::abs(the_grid[y][x]->direction[1]->value - the_grid[y][x]->value));
		
		p_q.push(edge(the_grid[y][x], //from
			the_grid[y][x]->direction[2],//to
			2,//cardinality
			std::abs(the_grid[y][x]->direction[2]->value - the_grid[y][x]->value));
		
		p_q.push(edge(the_grid[y][x], //from
			the_grid[y][x]->direction[3],//to
			3,//cardinality
			std::abs(the_grid[y][x]->direction[3]->value - the_grid[y][x]->value));
		
		bool break_flag = false;
		edge current_edge;
		grid_point* current_point,previous_point;
		while(!p_q.empty()){
			current_edge = p_q.pop();
			current_point = current_edge.to;
			previous_point = current_edge.from;
			
			for(int i = 0; i < 4; i++){
				if(current_point->direction[i] == previous_point)
					continue;
				if(current_point->direction[i]->goal_flag){
					break_flag = true;
					break;
				}
				
				double added_val = 0; //CHANGE THIS LATER. This is where we look out for people. Lol.
				
				p_q.push(edge(current_point,
							current_point->direction[i],
							current_edge.cardinality,
							std::abs(current_point->direction[i]->value - current_point->value) + added_val));
				
			}
			if(break_flag)
				break;
		}
		
		if(cardinality < 2)
			agents_master[i]->add_to_y_accel( (-1 * cardinality)  +  (1 * (1 - cardinality)) );
		else
			agents_master[i]->add_to_x_accel( (1 * (cardinality % 2))  +  (-1 * (1 - (cardinality % 2))));
		
	}
}

void grid_world::place_fire(double x, double y, double (*p)(double), double (* v_s)(double, double, double, double) ){
	
	static_agents_master.push_back(new static_agent(x, y, 0, p, v_s));
	
}

void grid_world::place_goal(double x, double y, double (*p)(double)){
	
	assert(x >= 0 && x < RESOLUTION_WIDTH && y >= 0 && y < RESOLUTION_HEIGHT);
	static_agents_master.push_back(new static_agent(x,y, 1,p, NULL));
	
	the_grid[round(y)][round(x)]->goal_flag = true;
	
}

void grid_world::place_agent(double x, double y, double (*p)(double), double (* v_s)(double, double, double, double)){
	
	agents_master.push_back(new grid_agent(x,y,2,p,v_s))
	
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
            << " " << agents_master[i]->agent_type << "\n";
            
    }
    
    out  << agents_master[len - 1]->get_x_coord()
    << " " << agents_master[len - 1]->get_y_coord()
    << " " << agents_master[len - 1]->get_x_veloc_index(0)
    << " " << agents_master[len - 1]->get_y_veloc_index(0)
    << " " << agents_master[len - 1]->agent_type << "\n";
    out.close();

}

void grid_world::print_static_csv(){
    // Output format is 
    // x y v_x v_y type
    
    std::ofstream out;
    out.open('static_data.txt');
    
    int len = (int) agents_master.size();
    for(int i = 0; i < (len - 1); ++i){
        
        out <<  agents_master[i]->get_x_coord()
            << " " << agents_master[i]->get_y_coord()
            << " " << agents_master[i]->agent_type << "\n";
            
    }
    
    out  << agents_master[len - 1]->get_x_coord()
    << " " << agents_master[len - 1]->get_y_coord()
    << " " << agents_master[len - 1]->agent_type << "\n";
    out.close();

}

void world::update_agent_pos_euler(){
	double len = agents_master.size();
	for(int i = 0; i < len; i++){
		if(!agents_master[i]->is_alive())
			continue;
		agents_master[i]->drag();
		agents_master[i]->euler_update();
	}
}


void world::update_agent_pos_ab4(){
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
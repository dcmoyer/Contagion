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
			
			the_grid[i][j]->up = the_grid[i-1][j];
			
		}
	}
	//Setting DOWN
	for(int i = 0; i < (RESOLUTION_HEIGHT - 1); i++){
		
		for(int j = 0; j < RESOLUTION_WIDTH; j++){
			
			the_grid[i][j]->down = the_grid[i+1][j];
			
		}
	}
	//Setting RIGHT
	for(int i = 0; i < RESOLUTION_HEIGHT; i++){
		
		for(int j = 0; j < (RESOLUTION_WIDTH-1); j++){
			
			the_grid[i][j]->right = the_grid[i][j+1];
			
		}
	}
	//Setting LEFT
	for(int i = 0; i < RESOLUTION_HEIGHT; i++){
		
		for(int j = 1; j < RESOLUTION_WIDTH; j++){
			
			the_grid[i][j]->left = the_grid[i-1][j];
			
		}
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
			the_grid[i][j]->up_cost = the_grid[i-1][j]->down_cost = abs(the_grid[i-1][j]->value - the_grid[i][j]->value);
			
		}
	}
	//Setting LEFT
	for(int i = 0; i < RESOLUTION_HEIGHT; i++){
		
		for(int j = 1; j < RESOLUTION_WIDTH; j++){
			
			//the_grid[i][j]->up = the_grid[i-1][j];
			the_grid[i][j]->right_cost = the_grid[i][j-1]->left_cost = abs(the_grid[i][j-1]->value - the_grid[i][j]->value);
			
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
		
		//shortest path
		std::set queue<edge, edge_comp>;
		queue.insert(edge(the_grid[y][x], /*from*/
			the_grid[y][x]->up,/*to*/
			the_grid[y][x]->up,/*cardinality*/
			std::abs(the_grid[y][x]->up->value - the_grid[y][x]->value));
		
		queue.insert(edge(the_grid[y][x], /*from*/
			the_grid[y][x]->down,/*to*/
			the_grid[y][x]->down,/*cardinality*/
			std::abs(the_grid[y][x]->down->value - the_grid[y][x]->value));
		
		queue.insert(edge(the_grid[y][x], /*from*/
			the_grid[y][x]->right,/*to*/
			the_grid[y][x]->right,/*cardinality*/
			std::abs(the_grid[y][x]->right->value - the_grid[y][x]->value));
		
		queue.insert(edge(the_grid[y][x], /*from*/
			the_grid[y][x]->left,/*to*/
			the_grid[y][x]->left,/*cardinality*/
			std::abs(the_grid[y][x]->left->value - the_grid[y][x]->value));
		
		while(!queue.empty()){
			
		}
	}
}

grid_point::grid_point(){
	
	value = 0;
	
	up_cost = 0;
	down_cost = 0;
	left_cost = 0;
	right_cost = 0;
	
	up = NULL;
	down = NULL;
	left = NULL;
	right = NULL;
	
	goal_flag = false;
	impass_flag = false;
	
}

void grid_point::add_to_value(double v){
	
	value += v;
	
}

void grid_point::set_value(double v){
	
	value = v;
	
}
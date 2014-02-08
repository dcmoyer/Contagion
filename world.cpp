#include "world.h"


//default constructor
world::world()
{
//create the cells
	for (int i = 0; i < DOMAIN_DIM_1; i++)
    {
		for(int j = 0; j < DOMAIN_DIM_2; j++) 
        {
			cellList[i][j] = new cell;
        }
    }
  
  //tell the cells who their neighbors are
	for (int i = 0; i < DOMAIN_DIM_1; i++)
    {
		for(int j = 0; j < DOMAIN_DIM_2; j++) 
        {
            vector<cell*> v(8);
            v[0] = cellList[i-1][j-1];
            v[1] = cellList[i][j-1];
            v[2] = cellList[i+1][j-1];

            v[3] = cellList[i-1][j];
            v[4] = cellList[i+1][j];

            v[5] = cellList[i-1][j+1];
            v[6] = cellList[i][j+1];
            v[7] = cellList[i+1][j+1];

            if(i == 0)
            {
                v[0]=v[3]=v[5]=NULL;
            }
             if((i+1) == DOMAIN_DIM_1)
            {
                v[2]=v[4]=v[7]=NULL;
            }
            if(j == 0)
            {
                v[0]=v[1]=v[2]=NULL;
            }
             if((j+1) == DOMAIN_DIM_2)
            {
                v[5]=v[6]=v[7]=NULL;
            }
            
            cellList[i][j]->set_neighbors(v);
        }
    }
	theLonelyIsland = new cell;
	death_count = 0;
    
}

//destructor
world::~world()
{    
    for(int i = 0; i < DOMAIN_DIM_1; i++)
	{
        for(int j = 0; j < DOMAIN_DIM_2; j++)
		{
            delete cellList[i][j];
        }
    }
    
	delete theLonelyIsland;
	
	int len = agents_master.size();
	for(int i = 0; i < len ; i++){
		delete agents_master[i];
	}
}

//add agent at position with given model
void world::add_agent(double x, double y, void (* up)(agent*,agent*))
{
	if(x < 0)
		x = 0;
	if(x >= CELL_LENGTH*DOMAIN_DIM_1)
		x = CELL_LENGTH*DOMAIN_DIM_1 - 1;
	if(y < 0)
		y = 0;
	if(y >= CELL_LENGTH*DOMAIN_DIM_2)
		y = CELL_LENGTH*DOMAIN_DIM_2 - 1;

	agents_master.push_back(new agent(x, y, up));
	int i = (int) (x)/CELL_LENGTH;
	int j = (int) (y)/CELL_LENGTH;
	cellList[i][j]->add_top(agents_master.back());
}

//add predator at position with given model
void world::add_predator(double x, double y, void (* up)(agent*,agent*))
{
	
	if(x < 0)
		x = 0;
	if(x >= CELL_LENGTH*DOMAIN_DIM_1)
		x = CELL_LENGTH*DOMAIN_DIM_1 - 1;
	if(y < 0)
		y = 0;
	if(y >= CELL_LENGTH*DOMAIN_DIM_2)
		y = CELL_LENGTH*DOMAIN_DIM_2 - 1;
	agents_master.push_back(new predator(x, y, up));
	int i = (int) (x)/CELL_LENGTH;
	int j = (int) (y)/CELL_LENGTH;
	cellList[i][j]->add_top(agents_master.back());
}

//add finch at position with given model
void world::add_finch_rand(double x, double y, void (* up)(agent*,agent*))
{
	if(x < 0)
		x = 0;
	else if(x >= CELL_LENGTH*DOMAIN_DIM_1)
		x = CELL_LENGTH*DOMAIN_DIM_1 - 1;
	if(y < 0)
		y = 0;
	else if(y >= CELL_LENGTH*DOMAIN_DIM_2)
		y = CELL_LENGTH*DOMAIN_DIM_2 - 1;
	agents_master.push_back(new finch(x, y, up));
	int i = (int) (x)/CELL_LENGTH;
	int j = (int) (y)/CELL_LENGTH;
	cellList[i][j]->add_top(agents_master.back());
}

void world::add_finch(double x, double y, void (* up)(agent*,agent*), unsigned char params[7])
{
	if(x < 0)
		x = 0;
	if(x >= CELL_LENGTH*DOMAIN_DIM_1)
		x = CELL_LENGTH*DOMAIN_DIM_1 - 1;
	if(y < 0)
		y = 0;
	if(y >= CELL_LENGTH*DOMAIN_DIM_2)
		y = CELL_LENGTH*DOMAIN_DIM_2 - 1;
	agents_master.push_back(new finch(x, y, up, params));
	int i = (int) (x)/CELL_LENGTH;
	int j = (int) (y)/CELL_LENGTH;
	cellList[i][j]->add_top(agents_master.back());
}

void world::add_finch2(double x, double y, void (* up)(agent*,agent*), void (* util_up)(double , double , double , double, finch2* ), unsigned char params[7]){
	if(x < 0)
		x = 0;
	if(x >= CELL_LENGTH*DOMAIN_DIM_1)
		x = CELL_LENGTH*DOMAIN_DIM_1 - 1;
	if(y < 0)
		y = 0;
	if(y >= CELL_LENGTH*DOMAIN_DIM_2)
		y = CELL_LENGTH*DOMAIN_DIM_2 - 1;
	agents_master.push_back(new finch2(x, y, up, util_up, params));
	int i = (int) (x)/CELL_LENGTH;
	int j = (int) (y)/CELL_LENGTH;
	cellList[i][j]->add_top(agents_master.back());

}

void world::add_finch2_rand(double x, double y, void (* up)(agent*,agent*), void (* util_up)(double , double , double , double, finch2* )){
	if(x < 0)
		x = 0;
	else if(x >= CELL_LENGTH*DOMAIN_DIM_1)
		x = CELL_LENGTH*DOMAIN_DIM_1 - 1;
	if(y < 0)
		y = 0;
	else if(y >= CELL_LENGTH*DOMAIN_DIM_2)
		y = CELL_LENGTH*DOMAIN_DIM_2 - 1;
	agents_master.push_back(new finch2(x, y, up, util_up));
	int i = (int) (x)/CELL_LENGTH;
	int j = (int) (y)/CELL_LENGTH;
	cellList[i][j]->add_top(agents_master.back());
}

void world::add_wall(double c_x, double c_y, double n_x, double n_y, double len, void (* up)(agent*,agent*)){
  
  if(c_x < 0)
    c_x = 0;
  if(c_x > CELL_LENGTH*DOMAIN_DIM_1)
    c_x = CELL_LENGTH*DOMAIN_DIM_1 - 1;
  if(c_y < 0)
    c_y = 0;
  if(c_y > CELL_LENGTH*DOMAIN_DIM_2)
    c_y = CELL_LENGTH*DOMAIN_DIM_2 - 1;
  
  agents_master.push_back((agent*) new wall(c_x, c_y, n_x, n_y, len, up));
  int i = (int) (c_x)/CELL_LENGTH;
  int j = (int) (c_y)/CELL_LENGTH;
  
  if( i == DOMAIN_DIM_1){
    i--;
  }
  if( j == DOMAIN_DIM_2){
    j--;
  }
  cellList[i][j]->add_top(new cell_node(agents_master.back()));
}

void world::add_boundary(void (* up)(agent*,agent*)){
  
  //Bottom
  for(int i = 0; i < DOMAIN_DIM_1; i++){
    add_wall(i*CELL_LENGTH + (double)CELL_LENGTH/2.0, 0, 0, 1, (double)(CELL_LENGTH/2), up);
  }
  //Top
  double top = DOMAIN_DIM_2 * CELL_LENGTH;
  for(int i = 0; i < DOMAIN_DIM_1; i++){
    add_wall(i*CELL_LENGTH + (double)CELL_LENGTH/2.0, top, 0, -1, (double)(CELL_LENGTH/2), up);
  }
  //Left Side
  for(int i = 0; i < DOMAIN_DIM_2; i++){
    add_wall(0, i*CELL_LENGTH + (double)CELL_LENGTH/2.0, 1, 0, (double)(CELL_LENGTH/2), up);
  }
  //Right Side
  double right = DOMAIN_DIM_1 * CELL_LENGTH;
  for(int i = 0; i < DOMAIN_DIM_2; i++){
    add_wall(right, i*CELL_LENGTH + (double)CELL_LENGTH/2.0, -1, 0, (double)(CELL_LENGTH/2), up);
  }
  
}

//populate with agents at given positions
void world::populate(int n, vector<double>& xpos, vector<double>& ypos, void (* up)(agent*,agent*)) {
	for (int i = 0; i < n; i++) {
	  double x = xpos[i];
		double y = ypos[i];
		add_agent(x, y, up);                   
	}
}

//randomly populate world with n agents using given model
void world::populate_rand(int n, void (* up)(agent*,agent*))
{
	for (int i = 0; i < n; i ++)
		{
			double x, y;
			/*Use this to restrict to the middle*/
			if(DOMAIN_DIM_1 % 2 == 0)
			{
				int padx = DOMAIN_DIM_1 / 2 - 1;
				x = padx*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH*2);
			}
			else 
			{
				int padx = DOMAIN_DIM_1 / 2;
				x = padx*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH);
			}
			if(DOMAIN_DIM_2 % 2 == 0)
			{
				int pady = DOMAIN_DIM_2 / 2 - 1;
				y = pady*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH*2);
			}
			else 
			{
				int pady = DOMAIN_DIM_2 / 2;
				y = pady*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH);
			}


			//double x = (double)rand() / RAND_MAX * (CELL_LENGTH*DOMAIN_DIM_1);
			//double y = (double)rand() / RAND_MAX * (CELL_LENGTH*DOMAIN_DIM_2);
			add_agent(x, y, up);
		}
}

//randomly populate world with n predators using given model
void world::populate_predator_rand(int n, void (* up)(agent*,agent*))
{
  double x, y, temp;
  int x_ring, y_ring;
	for (int i = 0; i < n; i ++)
		{
      
			//double x = (double)rand() / RAND_MAX * (CELL_LENGTH*DOMAIN_DIM_1);
			//double y = (double)rand() / RAND_MAX * (CELL_LENGTH*DOMAIN_DIM_2);
			
			/*Use this to restrict to the middle*/
      
      //Take the edge pieces and line them up.
      //If in first section, it's in the x-ring edge pieces.
      //  (along bottom or top of annulus)
      //If in the next section, flip flop x and y
      //  it's in the y-ring section.
      //  (along left or right of annulus)
      //Final section is corners
      
      x_ring = DOMAIN_DIM_1-2;
      y_ring = DOMAIN_DIM_2-2;
      
      x = rand() % ((x_ring + y_ring + 1)* CELL_LENGTH);
      y = rand() % CELL_LENGTH;
      if(x / CELL_LENGTH  < x_ring){
        x += CELL_LENGTH;
        if(y < CELL_LENGTH/2){
          y += CELL_LENGTH/2;
        }else{
          y += y_ring* CELL_LENGTH + CELL_LENGTH/2;
        }
      } else if ( x / CELL_LENGTH < x_ring + y_ring) {
        temp = y;
        y = x;
        x = temp;
        
        y -= x_ring*CELL_LENGTH;
        y += CELL_LENGTH;
        
        if(x < CELL_LENGTH/2){
          x += CELL_LENGTH/2;
        }else{
          x += x_ring* CELL_LENGTH + CELL_LENGTH/2;
        }
        
      } else{
        x -= (x_ring + y_ring) * CELL_LENGTH;
        if(x < CELL_LENGTH){
          x += CELL_LENGTH/2;
        }else{
          x += x_ring* CELL_LENGTH + CELL_LENGTH/2;
        }
        if(y < CELL_LENGTH){
          y += CELL_LENGTH/2;
        }else{
          y += y_ring* CELL_LENGTH + CELL_LENGTH/2;
        }
        
      }
      std::cout << x << " "<< y << "\n";
			add_predator(x, y, up);
		}
}


void world::populate_finches_rand(int n, void (* up)(agent*,agent*))
{
	for (int i = 0; i < n; i ++)
		{
			//TODO: REWRITE THIS.
			double x, y;
			/*Use this to restrict to the middle*/
			if(DOMAIN_DIM_1 % 2 == 0)
			{
				int padx = DOMAIN_DIM_1 / 2 - 1;
				x = padx*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH*2);
			}
			else 
			{
				int padx = DOMAIN_DIM_1 / 2;
				x = padx*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH);
			}
			if(DOMAIN_DIM_2 % 2 == 0)
			{
				int pady = DOMAIN_DIM_2 / 2 - 1;
				y = pady*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH*2);
			}
			else 
			{
				int pady = DOMAIN_DIM_2 / 2;
				y = pady*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH);
			}
			
			//double x = (double)rand() / RAND_MAX * (CELL_LENGTH*DOMAIN_DIM_1);
			//double y = (double)rand() / RAND_MAX * (CELL_LENGTH*DOMAIN_DIM_2);
			
			add_finch_rand(x, y, up);
		}
}

void world::populate_finches2_rand(int n, void (* up)(agent*, agent*), void (* util_up)(double , double , double , double, finch2* )){
	for (int i = 0; i < n; i ++)
		{
			//TODO: REWRITE THIS.
			double x, y;
			/*Use this to restrict to the middle*/
			if(DOMAIN_DIM_1 % 2 == 0)
			{
				int padx = DOMAIN_DIM_1 / 2 - 1;
				x = padx*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH*2);
			}
			else 
			{
				int padx = DOMAIN_DIM_1 / 2;
				x = padx*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH);
			}
			if(DOMAIN_DIM_2 % 2 == 0)
			{
				int pady = DOMAIN_DIM_2 / 2 - 1;
				y = pady*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH*2);
			}
			else 
			{
				int pady = DOMAIN_DIM_2 / 2;
				y = pady*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH);
			}
			
			//double x = (double)rand() / RAND_MAX * (CELL_LENGTH*DOMAIN_DIM_1);
			//double y = (double)rand() / RAND_MAX * (CELL_LENGTH*DOMAIN_DIM_2);
			
			add_finch2_rand(x, y, up, util_up);
		}
}

void world::populate_finches_std(int n, void (* up)(agent*,agent*))
{
	for (int i = 0; i < n; i ++)
		{
			double x, y;
			/*Use this to restrict to the middle*/
			if(DOMAIN_DIM_1 % 2 == 0)
			{
				int padx = DOMAIN_DIM_1 / 2 - 1;
				x = padx*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH*2);
			}
			else 
			{
				int padx = DOMAIN_DIM_1 / 2;
				x = padx*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH);
			}
			if(DOMAIN_DIM_2 % 2 == 0)
			{
				int pady = DOMAIN_DIM_2 / 2 - 1;
				y = pady*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH*2);
			}
			else 
			{
				int pady = DOMAIN_DIM_2 / 2;
				y = pady*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH);
			}
			
			//double x = (double)rand() / RAND_MAX * (CELL_LENGTH*DOMAIN_DIM_1);
			//double y = (double)rand() / RAND_MAX * (CELL_LENGTH*DOMAIN_DIM_2);
			
			unsigned char params[7];
			params[0] = .45 * 255;
			params[1] = .5 * 255;
			params[2] = .01 * 255;
			params[3] = .6 * 255;
			params[4] = .6 * 255;
			params[5] = .5 * 255;
			params[6] = .5 * 255;

			add_finch(x, y, up, params);
		}
}


void world::run(std::ostream& strm, int print_every, int iterations)
{
	
    time_t t = time(NULL);
	std::cout << 0 << " " << time(NULL) - t << " total seconds elapsed" << "\n";
	print(strm);
	for(int i = 1; i <= 4; i++)
	{
        update_forward_velocs();
		
		update_agent_pos_euler();
		move_to_cell();
		if(i % print_every == 0){
			std::cout << i << " " << time(NULL) - t << " total seconds elapsed" << "\n";
			print(strm);
			
		}
		//w.print(str);
		//w.print(std::cout);
    }

	//solve using AB4
	for(int i = 5; i <= iterations; i++)
	{
		update_forward_velocs();
		update_agent_pos_ab4();
		move_to_cell();
		if(i % print_every == 0){
			std::cout << i << " " << time(NULL) - t << " total seconds elapsed" << "\n";
			print(strm);
		}
		//w.print(str);
		//w.print(std::cout);
	}

}

void world::run_evolution(std::ostream& strm)
{
	int threshold = STUDYSIZE / 2;
  int i;
	for( i = 1; i <= 4; i++)
	{
        update_forward_velocs();
		euler_evolve();
		move_to_cell_evo();
    }

	//solve using AB4
	for(i ; i <= STEPS_PER_GEN; i++)
	{
		update_forward_velocs();
		ab4_evolve();
		move_to_cell_evo();
	}
  
  strm << i << "\n";
}

void world::run_evolution_2(std::ostream& strm)
{
	int threshold = STUDYSIZE / 2;
  int i;
	for( i = 1; i <= 4; i++)
	{
        update_forward_velocs();
		euler_evolve();
		move_to_cell_evo();
        update_utility();
    }

	//solve using AB4
	for(i ; i <= STEPS_PER_GEN; i++)
	{
		update_forward_velocs();
		ab4_evolve();
		move_to_cell_evo();
        update_utility();
	}
  
  strm << i << "\n";
}

// Functions that are helpful for debugging 

// Get cell of index i,j 

cell* world::get_cell(int i, int j) {
	return(cellList[i][j]);
}



// Ask whether cell i,j is empty 
int world::is_empty(int i, int j) 
{
  cell* current_cell = cellList[i][j];
  //std::cout << current_cell << std::endl;
  
  cell_node* current_node = current_cell->get_top();
  
  if(current_node == NULL) 
    {
      //std::cout << "Current node was empty" << std::endl;
      return 1;
    }
  else 
    {
      //std::cout << "Current node not empty" << std::endl;
      return 0;
    }
}



void world::update_forward_velocs(){
	//Iterates through all cells and does pairwise comparisons
    
    cell* origin = cellList[0][0];

	//Same-cell comparison
#pragma omp parallel for
	for(int i = 0; i < DOMAIN_DIM_1; i++){
		for(int j = 0; j < DOMAIN_DIM_2; j++){
			
			cell_node_iterator target = cellList[i][j]->get_iter();
			cell_node_iterator target2 = cellList[i][j]-> get_iter();
			for(target; target.current != NULL; target.next()){
				
				for(target2; target2.current != NULL; target2.next()){
					if(target2.current == target.current)
						break;
					
					agent* agent_brown = target.current->get_agent();
					agent* agent_jones = target2.current->get_agent();

					agent_brown->update(agent_brown, agent_jones);
					agent_jones->update(agent_jones, agent_brown);
					//Do comparisons each way, since update rules might be different
				}
				target2.reset_current();
			}    
		}
	}
	
	//Compare to cell to the right
#pragma omp parallel for
    for(int i = 0; i < DOMAIN_DIM_1; i++){
        for(int j = 0; j < DOMAIN_DIM_2; j++){
        
            if( cellList[i][j]->get_neighbor(4) == NULL )
                           continue;
        
            cell_node_iterator target = cellList[i][j]->get_iter();
            cell_node_iterator right = cellList[i][j]->get_neighbor(4) -> get_iter();
            
            for(target; target.current != NULL; target.next()){
                
                for(right; right.current != NULL; right.next()){
                    
					agent* agent_brown = target.current->get_agent();
					agent* agent_jones = right.current->get_agent();

					agent_brown->update(agent_brown, agent_jones);
					agent_jones->update(agent_jones, agent_brown);

                   /* target.current->get_agent()->update(target.current->get_agent(), right.current->get_agent());
                    right.current->get_agent()->update(right.current->get_agent(), target.current->get_agent());*/
                    
                }
                
                right.reset_current();
                
            }    
        
        }
    }
    
	//Compare to cell below
#pragma omp parallel for
    for(int i = 0; i < DOMAIN_DIM_1; i++){
        for(int j = 0; j < DOMAIN_DIM_2; j++){
            
            if(cellList[i][j]->get_neighbor(6) == NULL)
                continue;
            
            cell_node_iterator target = cellList[i][j]->get_iter();
            cell_node_iterator upwards = cellList[i][j]->get_neighbor(6) -> get_iter();
            
            for(target; target.current != NULL; target.next()){
                
                for(upwards; upwards.current != NULL; upwards.next()){
                    
					agent* agent_brown = target.current->get_agent();
					agent* agent_jones = upwards.current->get_agent();

					agent_brown->update(agent_brown, agent_jones);
					agent_jones->update(agent_jones, agent_brown);

                 /*   target.current->get_agent()->update(target.current->get_agent(), upwards.current->get_agent());
                    upwards.current->get_agent()->update(upwards.current->get_agent(), target.current->get_agent());*/
                    
                    
                }
                
                upwards.reset_current();
                
            }
        }
    }
	//Compare to cell to the bottomn right
#pragma omp parallel for
    for(int i = 0; i < DOMAIN_DIM_1; i++){
        for(int j = 0; j < DOMAIN_DIM_2; j++){
            
            if(cellList[i][j]->get_neighbor(7) == NULL)
                continue;
            
            cell_node_iterator target = cellList[i][j]->get_iter();
            cell_node_iterator upwards = cellList[i][j]->get_neighbor(7) -> get_iter();
            
            for(target; target.current != NULL; target.next()){
                
                for(upwards; upwards.current != NULL; upwards.next()){
                    
					agent* agent_brown = target.current->get_agent();
					agent* agent_jones = upwards.current->get_agent();

					agent_brown->update(agent_brown, agent_jones);
					agent_jones->update(agent_jones, agent_brown);

                   /* target.current->get_agent()->update(target.current->get_agent(), upwards.current->get_agent());
                   upwards.current->get_agent()->update(upwards.current->get_agent(), target.current->get_agent());*/
                    
                }
                
                upwards.reset_current();
            }
        }
    }


	//Compare to cell to the bottom left
#pragma omp parallel for
    for(int i = 0; i < DOMAIN_DIM_1; i++){
        for(int j = 0; j < DOMAIN_DIM_2; j++){
            
            if(cellList[i][j]->get_neighbor(5) == NULL)
                continue;
            
            cell_node_iterator target = cellList[i][j]->get_iter();
            cell_node_iterator upwards = cellList[i][j]->get_neighbor(5) -> get_iter();
            
            for(target; target.current != NULL; target.next()){
                
                for(upwards; upwards.current != NULL; upwards.next()){
                    
					 
					agent* agent_brown = target.current->get_agent();
					agent* agent_jones = upwards.current->get_agent();

					agent_brown->update(agent_brown, agent_jones);
					agent_jones->update(agent_jones, agent_brown);
					
					/*

                    target.current->get_agent()->update(target.current->get_agent(), upwards.current->get_agent());
                    upwards.current->get_agent()->update(upwards.current->get_agent(), target.current->get_agent());*/
                    
                }
                
                upwards.reset_current();
            }
        }
    }
}

void world::update_agent_pos_euler(){

    for(int i = 0; i < DOMAIN_DIM_1; i++){
        for(int j = 0; j < DOMAIN_DIM_2; j++){
            cell_node_iterator target = cellList[i][j]->get_iter();
            for(target; target.current != NULL; target.next()){
				agent* agent_smith = target.current->get_agent();

                if (agent_smith->is_alive()) {
                   agent_smith->normalize_accel();
					agent_smith->drag();
                    agent_smith->euler_update();
                } else {
                    agent_smith->set_x_coord(-1);
					agent_smith->set_y_coord(-1);
				}
			}
		}
	}
    
}


void world::update_agent_pos_ab4(){

  for(int i = 0; i < DOMAIN_DIM_1; i++){
	for(int j = 0; j < DOMAIN_DIM_2; j++){
		cell_node_iterator target = cellList[i][j]->get_iter();
		for(target; target.current != NULL; target.next()){

			agent* agent_smith = target.current->get_agent();
			if (agent_smith->is_alive()) {
				agent_smith->normalize_accel();
				agent_smith->drag();
				agent_smith->ab4_update();
			} else {
				agent_smith->set_x_coord(-1);
				agent_smith->set_y_coord(-1);
				}
			}
		}
	}
  
}

void world::euler_evolve(){

    for(int i = 0; i < DOMAIN_DIM_1; i++){
        for(int j = 0; j < DOMAIN_DIM_2; j++){
            cell_node_iterator target = cellList[i][j]->get_iter();
            for(target; target.current != NULL; target.next()){
				agent* agent_smith = target.current->get_agent();

                if (agent_smith->is_alive()) {
                   agent_smith->normalize_accel();
					agent_smith->drag();
                    agent_smith->euler_update();
                } else {
                    agent_smith->set_x_coord(-1);
					agent_smith->set_y_coord(-1);
				}
			}
		}
	}
    
}


void world::ab4_evolve()
{

  for(int i = 0; i < DOMAIN_DIM_1; i++)
  {
	for(int j = 0; j < DOMAIN_DIM_2; j++)
	{
		cell_node_iterator target = cellList[i][j]->get_iter();
		for(target; target.current != NULL; target.next())
		{
			agent* agent_smith = target.current->get_agent();
			if (agent_smith->is_alive()) {
				agent_smith->normalize_accel();
				agent_smith->drag();
				agent_smith->ab4_update();
			} else {
				agent_smith->set_x_coord(-1);
				agent_smith->set_y_coord(-1);
				
			}
		}
	  }
	}
  
}

void world::move_to_cell() {
	/*Sorry for hijacking this for evolution stuff, you may want to revert it if you 
	don't want the alerts. I will be using move_to_cel_evo instead. (Doug) */
	for (int i = 0; i < DOMAIN_DIM_1; i++) {
		for (int j = 0; j < DOMAIN_DIM_2; j++) {
			cell* current_cell = cellList[i][j];
			cell_node* current_node = current_cell->get_top();
			cell_node* prev = NULL;
			while (current_node != NULL) {
				agent* current_agent = current_node->get_agent();
				if(!(current_agent->is_alive())) {
					
					cell_node* temp = current_node->get_next();
				
					current_cell->extract_node_and_add(current_node, theLonelyIsland);
					death_count++;
					std::cout << "\n death count is  "<<  death_count << "\n";
				
					current_node = temp;
					continue;
				}
				int x = current_agent->cell_num_dim1();
				int y = current_agent->cell_num_dim2();
				if ( (current_agent->get_type() != 2) && (x != i || y != j)) {
					if (prev == NULL) {
						current_node = current_cell->remove_top();
					} else {
						prev->set_next(current_node->get_next());
						current_node->set_next(NULL);
					}
					if(x < 0 || x >= DOMAIN_DIM_1 || y < 0 || y >= DOMAIN_DIM_2){
						
						//current_agent->move_inside(x,y);
						current_agent->kill();
						
						theLonelyIsland->add_top(current_node);
						death_count++;
						std::cout << "\n out of bounds kill \n";
						std::cout << "\n death count is  "<<  death_count << "\n";
					}
					else{
						cellList[x][y]->add_top(current_node);
					}
					if(prev == NULL){
						current_node = current_cell->get_top();
					} else {
						current_node = prev->get_next();
					}
				} else {
					prev = current_node;
					current_node = current_node->get_next();
				}
			}
		}
	}
}


void world::move_to_cell_evo() {
	for (int i = 0; i < DOMAIN_DIM_1; i++) {
		for (int j = 0; j < DOMAIN_DIM_2; j++) {
			cell* current_cell = cellList[i][j];
			cell_node* current_node = current_cell->get_top();
			cell_node* prev = NULL;
			while (current_node != NULL) {
				agent* current_agent = current_node->get_agent();
				if(!(current_agent->alive)) {
					
					cell_node* temp = current_node->get_next();
				
					current_cell->extract_node_and_add(current_node, theLonelyIsland);
					death_count++;
					//std::cout << "\n death count is  "<<  death_count << " lemme check the pop \n";
				
					int ams = agents_master.size();
					int count = 0;
					for(int i = 0; i < ams; i++) 
					{
						if (agents_master[i]->get_type() == 0 && agents_master[i]->is_alive()) 
						{								
							count++;
						}
					}
					std::cout << "Remaining population: " << count << " \n";

                    if(count == 0){
                        exit(1);
                    }
					current_node = temp;
					continue;
				}
				int x = current_agent->cell_num_dim1();
				int y = current_agent->cell_num_dim2();
				if ( (current_agent->get_type() != 2) && (x != i || y != j)) {
					if (prev == NULL) {
						current_node = current_cell->remove_top();
					} else {
						prev->set_next(current_node->get_next());
						current_node->set_next(NULL);
					}
					if(x < 0 || x >= DOMAIN_DIM_1 || y < 0 || y >= DOMAIN_DIM_2){
						
						//current_agent->move_inside(x,y);
						current_agent->kill();
						
						theLonelyIsland->add_top(current_node);
						if (current_agent->get_type() == 0)
						{
							death_count++;
							std::cout << "Out of bounds kill, THIS IS BAD \n";
							int ams = agents_master.size();
							int count = 0;
							for(int i = 0; i < ams; i++) 
							{
								if (agents_master[i]->get_type() == 0 && agents_master[i]->is_alive()) 
								{								
									count++;
								}
							}
							std::cout << "Remaining population: " << count << " \n";
						}
						else
              {
							std::cout << "\n predator out of bounds, THIS IS BAD \n";
							
						}
					}
					else{
						cellList[x][y]->add_top(current_node);
					}
					if(prev == NULL){
						current_node = current_cell->get_top();
					} else {
						current_node = prev->get_next();
					}
				} else {
					prev = current_node;
					current_node = current_node->get_next();
				}
			}
		}
	}
}

void world::update_utility(){
    int ams = agents_master.size();
    double x=0;
    double y=0;
    double v_x = 0;
    double v_y = 0;
    for(int i = 0; i < ams; i++){
        if(agents_master[i]->get_type() == 0){
            x += agents_master[i]->get_x_coord();
            y += agents_master[i]->get_y_coord();
            v_x += agents_master[i]->get_x_veloc_index(0);
            v_y += agents_master[i]->get_y_veloc_index(0);
        }
    }
    x = x/STUDYSIZE;
    y = y/STUDYSIZE;
    
    v_x = v_x/STUDYSIZE;
    v_y = v_y/STUDYSIZE;
    
    for(int i = 0; i < ams; i++){
        if(agents_master[i]->get_type() == 0){
            ((finch2*) agents_master[i])-> util_update(x,y,v_x,v_y,(finch2*)agents_master[i]);
        }
    }
    
}

void world::print(std::ostream& strm)
{
	for (size_t  i = 0; i < agents_master.size(); i++)
		{
			if(agents_master[i]->alive)
			{
			strm<< agents_master[i]->get_heading() << "," << (*agents_master[i]).get_x_coord() 
		      <<"," << (*agents_master[i]).get_y_coord() 
		      <<"," << agents_master[i]->agent_type 
		      << "," << (*agents_master[i]).get_q_mag() 
		      << ",";
			}
			
			else
			{
				strm << 0 << "," << -100
		      <<"," << -100
		      <<"," << 0
		      << "," << 0
		      << ",";
			}
		}
	strm << "\n";
}

void world::print_csv(std::string filename){
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


void world::repopulate1(void (* up)(agent*,agent*), std::ostream& gen_out) 
{
	//TODO: use cell_node delete function (maybe)?
	// Delete old cells
	for(int i = 0; i < DOMAIN_DIM_1; i++){
		for(int j = 0; j < DOMAIN_DIM_2; j++){
			delete cellList[i][j];
		}
	}
	    
	delete theLonelyIsland;
	
	//create new cells
	for (int i = 0; i < DOMAIN_DIM_1; i++)
    {
		for(int j = 0; j < DOMAIN_DIM_2; j++) 
        {
			cellList[i][j] = new cell;
        }
    }

	for (int i = 0; i < DOMAIN_DIM_1; i++)
    {
		for(int j = 0; j < DOMAIN_DIM_2; j++) 
        {
            vector<cell*> v(8);
            v[0] = cellList[i-1][j-1];
            v[1] = cellList[i][j-1];
            v[2] = cellList[i+1][j-1];

            v[3] = cellList[i-1][j];
            v[4] = cellList[i+1][j];

            v[5] = cellList[i-1][j+1];
            v[6] = cellList[i][j+1];
            v[7] = cellList[i+1][j+1];

            if(i == 0)
            {
                v[0]=v[3]=v[5]=NULL;
            }
             if((i+1) == DOMAIN_DIM_1)
            {
                v[2]=v[4]=v[7]=NULL;
            }
            if(j == 0)
            {
                v[0]=v[1]=v[2]=NULL;
            }
             if((j+1) == DOMAIN_DIM_2)
            {
                v[5]=v[6]=v[7]=NULL;
            }
            
            cellList[i][j]->set_neighbors(v);
        }
    }
	theLonelyIsland = new cell;
	death_count = 0;
		

	// Copy the values
	unsigned char oldparams [STUDYSIZE][9];

	int ams = agents_master.size();
	int count = 0;
	for(int i = 0; i < ams; i++) 
	{
		if (agents_master[i]->get_type() == 0 && agents_master[i]->is_alive()) 
		{
			count++;
			finch* current = (finch*) agents_master[i];
			for (int j = 0; j < 9; j++) 
			{
				int x = current->params[j];
				oldparams[count-1][j] = x;
				gen_out << x  << ", ";
			}
			gen_out << "\n";
		}
	}
		
	// Delete all the agents
	for(int i = 0; i < ams; i++) 
	{
		delete agents_master[i];
	}
	
	agents_master.clear();
	
	
	//Shuffle, determine pairs

	//Mating
	for(int i = 0; i < STUDYSIZE - count; i++)
	{	
		int dad = rand()% count;
		int mom = rand()% count;

		int crosspoint = rand()%10;
		
		for(int j = 0; j < crosspoint; j++)
			{
				oldparams[i+count][j] = oldparams[dad][j];
			}

		for(int k = crosspoint; k < 9; k++)
			{
				oldparams[i+count][k] = oldparams[mom][k];
			}
	}


	//mutate
	for(int i = 0; i < STUDYSIZE; i++)
	{	
			//this will choose which genes mutate with chance (1/2)^5
			unsigned short x = rand()% 512;
			unsigned short y = rand()% 512;
			unsigned short z = rand()% 512;
			unsigned short a = rand()% 512;
			unsigned short b = rand()% 512;
			unsigned short M = x & y & z & a & b;

			for(int j = 0; j < 9; j++)
			{
				if(M & (1u << j))
				{
					unsigned short N = rand()% 8;
					oldparams[i][j] ^=  ( 1u << N);
				}
			}
	}

	
	for(int i  = 0; i < STUDYSIZE; i++)
	{
		//generate random (x,y) position
		double x, y;
		if(DOMAIN_DIM_1 % 2 == 0)
		{
			int padx = DOMAIN_DIM_1 / 2 - 1;
			x = padx*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH*2);
		}
		else 
		{
			int padx = DOMAIN_DIM_1 / 2;
			x = padx*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH);
		}
		if(DOMAIN_DIM_2 % 2 == 0)
		{
			int pady = DOMAIN_DIM_2 / 2 - 1;
			y = pady*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH*2);
		}
		else 
		{
			int pady = DOMAIN_DIM_2 / 2;
			y = pady*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH);
		}
		
		//funky business with arrays, can reduce?
		unsigned char genes[9];
		for(int z = 0; z < 9; z++)
		{
			genes[z] = oldparams[i][z];
		}

		add_finch(x, y, up, genes);
	}

}

void world::repopulate2(void (* up)(agent*,agent*), std::ostream& strm) 
{
	std::cout << "Now repopulating, death count is " << death_count;
	// Delete old cells
	for(int i = 0; i < DOMAIN_DIM_1; i++){
		for(int j = 0; j < DOMAIN_DIM_2; j++){
			delete cellList[i][j];
		}
	}
	    
	delete theLonelyIsland;
	
	// Create new cells
	for (int i = 0; i < DOMAIN_DIM_1; i++) 
	{
		for(int j = 0; j < DOMAIN_DIM_2; j++) 
		{
			cellList[i][j] = new cell;
	    }
	}
	  

	//tell the cells who their neighbors are
	for (int i = 0; i < DOMAIN_DIM_1; i++)
	{
		for(int j = 0; j < DOMAIN_DIM_2; j++) 
		{
			
			vector<cell*> v(8);
			v[0] = cellList[i-1][j-1];
			v[1] = cellList[i][j-1];
			v[2] = cellList[i+1][j-1];

			v[3] = cellList[i-1][j];
			v[4] = cellList[i+1][j];
			
			v[5] = cellList[i-1][j+1];
			v[6] = cellList[i][j+1];
			v[7] = cellList[i+1][j+1];

			if(i == 0)
			{
				v[0]=v[3]=v[5]=NULL;
	        }
			if((i+1) == DOMAIN_DIM_1)
			{
				v[2]=v[4]=v[7]=NULL;
			}
			if(j == 0)
			{
				v[0]=v[1]=v[2]=NULL;
			}
			if((j+1) == DOMAIN_DIM_2)
			{
				v[5]=v[6]=v[7]=NULL;
			}
	            
			cellList[i][j]->set_neighbors(v);
		}
	}
	theLonelyIsland = new cell;
		
	// Copy the values
	char parameter [5][7];
	int ams = agents_master.size();
	int count = 0;
	for(int i = 0; i < ams; i++) 
	{
		if (agents_master[i]->get_type() == 0 && agents_master[i]->is_alive()) 
		{
			count++;
			std::cout << "count is " << count;
			finch* current = (finch*) agents_master[i];
			for (int j = 0; j < 7; j++) 
			{
				parameter[count-1][j] = (*current).params[j];
			}
		}
	}
		
	// Delete all the agents
	for(int i = 0; i < agents_master.size(); i++) {
		delete agents_master[i];
	}
	
	agents_master.clear();
	death_count = 0;

	//Repopulate!
	populate_finches_std(10, up);


}

bool sort_func(agent* left, agent* right){ 
    return ((finch2*) left) -> util < ((finch2*) right) -> util;
}

void world::repopulate_CS_util(void (* up)(agent*, agent*), void (* util_up)(double , double , double , double, finch2* ), std::ostream& gen_out){
    
	for(int i = 0; i < DOMAIN_DIM_1; i++){
		for(int j = 0; j < DOMAIN_DIM_2; j++){
			delete cellList[i][j];
		}
	}
	    
	delete theLonelyIsland;
	
	//create new cells
	for (int i = 0; i < DOMAIN_DIM_1; i++)
    {
		for(int j = 0; j < DOMAIN_DIM_2; j++) 
        {
			cellList[i][j] = new cell;
        }
    }

	for (int i = 0; i < DOMAIN_DIM_1; i++)
    {
		for(int j = 0; j < DOMAIN_DIM_2; j++) 
        {
            vector<cell*> v(8);
            v[0] = cellList[i-1][j-1];
            v[1] = cellList[i][j-1];
            v[2] = cellList[i+1][j-1];

            v[3] = cellList[i-1][j];
            v[4] = cellList[i+1][j];

            v[5] = cellList[i-1][j+1];
            v[6] = cellList[i][j+1];
            v[7] = cellList[i+1][j+1];

            if(i == 0)
            {
                v[0]=v[3]=v[5]=NULL;
            }
             if((i+1) == DOMAIN_DIM_1)
            {
                v[2]=v[4]=v[7]=NULL;
            }
            if(j == 0)
            {
                v[0]=v[1]=v[2]=NULL;
            }
             if((j+1) == DOMAIN_DIM_2)
            {
                v[5]=v[6]=v[7]=NULL;
            }
            
            cellList[i][j]->set_neighbors(v);
        }
    }
	theLonelyIsland = new cell;
    
    int ams = agents_master.size();
    unsigned char oldparams [STUDYSIZE][9];
    
    for(int i = 0; i < ams; i++){
        if(agents_master[i]->get_type() != 0){
            delete agents_master[i];
            agents_master.erase(agents_master.begin() + i);
            i--;
            ams--;
        }
    }
    
    int SS_over2 = STUDYSIZE/2;
    if(agents_master.size() == SS_over2){
        exit(1);
    }
    
    std::sort(agents_master.begin(), agents_master.end(), sort_func);
    
    for(int i = 0; i < SS_over2; i++){
		finch2* current = (finch2*) agents_master[i];
        int x = 0;
		for (int j = 0; j < 9; j++) 
		{
			x = current->params[j];
			oldparams[i][j] = x;
			gen_out << x << ", ";
		}
		x = current->util;
		gen_out << x;
        
		gen_out << "\n";
    }
    
	for(int i = 0; i < STUDYSIZE; i++) 
	{
		delete agents_master[i];
	}
	
	agents_master.clear();
	
	
	//Shuffle, determine pairs

	//Mating
	for(int i = 0; i < SS_over2; i++)
    {	
		int dad = rand()% SS_over2;
		int mom = rand()% SS_over2;

		int crosspoint = rand()%10;
		
		for(int j = 0; j < crosspoint; j++)
		{
			oldparams[i+SS_over2][j] = oldparams[dad][j];
		}

		for(int k = crosspoint; k < 9; k++)
		{
			oldparams[i+SS_over2][k] = oldparams[mom][k];
		}
	}


	//mutate
	for(int i = 0; i < STUDYSIZE; i++)
	{	
			//this will choose which genes mutate with chance (1/2)^5
			unsigned short x = rand()% 512;
			unsigned short y = rand()% 512;
			unsigned short z = rand()% 512;
			unsigned short a = rand()% 512;
			unsigned short b = rand()% 512;
			unsigned short M = x & y & z & a & b;

			for(int j = 0; j < 9; j++)
			{
				if(M & (1u << j))
				{
					unsigned short N = rand()% 8;
					oldparams[i][j] ^=  ( 1u << N);
				}
			}
	}

	
	for(int i  = 0; i < STUDYSIZE; i++)
	{
		//generate random (x,y) position
		double x, y;
		if(DOMAIN_DIM_1 % 2 == 0)
		{
			int padx = DOMAIN_DIM_1 / 2 - 1;
			x = padx*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH*2);
		}
		else 
		{
			int padx = DOMAIN_DIM_1 / 2;
			x = padx*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH);
		}
		if(DOMAIN_DIM_2 % 2 == 0)
		{
			int pady = DOMAIN_DIM_2 / 2 - 1;
			y = pady*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH*2);
		}
		else 
		{
			int pady = DOMAIN_DIM_2 / 2;
			y = pady*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH);
		}
		
		//funky business with arrays, can reduce?
		unsigned char genes[9];
		for(int z = 0; z < 9; z++)
		{
			genes[z] = oldparams[i][z];
		}

		add_finch2(x, y, up, util_up, genes);
	}
    
}

void world::repopulate_prob(void (* up)(agent*, agent*), std::ostream& gen_out){
	//TODO: use cell_node delete function (maybe)?
	// Delete old cells
	for(int i = 0; i < DOMAIN_DIM_1; i++){
		for(int j = 0; j < DOMAIN_DIM_2; j++){
			delete cellList[i][j];
		}
	}
	    
	delete theLonelyIsland;
	
	//create new cells
	for (int i = 0; i < DOMAIN_DIM_1; i++)
    {
		for(int j = 0; j < DOMAIN_DIM_2; j++) 
        {
			cellList[i][j] = new cell;
        }
    }

	for (int i = 0; i < DOMAIN_DIM_1; i++)
    {
		for(int j = 0; j < DOMAIN_DIM_2; j++) 
        {
            vector<cell*> v(8);
            v[0] = cellList[i-1][j-1];
            v[1] = cellList[i][j-1];
            v[2] = cellList[i+1][j-1];

            v[3] = cellList[i-1][j];
            v[4] = cellList[i+1][j];

            v[5] = cellList[i-1][j+1];
            v[6] = cellList[i][j+1];
            v[7] = cellList[i+1][j+1];

            if(i == 0)
            {
                v[0]=v[3]=v[5]=NULL;
            }
             if((i+1) == DOMAIN_DIM_1)
            {
                v[2]=v[4]=v[7]=NULL;
            }
            if(j == 0)
            {
                v[0]=v[1]=v[2]=NULL;
            }
             if((j+1) == DOMAIN_DIM_2)
            {
                v[5]=v[6]=v[7]=NULL;
            }
            
            cellList[i][j]->set_neighbors(v);
        }
    }
	theLonelyIsland = new cell;
	death_count = 0;
		

	// Copy the values
	unsigned char oldparams [STUDYSIZE][9];

	int ams = agents_master.size();
	int count = 0;
	for(int i = 0; i < ams; i++) 
	{
		if (agents_master[i]->get_type() == 0 && agents_master[i]->is_alive()) 
		{
			count++;
			finch* current = (finch*) agents_master[i];
			for (int j = 0; j < 9; j++) 
			{
				int x = current->params[j];
				oldparams[count-1][j] = x;
				gen_out << x  << ", ";
			}
			gen_out << "\n";
		}
	}
		
	// Delete all the agents
	for(int i = 0; i < ams; i++) 
	{
		delete agents_master[i];
	}
	
	agents_master.clear();
	
    evo_prob(oldparams, count);
    
	for(int i  = 0; i < STUDYSIZE; i++)
	{
		//generate random (x,y) position
		double x, y;
		if(DOMAIN_DIM_1 % 2 == 0)
		{
			int padx = DOMAIN_DIM_1 / 2 - 1;
			x = padx*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH*2);
		}
		else 
		{
			int padx = DOMAIN_DIM_1 / 2;
			x = padx*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH);
		}
		if(DOMAIN_DIM_2 % 2 == 0)
		{
			int pady = DOMAIN_DIM_2 / 2 - 1;
			y = pady*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH*2);
		}
		else 
		{
			int pady = DOMAIN_DIM_2 / 2;
			y = pady*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH);
		}
		
		//funky business with arrays, can reduce?
		unsigned char genes[9];
		for(int z = 0; z < 9; z++)
		{
			genes[z] = oldparams[i][z];
		}

		add_finch(x, y, up, genes);
	}
    
}

void world::repopulate_CS_util_prob(void (* up)(agent*, agent*), void (* util_up)(double , double , double , double, finch2* ), std::ostream& gen_out){
    
	for(int i = 0; i < DOMAIN_DIM_1; i++){
		for(int j = 0; j < DOMAIN_DIM_2; j++){
			delete cellList[i][j];
		}
	}
	    
	delete theLonelyIsland;
	
	//create new cells
	for (int i = 0; i < DOMAIN_DIM_1; i++)
    {
		for(int j = 0; j < DOMAIN_DIM_2; j++) 
        {
			cellList[i][j] = new cell;
        }
    }

	for (int i = 0; i < DOMAIN_DIM_1; i++)
    {
		for(int j = 0; j < DOMAIN_DIM_2; j++) 
        {
            vector<cell*> v(8);
            v[0] = cellList[i-1][j-1];
            v[1] = cellList[i][j-1];
            v[2] = cellList[i+1][j-1];

            v[3] = cellList[i-1][j];
            v[4] = cellList[i+1][j];

            v[5] = cellList[i-1][j+1];
            v[6] = cellList[i][j+1];
            v[7] = cellList[i+1][j+1];

            if(i == 0)
            {
                v[0]=v[3]=v[5]=NULL;
            }
             if((i+1) == DOMAIN_DIM_1)
            {
                v[2]=v[4]=v[7]=NULL;
            }
            if(j == 0)
            {
                v[0]=v[1]=v[2]=NULL;
            }
             if((j+1) == DOMAIN_DIM_2)
            {
                v[5]=v[6]=v[7]=NULL;
            }
            
            cellList[i][j]->set_neighbors(v);
        }
    }
	theLonelyIsland = new cell;
    
    int ams = agents_master.size();
    unsigned char oldparams [STUDYSIZE][9];
    
    for(int i = 0; i < ams; i++){
        if(agents_master[i]->get_type() != 0){
            delete agents_master[i];
            agents_master.erase(agents_master.begin() + i);
            i--;
            ams--;
        }
    }
    
    int SS_over2 = STUDYSIZE/2;
    if(agents_master.size() == SS_over2){
        exit(1);
    }
    
    std::sort(agents_master.begin(), agents_master.end(), sort_func);
    
    for(int i = 0; i < SS_over2; i++){
		finch2* current = (finch2*) agents_master[i];
        int x = 0;
		for (int j = 0; j < 9; j++) 
		{
			x = current->params[j];
			oldparams[i][j] = x;
			gen_out << x << ", ";
		}
		x = current->util;
		gen_out << x;
        
		gen_out << "\n";
    }
    
	for(int i = 0; i < STUDYSIZE; i++) 
	{
		delete agents_master[i];
	}
	
	agents_master.clear();
    
    evo_prob(oldparams, SS_over2);

    for(int i  = 0; i < STUDYSIZE; i++)
    {
    	//generate random (x,y) position
    	double x, y;
    	if(DOMAIN_DIM_1 % 2 == 0)
    	{
    		int padx = DOMAIN_DIM_1 / 2 - 1;
    		x = padx*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH*2);
    	}
    	else 
    	{
    		int padx = DOMAIN_DIM_1 / 2;
    		x = padx*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH);
    	}
    	if(DOMAIN_DIM_2 % 2 == 0)
    	{
    		int pady = DOMAIN_DIM_2 / 2 - 1;
    		y = pady*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH*2);
    	}
    	else 
    	{
    		int pady = DOMAIN_DIM_2 / 2;
    		y = pady*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH);
    	}
	
    	//funky business with arrays, can reduce?
    	unsigned char genes[9];
    	for(int z = 0; z < 9; z++)
    	{
    		genes[z] = oldparams[i][z];
    	}

    	add_finch2(x, y, up, util_up, genes);
    }
    
}

void world::print_parameter(std::ostream& strm)
{
	for (size_t  i = 0; i < agents_master.size(); i++)
		{
			if(agents_master[i]->is_alive() && agents_master[i]->get_type() == 0)
			{
				finch* current = (finch*) agents_master[i];
			strm << (*current).params[0] << " " 
			<< (*current).params[1] << " " 
			<< (*current).params[2] << " " 
			<< (*current).params[3] << " " 
			<< (*current).params[4] << " " 
			<< (*current).params[5] << " " 
			<< (*current).params[6] << " ";
			} else {
				strm << 0 << " " 
				<< 0 << " " 
				<< 0 << " " 
				<< 0 << " " 
				<< 0 << " " 
				<< 0 << " " 
				<< 0 << " "; 
			}
		}
	strm << "\n";
}

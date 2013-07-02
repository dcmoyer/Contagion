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
				
            std::vector<cell*> v(8);
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
            else if((i+1) == DOMAIN_DIM_1)
            {
                v[2]=v[4]=v[7]=NULL;
            }
            if(j == 0)
            {
                v[0]=v[1]=v[2]=NULL;
            }
            else if((j+1) == DOMAIN_DIM_2)
            {
                v[5]=v[6]=v[7]=NULL;
            }
            
            cellList[i][j]->set_neighbors(v);
        }
    }
    
    
}

world::~world(){
    
    for(int i = 0; i < DOMAIN_DIM_1; i++){
        for(int j = 0; j < DOMAIN_DIM_2; j++){
            delete cellList[i][j];
        }
    }
    
}


/*
 
 Hey everyone, so this function is really confusing. I'm sorry, but I've built it
 such that we can easily switch to OPEN MP. However, that makes life kinda terrible
 for reading things. Sorry -DM
 
 */
void world::update_forward_velocs(){
    
    cell* origin = cellList[0][0];
    cell* end = origin + (DOMAIN_DIM_1 * DOMAIN_DIM_3);
    
    for(int i = 0; i < DOMAIN_DIM_1; i++){
        for(int j = 0; j < DOMAIN_DIM_2; j++){
            
            cell_node_iterator target = cellList[i][j]->get_iter();
            cell_node_iterator target2 = cellList[i][j]-> get_iter();
            
            for(target; target.current != NULL; target.next()){
                
                for(right; right.current != NULL; right.next()){
                    if(right.current == target.current)
                        break;
                    
                    target.current->get_agent()->update(target.current->get_agent(), right.current->get_agent());
                    right.current->get_agent()->update(right.current->get_agent(), target.current->get_agent());
                    
                }
                
                right.reset_current();
                
            }    
            
        }
    }
    
    /*
     THIS IS WHERE WE'D PUT OPEN MP
     */
    //UPDATE RIGHT
    /*
    for(cell* iter = origin; iter < end; iter++)
    {
        
        if(iter->get_neighbor(4) == NULL)
            continue;
        
        cell_node_iterator target = iter->get_iter();
        cell_node_iterator right = iter->get_neighbor(4) -> get_iter();
        
        for(target; target.current != NULL; target.next()){
            
            for(right; right.current != NULL; right.next()){
                
                target.current->get_agent()->update(target.current->get_agent(), right.current->get_agent());
                right.current->get_agent()->update(right.current->get_agent(), target.current->get_agent());

            }
            
            right.reset_current();
            
        }
        
    }*/
    
    for(int i = 0; i < DOMAIN_DIM_1; i++){
        for(int j = 0; j < DOMAIN_DIM_2; j++){
        
            if( cellList[i][j]->get_neighbor(4) == NULL )
                           continue;
        
            cell_node_iterator target = cellList[i][j]->get_iter();
            cell_node_iterator right = cellList[i][j]->get_neighbor(4) -> get_iter();
            
            for(target; target.current != NULL; target.next()){
                
                for(right; right.current != NULL; right.next()){
                    
                    target.current->get_agent()->update(target.current->get_agent(), right.current->get_agent());
                    right.current->get_agent()->update(right.current->get_agent(), target.current->get_agent());
                    
                }
                
                right.reset_current();
                
            }    
        
        }
    }
    
    //UPDATE UP
    /*
    end = origin + (DOMAIN_DIM_1);
    for(cell* iter = origin; iter < end; iter++)
    {
        
        for(cell* inner_iter = iter; inner_iter < end; inner_iter += DOMAIN_DIM_1){
            if(inner_iter->get_neighbor(6) == NULL)
                continue;
        
            cell_node_iterator target = inner_iter->get_iter();
            cell_node_iterator upwards = inner_iter->get_neighbor(6) -> get_iter();
            
            for(target; target.current != NULL; target.next()){
            
                for(upwards; upwards.current != NULL; upwards.next()){
                    
                    target.current->get_agent()->update(target.current->get_agent(), upwards.current->get_agent());
                    upwards.current->get_agent()->update(upwards.current->get_agent(), target.current->get_agent());

                
                }
            
                upwards.reset_current();
            
            }
        }
    }*/
    
    for(int i = 0; i < DOMAIN_DIM_1; i++){
        for(int j = 0; j < DOMAIN_DIM_2; j++){
            
            if(cellList[i][j]->get_neighbor(6) == NULL)
                continue;
            
            cell_node_iterator target = cellList[i][j]->get_iter();
            cell_node_iterator upwards = cellList[i][j]->get_neighbor(6) -> get_iter();
            
            for(target; target.current != NULL; target.next()){
                
                for(upwards; upwards.current != NULL; upwards.next()){
                    
                    target.current->get_agent()->update(target.current->get_agent(), upwards.current->get_agent());
                    upwards.current->get_agent()->update(upwards.current->get_agent(), target.current->get_agent());
                    
                    
                }
                
                upwards.reset_current();
                
            }
        }
    }
    
    
    /*
    //UPDATE Right DIAG
    //along first dimension
    for(int off_diag = 0; off_diag < DOMAIN_DIM_1; off_diag++)
    {
        cell* current = origin + off_diag;
        int runs = DOMAIN_DIM_1 - off_diag;
        for(int i = 0; i < runs; i++){
            if(current->get_neighbor(7) == NULL)
                continue;
            
            cell_node_iterator target = current->get_iter();
            cell_node_iterator upwards = current->get_neighbor(7) -> get_iter();
            
            for(target; target.current != NULL; target.next()){
                
                for(upwards; upwards.current != NULL; upwards.next()){
                    
                    target.current->get_agent()->update(target.current->get_agent(), upwards.current->get_agent());
                    upwards.current->get_agent()->update(upwards.current->get_agent(), target.current->get_agent());
                    
                }
                
                upwards.reset_current();
            }
            current += DOMAIN_DIM_1 + 1;
        }
    }
    //intermedius along second dimension
    for(int intermedius = 1; intermedius <= DOMAIN_DIM_2 - DOMAIN_DIM_1; intermedius++){
        cell* current = origin + (intermedius * DOMAIN_DIM_1);
        int runs = DOMAIN_DIM_1;
        for(int i = 0; i < runs; i++){
            if(current->get_neighbor(7) == NULL)
                continue;
            
            cell_node_iterator target = current->get_iter();
            cell_node_iterator upwards = current->get_neighbor(7) -> get_iter();
            
            for(target; target.current != NULL; target.next()){
                
                for(upwards; upwards.current != NULL; upwards.next()){
                    
                    target.current->get_agent()->update(target.current->get_agent(), upwards.current->get_agent());
                    upwards.current->get_agent()->update(upwards.current->get_agent(), target.current->get_agent());
                    
                }
                
                upwards.reset_current();
            }
            current += DOMAIN_DIM_1 + 1;
        }
    }
    //along second dimension
    for(int off_diag = DOMAIN_DIM_2 - DOMAIN_DIM_1 + 1; off_diag < DOMAIN_DIM_2; off_diag++)
    {
        cell* current = origin + (off_diag * DOMAIN_DIM_1);
        int runs = DOMAIN_DIM_2 - off_diag;
        for(int i = 0; i < runs; i++){
            if(current->get_neighbor(7) == NULL)
                continue;
            
            cell_node_iterator target = current->get_iter();
            cell_node_iterator upwards = current->get_neighbor(7) -> get_iter();
            
            for(target; target.current != NULL; target.next()){
                
                for(upwards; upwards.current != NULL; upwards.next()){
                    
                    target.current->get_agent()->update(target.current->get_agent(), upwards.current->get_agent());
                    upwards.current->get_agent()->update(upwards.current->get_agent(), target.current->get_agent());
                    
                }
                
                upwards.reset_current();
            }
            current += DOMAIN_DIM_1 + 1;
        }
    }
     */
    for(int i = 0; i < DOMAIN_DIM_1; i++){
        for(int j = 0; j < DOMAIN_DIM_2; j++){
            
            if(cellList[i][j]->get_neighbor(7) == NULL)
                continue;
            
            cell_node_iterator target = cellList[i][j]->get_iter();
            cell_node_iterator upwards = cellList[i][j]->get_neighbor(7) -> get_iter();
            
            for(target; target.current != NULL; target.next()){
                
                for(upwards; upwards.current != NULL; upwards.next()){
                    
                    target.current->get_agent()->update(target.current->get_agent(), upwards.current->get_agent());
                    upwards.current->get_agent()->update(upwards.current->get_agent(), target.current->get_agent());
                    
                }
                
                upwards.reset_current();
            }
        }
    }
    /*
    //UPDATE Left DIAG
    //Along Dim 1
    for(int off_diag = 0; off_diag < DOMAIN_DIM_1; off_diag++)
    {
        cell* current = origin + off_diag;
        int runs = off_diag;
        for(int i = 0; i < runs; i++){
            if(current->get_neighbor(5) == NULL)
                continue;
            
            cell_node_iterator target = current->get_iter();
            cell_node_iterator upwards = current->get_neighbor(5) -> get_iter();
            
            for(target; target.current != NULL; target.next()){
                
                for(upwards; upwards.current != NULL; upwards.next()){
                    
                    target.current->get_agent()->update(target.current->get_agent(), upwards.current->get_agent());
                    upwards.current->get_agent()->update(upwards.current->get_agent(), target.current->get_agent());
                    
                }
                
                upwards.reset_current();
                
            }
            current += DOMAIN_DIM_1 - 1;
        }
    }
    //intermedius along second dimension
    for(int intermedius = 1; intermedius <= DOMAIN_DIM_2 - DOMAIN_DIM_1; intermedius++){
        cell* current = end - 1 + (intermedius * DOMAIN_DIM_1);
        int runs = DOMAIN_DIM_1;
        for(int i = 0; i < runs; i++){
            if(current->get_neighbor(5) == NULL)
                continue;
            
            cell_node_iterator target = current->get_iter();
            cell_node_iterator upwards = current->get_neighbor(5) -> get_iter();
            
            for(target; target.current != NULL; target.next()){
                
                for(upwards; upwards.current != NULL; upwards.next()){
                    
                    target.current->get_agent()->update(target.current->get_agent(), upwards.current->get_agent());
                    upwards.current->get_agent()->update(upwards.current->get_agent(), target.current->get_agent());
                    
                }
                
                upwards.reset_current();
            }
            current += DOMAIN_DIM_1 - 1;
        }
    }
    
    for(int off_diag = DOMAIN_DIM_2 - DOMAIN_DIM_1 + 1; off_diag < DOMAIN_DIM_2; off_diag++)
    {
        cell* current = end - 1 + (off_diag * DOMAIN_DIM_1); //Remember the reassignment of end.
        int runs = DOMAIN_DIM_2 - off_diag;
        for(int i = 0; i < runs; i++){
            if(current->get_neighbor(5) == NULL)
                continue;
            
            cell_node_iterator target = current->get_iter();
            cell_node_iterator upwards = current->get_neighbor(5) -> get_iter();
            
            for(target; target.current != NULL; target.next()){
                
                for(upwards; upwards.current != NULL; upwards.next()){
                    
                    target.current->get_agent()->update(target.current->get_agent(), upwards.current->get_agent());
                    upwards.current->get_agent()->update(upwards.current->get_agent(), target.current->get_agent());
                    
                }
                
                upwards.reset_current();
                
            }
            current += DOMAIN_DIM_1 - 1;
        }
    }
     */
    for(int i = 0; i < DOMAIN_DIM_1; i++){
        for(int j = 0; j < DOMAIN_DIM_2; j++){
            
            if(cellList[i][j]->get_neighbor(5) == NULL)
                continue;
            
            cell_node_iterator target = cellList[i][j]->get_iter();
            cell_node_iterator upwards = cellList[i][j]->get_neighbor(5) -> get_iter();
            
            for(target; target.current != NULL; target.next()){
                
                for(upwards; upwards.current != NULL; upwards.next()){
                    
                    target.current->get_agent()->update(target.current->get_agent(), upwards.current->get_agent());
                    upwards.current->get_agent()->update(upwards.current->get_agent(), target.current->get_agent());
                    
                }
                
                upwards.reset_current();
            }
        }
    }
    
    /*
    //DRAG TERM; Also should contain division by Nearest Neighbor Count.
    origin = cellList[0][0];
    end = origin + (DOMAIN_DIM_1 * DOMAIN_DIM_3);
    for(cell* iter = origin; iter < end; iter++){
        cell_node_iterator target = iter->get_iter();
        for(target; target.current != NULL; target.next()){
            
    //        target.current->get_agent()->drag();
            
        }
    }
    */
    
    
    
}

void world::update_agent_pos(){
    cell* origin = cellList[0][0];
    cell* end = origin + (DOMAIN_DIM_1 * DOMAIN_DIM_3);
    for(cell* iter = origin; iter < end; iter++){
        cell_node_iterator target = iter->get_iter();
        for(target; target.current != NULL; target.next()){
            
            target.current->get_agent()->drag();
            target.current->get_agent()->ab4_update();
            //target.current->get_agent()->
            // change to new cell if appropriate
            // change "switch flag"
        }
    }
    
    
}

//use ab4 to update the positions of all agents
void world::refresh_ab4()
{
		for (int i = 0; i < NUM_OF_AGENTS; i ++)
		{
			(*agents_master[i]).ab4_update();
		}
    
}

//use euler to update positions when not enough points for ab4
void world::refresh_eul()
{
		for (int i = 0; i < NUM_OF_AGENTS; i ++)
		{
			(*agents_master[i]).euler_update();
		}
}


void world::print(std::ostream& strm)
{
	for (size_t  i = 0; i < agents_master.size(); i++)
		{
			strm<< 0 << "," << (*agents_master[i]).get_x_coord() 
				<<"," << (*agents_master[i]).get_y_coord() <<"," << (*agents_master[i]).get_z_coord() << "," << (*agents_master[i]).get_q_mag() << ",";
		}
	strm << "\n";
}

void world::add_agent()
{
	double v[HIST_LENGTH];
	for(int i = 0; i < HIST_LENGTH; i++)
		v[i] = 0;
	agents_master.push_back(new agent(0, 0, v, v));
	int x =(int) ((*agents_master.back()).get_x_coord())/CELL_LENGTH;
	int y = (int) ((*agents_master.back()).get_y_coord())/CELL_LENGTH;
	cellList[x][y]->add_top(new cell_node(agents_master.back()));
}

void world::add_agent(double x, double y)
{
	if(x < 0)
		x = 0;
	if(x >= CELL_LENGTH*DOMAIN_DIM_1)
		x = CELL_LENGTH*DOMAIN_DIM_1 - 1;
	if(y < 0)
		y = 0;
	if(y >= CELL_LENGTH*DOMAIN_DIM_2)
		y = CELL_LENGTH*DOMAIN_DIM_2 - 1;



	double v[HIST_LENGTH];
	for(int i = 0; i < HIST_LENGTH; i++)
		v[i] = 0;
	agents_master.push_back(new agent(x, y, v, v));
	int i = (int) (x)/CELL_LENGTH;
	int j = (int) (y)/CELL_LENGTH;
	cellList[i][j]->add_top(new cell_node(agents_master.back()));
}
	
void world::add_agent(double x, double y, double z, void (* up)(agent*,agent*))
{
	if(x < 0)
		x = 0;
	if(x >= CELL_LENGTH*DOMAIN_DIM_1)
		x = CELL_LENGTH*DOMAIN_DIM_1 - 1;
	if(y < 0)
		y = 0;
	if(y >= CELL_LENGTH*DOMAIN_DIM_2)
		y = CELL_LENGTH*DOMAIN_DIM_2 - 1;
	if(z < 0)
		z = 0;
	if(z >= CELL_LENGTH*DOMAIN_DIM_2)
		z = CELL_LENGTH*DOMAIN_DIM_2 - 1;

	double v[HIST_LENGTH];
	for(int i = 0; i < HIST_LENGTH; i++)
		v[i] = 0;
	agents_master.push_back(new agent(x, y, z, v, v, v, 0, 'a',  up)); //?!?!?!
	int i = (int) (x)/CELL_LENGTH;
	int j = (int) (y)/CELL_LENGTH;
	cellList[i][j]->add_top(new cell_node(agents_master[i]));
}

void world::populate()
{
	for (int i = 0; i < NUM_OF_AGENTS; i ++)
		{
			add_agent();
		}
}

void world::populate_rand()
{
	for (int i = 0; i < NUM_OF_AGENTS; i ++)
		{
			double x = rand() % (CELL_LENGTH*DOMAIN_DIM_1 ) - 1;
			double y = rand() % (CELL_LENGTH*DOMAIN_DIM_2 ) - 1;
			//double z = rand() % (CELL_LENGTH*DOMAIN_DIM_3 ) - 1;
			add_agent(x, y);
		}
}

void world::populate(int n)
{
	for (int i = 0; i < n; i ++)
		{
			add_agent();
		}
}

void world::populate_rand(int n)
{
	for (int i = 0; i < n; i ++)
		{
			double x = rand() % (CELL_LENGTH*DOMAIN_DIM_1 ) - 1;
			double y = rand() % (CELL_LENGTH*DOMAIN_DIM_2 ) - 1;
			//double z = rand() % (CELL_LENGTH*DOMAIN_DIM_3 ) - 1;
			add_agent(x, y);
		}
}

void world::move_to_cell() {
	for (int i = 0; i < DOMAIN_DIM_1; i++) {
		for (int j = 0; j < DOMAIN_DIM_2; i++) {
			cell* current_cell = cellList[i][j];
			cell_node* current_node = current_cell->get_top();
			cell_node* prev = NULL;
			while (current_node != NULL) {
				agent* current_agent = current_node->get_agent();
				if (!current_cell->in_the_cell(*current_agent)) {
					if (prev == NULL) {
						current_node = current_cell->remove_top();
					} else {
						prev->set_next(current_node->get_next());
						current_node->set_next(NULL);
					}
					int x = current_node->get_agent()->cell_num_dim1();
					int y = current_node->get_agent()->cell_num_dim2();
					cellList[x][y]->add_top(current_node);
					current_node = prev->get_next();
				} else {
					prev = current_node;
					current_node = current_node->get_next();
				}
			}
		}
	}
}

#include "world.h"


//default constructor
world::world()
{
	//create the agents
	for (int i = 0; i < NUM_OF_AGENTS; i ++)
		{
			agents_master[i] = new agent();
		}
	
	//create the cells
	for (int i = 0; i < DOMAIN_DIM_1; i++)
		{
			for(int j = 0; j < DOMAIN_DIM_2); 
			//cellList[i][j] = cell(vector<agents*> &agents);
		}


	//tell the cells who their neighbors are
	 //void set_neighbors(vector<cell*> );
}


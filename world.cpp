#include "world.h"


//default constructor
world::world()
{
//create the cells
	for (int i = 0; i < DOMAIN_DIM_1; i++)
		{
			for(int j = 0; j < DOMAIN_DIM_2); 
			{
				cellList[i][j] = cell();
			}
		}

//create the agents and add agents to the cells
	for (int i = 0; i < NUM_OF_AGENTS; i ++)
		{
			agents_master[i] = new agent();
			int x = ((*agents_master[i]).get_x_coord())/CELL_LENGTH;
			int y = ((*agents_master[i]).get_y_coord())/CELL_LENGTH;
			cellList[x][y].add_top(cell_node(agents_master[i]));
		}
	

//tell the cells who their neighbors are
	for (int i = 0; i < DOMAIN_DIM_1; i++)
		{
			for(int j = 0; j < DOMAIN_DIM_2); 
			{
				//messy, please help (doug)
				vector<cell*> v(8);
				v(0) = &cellList[i-1][j-1];
				v(1) = &cellList[i][j-1];
				v(2) = &cellList[i+1][j-1];

				v(3) = &cellList[i-1][j];
				v(4) = &cellList[i+1][j];

				v(5) = &cellList[i-1][j+1];
				v(6) = &cellList[i][j+1];
				v(7) = &cellList[i+1][j+1];

				if(i == 0)
				{
					v(0)=v(3)=v(5)=NULL;
				}
				else if((i+1) == DOMAIN_DIM_1)
				{
					v(2)=v(4)=v(7)=NULL;
				}

				if(j == 0)
				{
					v(0)=v(1)=v(2)=NULL;
				}
				else if((j+1) == DOMAIN_DIM_2)
				{
					v(5)=v(6)=v(7)=NULL;
				}

				cellList[i][j].set_neighbors(v);
			}
		}
}


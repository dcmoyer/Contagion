#include "world.h"

//default constructor
world::world()
{
//create the cells
	for (int i = 0; i < DOMAIN_DIM_1; i++)
		{
			for(int j = 0; j < DOMAIN_DIM_2; j++) 
			{
				cellList[i][j] = cell();
			}
		}


//tell the cells who their neighbors are
	for (int i = 0; i < DOMAIN_DIM_1; i++)
		{
			for(int j = 0; j < DOMAIN_DIM_2; j++) 
			{
				
				std::vector<cell*> v(8);
				v[0] = &cellList[i-1][j-1];
				v[1] = &cellList[i][j-1];
				v[2] = &cellList[i+1][j-1];

				v[3] = &cellList[i-1][j];
				v[4] = &cellList[i+1][j];

				v[5] = &cellList[i-1][j+1];
				v[6] = &cellList[i][j+1];
				v[7] = &cellList[i+1][j+1];

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

				cellList[i][j].set_neighbors(v);
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
				<<"," << (*agents_master[i]).get_y_coord() <<"," << (*agents_master[i]).get_z_coord() << ",";
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
	cellList[x][y].add_top(new cell_node(agents_master.back()));
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
	cellList[i][j].add_top(new cell_node(agents_master.back()));
}
	
void world::add_agent(double x, double y, double z, double (* up)(agent*,agent*))
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
	agents_master.push_back(new agent(x, y, z, v, v, v, 0, v, 'a',  up)); //?!?!?!
	int i = (int) (x)/CELL_LENGTH;
	int j = (int) (y)/CELL_LENGTH;
	cellList[i][j].add_top(new cell_node(agents_master[i]));
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
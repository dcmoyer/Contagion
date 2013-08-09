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

world::world(void (* up1)(agent*,agent*), void (* up)(agent*,agent*))
{
//Pacman maze world generator. 


//create the cells
	for (int i = 0; i < 18; i++)
    {
		for(int j = 0; j < 9; j++) 
        {
			cellList[i][j] = new cell(i,j);
        }
    }
  
	theLonelyIsland = new cell;
	death_count = 0;

//empty some cells
	for(int j = 1; j <= 3; j++)
	{
		cellList[1][j]->phantom_zone = true;
		cellList[16][j]->phantom_zone = true;
	}

	for(int j = 5; j <= 7; j++)
	{
		cellList[1][j]->phantom_zone = true;
		cellList[16][j]->phantom_zone = true;
	}

	cellList[2][1]->phantom_zone = true;
	cellList[2][7]->phantom_zone = true;
	cellList[15][1]->phantom_zone = true;
	cellList[15][7]->phantom_zone = true;

	for(int j = 0; j <= 1; j++)
	{
		cellList[4][j]->phantom_zone = true;
		cellList[13][j]->phantom_zone = true;
	}

	for(int j = 7; j <= 8; j++)
	{
		cellList[4][j]->phantom_zone = true;
		cellList[13][j]->phantom_zone = true;
	}


	for(int i = 3; i <= 4; i++)
	{
		cellList[i][3]->phantom_zone = true;
		cellList[i][5]->phantom_zone = true;
	}


	for(int i = 13; i <= 14; i++)
	{
		cellList[i][3]->phantom_zone = true;
		cellList[i][5]->phantom_zone = true;
	}



	for(int i = 6; i <= 11; i++)
	{
		cellList[i][1]->phantom_zone = true;
		cellList[i][7]->phantom_zone = true;
		for(int j = 3; j <= 5; j++)
		{
			cellList[i][j]->phantom_zone = true;
		}
	}

	//set neighbors
	for (int i = 0; i < 18; i++)
    {
		for(int j = 0; j < 9; j++) 
        {

			if(!(cellList[i][j]->phantom_zone))
			{
            vector<cell*> v;
			


			if(j >= 1 )
			{
				v.push_back(cellList[i][j-1]);
				if(!(cellList[i][j-1]->phantom_zone))
				{
				if(j >= 2 && !(cellList[i][j-2]->phantom_zone))
				{
					v.push_back(cellList[i][j-2]);
					if(j >= 3 && !(cellList[i][j-3]->phantom_zone))
						{
							v.push_back(cellList[i][j-3]);
						}
				}
				}
				else
					{
				//add bottom wall 
				add_wall(i*CELL_LENGTH + (double)CELL_LENGTH/2.0, (j) * CELL_LENGTH +1, 0, 1, (double)(CELL_LENGTH/2)+10, up1);
			}
			
			}

            else
			{
				//add bottom wall 
				add_wall(i*CELL_LENGTH + (double)CELL_LENGTH/2.0, (j) * CELL_LENGTH +1, 0, 1, (double)(CELL_LENGTH/2)+10, up1);
			}





			if(j < 8 )
			{
				v.push_back(cellList[i][j+1]);
				if( !(cellList[i][j+1]->phantom_zone))
				{
				if(j <7 && !(cellList[i][j+2]->phantom_zone))
				{
					v.push_back(cellList[i][j+2]);
					if(j <6 && !(cellList[i][j+3]->phantom_zone))
						{
							v.push_back(cellList[i][j+3]);
						}
				}
				}
				else
			{
				
				//add top wall 
				add_wall(i*CELL_LENGTH + (double)CELL_LENGTH/2.0, (j+1) * CELL_LENGTH - 1, 0, -1, (double)(CELL_LENGTH/2)+10 , up1);
			}

			}
			else
			{
				
				//add top wall 
				add_wall(i*CELL_LENGTH + (double)CELL_LENGTH/2.0, (j+1) * CELL_LENGTH - 1, 0, -1, (double)(CELL_LENGTH/2)+10 , up1);
			}



			if(i >= 1)
			{
				v.push_back(cellList[i-1][j]);
				if(  !(cellList[i-1][j]->phantom_zone))
				{

				if(i >= 2 && !(cellList[i-2][j]->phantom_zone))
				{
					v.push_back(cellList[i-2][j]);
					if(i >= 3 && !(cellList[i-3][j]->phantom_zone))
						{
							v.push_back(cellList[i-3][j]);
						}
				}
				}
				else
			{
				//add left wall 
				add_wall(i*CELL_LENGTH + 1, (j) * CELL_LENGTH + (double)CELL_LENGTH / 2.0 , 1, 0, (double)(CELL_LENGTH/2)+5 , up1);
			}

			}
			else
			{
				//add left wall 
				add_wall(i*CELL_LENGTH + 1, (j) * CELL_LENGTH + (double)CELL_LENGTH / 2.0 , 1, 0, (double)(CELL_LENGTH/2)+5 , up1);
			}

			if(i < 17 )
			{
				v.push_back(cellList[i+1][j]);
				if( !(cellList[i+1][j]->phantom_zone))
				{
				if(i <16 && !(cellList[i+2][j]->phantom_zone))
				{
					v.push_back(cellList[i+2][j]);
					if(i < 15 && !(cellList[i+3][j]->phantom_zone))
						{
							v.push_back(cellList[i+3][j]);
						}
				}
				}
				else
			{
				//add right wall 
				add_wall((i+1)*CELL_LENGTH - 1, (j) * CELL_LENGTH + (double)CELL_LENGTH / 2.0, -1, 0, (double)(CELL_LENGTH/2) +5, up1);
			}

			}
			else
			{
				//add right wall 
				add_wall((i+1)*CELL_LENGTH - 1, (j) * CELL_LENGTH + (double)CELL_LENGTH / 2.0, -1, 0, (double)(CELL_LENGTH/2) +5, up1);
			}


			if( i >= 1 && j >= 1/* && !(cellList[i-1][j-1]->phantom_zone)*/)
			{
				v.push_back(cellList[i-1][j-1]);
			}
			
			if( i >= 1 && j < 8 /*&& !(cellList[i-1][j+1]->phantom_zone)*/)
			{
				v.push_back(cellList[i-1][j+1]);
			}

			
			if( i < 17 && j >= 1 /*&& !(cellList[i+1][j-1]->phantom_zone)*/)
			{
				v.push_back(cellList[i+1][j-1]);
			}

			
			if( i < 17 && j < 8 /*&& !(cellList[i+1][j+1]->phantom_zone)*/)
			{
				v.push_back(cellList[i+1][j+1]);
			}

            cellList[i][j]->set_neighbors(v);
			}


			///// else this is a phantom cell
			else
			{
				
			/*	vector<cell*> v(8);
			
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
            
            cellList[i][j]->set_neighbors(v);*/


            vector<cell*> v;
			


			if(j >= 1 && !(cellList[i][j-1]->phantom_zone))
			{
				v.push_back(cellList[i][j-1]);
				if(j >= 2 && !(cellList[i][j-2]->phantom_zone))
				{
					v.push_back(cellList[i][j-2]);
					if(j >= 3 && !(cellList[i][j-3]->phantom_zone))
						{
							v.push_back(cellList[i][j-3]);
						}
				}
			}
         





			if(j < 8 && !(cellList[i][j+1]->phantom_zone))
			{
				v.push_back(cellList[i][j+1]);
				if(j <7 && !(cellList[i][j+2]->phantom_zone))
				{
					v.push_back(cellList[i][j+2]);
					if(j <6 && !(cellList[i][j+3]->phantom_zone))
						{
							v.push_back(cellList[i][j+3]);
						}
				}
			}
		



			if(i >= 1 && !(cellList[i-1][j]->phantom_zone))
			{
				v.push_back(cellList[i-1][j]);
				if(i >= 2 && !(cellList[i-2][j]->phantom_zone))
				{
					v.push_back(cellList[i-2][j]);
					if(i >= 3 && !(cellList[i-3][j]->phantom_zone))
						{
							v.push_back(cellList[i-3][j]);
						}
				}
			}
		

			if(i < 17 && !(cellList[i+1][j]->phantom_zone))
			{
				v.push_back(cellList[i+1][j]);
				if(i <16 && !(cellList[i+2][j]->phantom_zone))
				{
					v.push_back(cellList[i+2][j]);
					if(i < 15 && !(cellList[i+3][j]->phantom_zone))
						{
							v.push_back(cellList[i+3][j]);
						}
				}
			}
			

			if( i >= 1 && j >= 1/* && !(cellList[i-1][j-1]->phantom_zone)*/)
			{
				v.push_back(cellList[i-1][j-1]);
			}
			
			if( i >= 1 && j < 8 /*&& !(cellList[i-1][j+1]->phantom_zone)*/)
			{
				v.push_back(cellList[i-1][j+1]);
			}

			
			if( i < 17 && j >= 1 /*&& !(cellList[i+1][j-1]->phantom_zone)*/)
			{
				v.push_back(cellList[i+1][j-1]);
			}

			
			if( i < 17 && j < 8 /*&& !(cellList[i+1][j+1]->phantom_zone)*/)
			{
				v.push_back(cellList[i+1][j+1]);
			}

            cellList[i][j]->set_neighbors(v);
			}
			}

			
			
        }

		



		
    

/*add_wall(51,49, -1, -1, 16, up);
add_wall(51,249, -1, -1, 16, up);
add_wall(149,149, -1, -1, 16, up);
add_wall(149,249, -1, -1, 16, up);
add_wall(199,349, -1, -1, 16, up);
add_wall(299,49, -1, -1, 16, up);
add_wall(299,149, -1, -1, 16, up);
add_wall(299,349, -1, -1, 16, up);
add_wall(649,149, -1, -1, 16, up);
add_wall(649,249, -1, -1, 16, up);
add_wall(649,349, -1, -1, 16, up);
add_wall(749,49, -1, -1, 16, up);
add_wall(749,349, -1, -1, 16, up);
add_wall(799,249, -1, -1, 16, up);*/

	//add corner walls
add_wall(52,52, -1, -1, 16, up);
add_wall(52,252, -1, -1, 16, up);
add_wall(152,152, -1, -1, 16, up);
add_wall(152,252, -1, -1, 16, up);
add_wall(202,352, -1, -1, 16, up);
add_wall(302,52, -1, -1, 16, up);
add_wall(302,152, -1, -1, 16, up);
add_wall(302,352, -1, -1, 16, up);
add_wall(652,152, -1, -1, 16, up);
add_wall(652,252, -1, -1, 16, up);
add_wall(652,352, -1, -1, 16, up);
add_wall(752,52, -1, -1, 16, up);
add_wall(752,352, -1, -1, 16, up);
add_wall(802,252, -1, -1, 16, up);



//add_wall(851,49, 1, -1, 16, up);
//add_wall(851,249, 1, -1, 16, up);
//add_wall(751,149, 1, -1, 16, up);
//add_wall(751,249, 1, -1, 16, up);
//add_wall(701,349, 1, -1, 16, up);
//add_wall(601,49, 1, -1, 16, up);
//add_wall(601,149, 1, -1, 16, up);
//add_wall(601,349, 1, -1,  16, up);
//add_wall(251,149, 1, -1,  16, up);
//add_wall(251,249, 1, -1,  16, up);
//add_wall(251,349, 1, -1,  16, up);
//add_wall(151,49, 1, -1,  16, up);
//add_wall(151,349, 1, -1,  16, up);
//add_wall(101,249, 1, -1,  16, up);


add_wall(848,52, 1, -1, 16, up);
add_wall(848,252, 1, -1, 16, up);
add_wall(748,152, 1, -1, 16, up);
add_wall(748,252, 1, -1, 16, up);
add_wall(698,352, 1, -1, 16, up);
add_wall(598,52, 1, -1, 16, up);
add_wall(598,152, 1, -1, 16, up);
add_wall(598,352, 1, -1,  16, up);
add_wall(248,152, 1, -1,  16, up);
add_wall(248,252, 1, -1,  16, up);
add_wall(248,352, 1, -1,  16, up);
add_wall(148,52, 1, -1,  16, up);
add_wall(148,352, 1, -1,  16, up);
add_wall(98,252, 1, -1,  16, up);




//add_wall(101,201, 1, 1,  16, up);
//add_wall(151,101, 1, 1,  16, up);
//add_wall(151,401, 1, 1,  16, up);
//add_wall(251,101, 1, 1,  16, up);
//add_wall(251,201, 1, 1,  16, up);
//add_wall(251,301, 1, 1,  16, up);
//add_wall(601,101, 1, 1,  16, up);
//add_wall(601,301, 1, 1,  16, up);
//add_wall(601,401, 1, 1,  16, up);
//add_wall(701,101, 1, 1,  16, up);
//add_wall(751,201, 1, 1,  16, up);
//add_wall(751,301, 1, 1,  16, up);
//add_wall(851,201, 1, 1,  16, up);
//add_wall(851,401, 1, 1,  16, up);

add_wall(98,198, 1, 1,  16, up);
add_wall(148,98, 1, 1,  16, up);
add_wall(148,398, 1, 1,  16, up);
add_wall(248,98, 1, 1,  16, up);
add_wall(248,198, 1, 1,  16, up);
add_wall(248,298, 1, 1,  16, up);
add_wall(598,98, 1, 1,  16, up);
add_wall(598,298, 1, 1,  16, up);
add_wall(598,398, 1, 1,  16, up);
add_wall(698,98, 1, 1,  16, up);
add_wall(748,198, 1, 1,  16, up);
add_wall(748,298, 1, 1,  16, up);
add_wall(848,198, 1, 1,  16, up);
add_wall(848,398, 1, 1,  16, up);




//add_wall(49,201, -1, 1,  16, up);
//add_wall(49,401, -1, 1,  16, up);
//add_wall(149,201, -1, 1,  16, up);
//add_wall(149,301, -1, 1,  16, up);
//add_wall(199,101, -1, 1,  16, up);
//add_wall(299,101, -1, 1,  16, up);
//add_wall(299,301, -1, 1,  16, up);
//add_wall(299,401, -1, 1,  16, up);
//add_wall(649,101, -1, 1,  16, up);
//add_wall(649,201, -1, 1,  16, up);
//add_wall(649,301, -1, 1,  16, up);
//add_wall(749,101, -1, 1,  16, up);
//add_wall(749,401, -1, 1,  16, up);
//add_wall(799,201, -1, 1,  16, up);

add_wall(52,198, -1, 1,  16, up);
add_wall(52,398, -1, 1,  16, up);
add_wall(152,198, -1, 1,  16, up);
add_wall(152,298, -1, 1,  16, up);
add_wall(202,98, -1, 1,  16, up);
add_wall(302,98, -1, 1,  16, up);
add_wall(302,298, -1, 1,  16, up);
add_wall(302,398, -1, 1,  16, up);
add_wall(652,98, -1, 1,  16, up);
add_wall(652,198, -1, 1,  16, up);
add_wall(652,298, -1, 1,  16, up);
add_wall(752,98, -1, 1,  16, up);
add_wall(752,398, -1, 1,  16, up);
add_wall(802,198, -1, 1,  16, up);

for(int i = 0; i <= 18; i++)
{

	add_wall(i*50-1,0, -1, 1,  16, up);
	add_wall(i*50-1,449, -1, 1,  16, up);
}



for(int j = 1; j < 9; j++)
{

	add_wall(0,j*50-1, -1, 1,  16, up);
	add_wall(0,j*50-1, -1, 1,  16, up);

}

	add_wall(100,50, -1, 1,  16, up);
	add_wall(200,50, -1, 1,  16, up);
	add_wall(250,50, -1, 1,  16, up);

	add_wall(800,50, -1, 1,  16, up);
	add_wall(700,50, -1, 1,  16, up);
	add_wall(650,50, -1, 1,  16, up);

	for(int i = 6; i <= 12; i++)
{

	add_wall(i*50-1,50, -1, 1,  16, up);
	add_wall(i*50-1,100, -1, 1,  16, up);
	add_wall(i*50-1,150, -1, 1,  16, up);
	add_wall(i*50-1,300, -1, 1,  16, up);
	add_wall(i*50-1,350, -1, 1,  16, up);
	add_wall(i*50-1,400, -1, 1,  16, up);
}


	add_wall(50,100, -1, 1,  16, up);
	add_wall(100,100, -1, 1,  16, up);
	add_wall(800,100, -1, 1,  16, up);
	add_wall(850,100, -1, 1,  16, up);

	add_wall(50,150, -1, 1,  16, up);
	add_wall(100,150, -1, 1,  16, up);
	add_wall(800,150, -1, 1,  16, up);
	add_wall(850,150, -1, 1,  16, up);

	add_wall(200,150, -1, 1,  16, up);
	add_wall(700,150, -1, 1,  16, up);

	add_wall(200,200, -1, 1,  16, up);
	add_wall(700,200, -1, 1,  16, up);
	add_wall(300,200, -1, 1,  16, up);
	add_wall(600,200, -1, 1,  16, up);

	add_wall(300,250, -1, 1,  16, up);
	add_wall(600,250, -1, 1,  16, up);
	add_wall(200,250, -1, 1,  16, up);
	add_wall(700,250, -1, 1,  16, up);

	add_wall(50,300, -1, 1,  16, up);
	add_wall(100,300, -1, 1,  16, up);
	add_wall(200,300, -1, 1,  16, up);


	add_wall(850,300, -1, 1,  16, up);
	add_wall(800,300, -1, 1,  16, up);
	add_wall(700,300, -1, 1,  16, up);

	add_wall(50,350, -1, 1,  16, up);
	add_wall(100,350, -1, 1,  16, up);
	add_wall(850,350, -1, 1,  16, up);
	add_wall(800,350, -1, 1,  16, up);



	add_wall(100,400, -1, 1,  16, up);
	add_wall(200,400, -1, 1,  16, up);
	add_wall(250,400, -1, 1,  16, up);

	add_wall(800,400, -1, 1,  16, up);
	add_wall(700,400, -1, 1,  16, up);
	add_wall(650,400, -1, 1,  16, up);
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
	for (int i = 0; i < n; i ++)
		{
			//double x = (double)rand() / RAND_MAX * (CELL_LENGTH*DOMAIN_DIM_1);
			//double y = (double)rand() / RAND_MAX * (CELL_LENGTH*DOMAIN_DIM_2);
			
			double x, y;
			/*Use this to restrict to the middle*/
			if(DOMAIN_DIM_1 % 2 == 0)
			{
				int padx = std::max(DOMAIN_DIM_1 / 2 - 2,0);
				x = padx*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH);
				if( rand() % 2)
					if(DOMAIN_DIM_1 > 2 )
						x += 3*CELL_LENGTH;
					else
						x += CELL_LENGTH;
			}
			else 
			{
				int padx = std::max(DOMAIN_DIM_1 / 2 -1,0);
				x = padx*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH);
				if(DOMAIN_DIM_1 >= 3 && rand() % 2)
					x += 2*CELL_LENGTH;
			}
			if(DOMAIN_DIM_2 % 2 == 0)
			{
				int pady = std::max(DOMAIN_DIM_2 / 2 - 2,0);
				y = pady*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH);
				if(rand() % 2)
					if(DOMAIN_DIM_2 > 2 )
						y += 3*CELL_LENGTH;
					else
						y += CELL_LENGTH;
			}
			else 
			{
				int pady = std::max(DOMAIN_DIM_2 / 2 -1,0);
				y = pady*CELL_LENGTH + (double)rand() / RAND_MAX * (CELL_LENGTH);
				if(DOMAIN_DIM_2 >= 3 && rand() % 2)
					y += 2*CELL_LENGTH;
			}
			add_predator(x, y, up);
		}
}


void world::populate_finches_rand(int n, void (* up)(agent*,agent*))
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
			
			add_finch_rand(x, y, up);
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
			params[2] = .03 * 255;
			params[3] = .7 * 255;
			params[4] = .6 * 255;
			params[5] = .5 * 255;
			params[6] = .5 * 255;

			add_finch(x, y, up, params);
		}
}

void world::populate_prey_pacman(void (* up)(agent*,agent*))
{
	unsigned char params[7];
	params[0] = .45 * 255;
	params[1] = 1.0 * 255;
	params[2] = .05 * 255;
	params[3] = .7 * 255;
	params[4] = .5 * 255;
	params[5] = .2 * 255;
	params[6] = .8 * 255;

	
	for(int i = 0; i < DOMAIN_DIM_1; i++)
	{
		for(int j = 0; j < DOMAIN_DIM_2; j++)
		{
			if(!(cellList[i][j]->phantom_zone))
			{
				add_finch(CELL_LENGTH/2 + CELL_LENGTH * i, CELL_LENGTH/2 + CELL_LENGTH * j, up, params);
			}
		}
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


void world::run_pacman(std::ostream& strm, int print_every, int iterations)
{
	
    time_t t = time(NULL);
	std::cout << 0 << " " << time(NULL) - t << " total seconds elapsed" << "\n";
	print(strm);
	for(int i = 1; i <= 4; i++)
	{
        update_forward_velocs_pacman();
		
		update_agent_pos_euler();
		//std::cerr << "\n";
		move_to_cell_pac();
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
		update_forward_velocs_pacman();
		update_agent_pos_ab4();
		//std::cerr << "\n";
		move_to_cell_pac();
		if(i % print_every == 0){
			std::cout << i << " " << time(NULL) - t << " total seconds elapsed" << "\n";
			print(strm);
		}
		//w.print(str);
		//w.print(std::cout);
		if(death_count >= 100)
			break;
	}

}
void world::run_evolution()
{
	int threshold = STUDYSIZE / 2;
	for(int i = 1; i <= 4; i++)
	{
        update_forward_velocs();
		euler_evolve();
		move_to_cell_evo();
    }

	//solve using AB4
	while(death_count < threshold)
	{
		update_forward_velocs();
		ab4_evolve();
		move_to_cell_evo();
	}
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

void world::update_forward_velocs_pacman(){
	//Iterates through all cells and does pairwise comparisons
    

	//Same-cell comparison
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
					
				}
				target2.reset_current();
			}    
		}
	}


	//all other neighbor comparisons
	for(int i = 0; i < DOMAIN_DIM_1; i++)
	{
        for(int j = 0; j < DOMAIN_DIM_2; j++)
		{
        
			/*if(cellList[i][j]->phantom_zone)
				continue;*/

			int n_end = cellList[i][j]->neighbors.size();
			for(int z = 0; z < n_end; z++)
			{

            cell_node_iterator target = cellList[i][j]->get_iter();
            cell_node_iterator right = cellList[i][j]->get_neighbor(z) -> get_iter();
            
            for(target; target.current != NULL; target.next())
			{
                
                for(right; right.current != NULL; right.next())
				{
                    
					agent* agent_brown = target.current->get_agent();
					agent* agent_jones = right.current->get_agent();

					agent_brown->update(agent_brown, agent_jones);
				//	agent_jones->update(agent_jones, agent_brown);

                   /* target.current->get_agent()->update(target.current->get_agent(), right.current->get_agent());
                    right.current->get_agent()->update(right.current->get_agent(), target.current->get_agent());*/
                    
                }
                
                right.reset_current();
                
            }    
        
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

void world::move_to_cell_pac() 
{
	for (int i = 0; i < DOMAIN_DIM_1; i++) {
		for (int j = 0; j < DOMAIN_DIM_2; j++) {

			cell* current_cell = cellList[i][j];

			/*if(current_cell->phantom_zone)
				continue;*/

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
					if(x < 0 || x >= DOMAIN_DIM_1 || y < 0 || y >= DOMAIN_DIM_2 /*|| cellList[x][y]->phantom_zone*/){
						
						//current_agent->move_inside(x,y);
						current_agent->kill();
						
						theLonelyIsland->add_top(current_node);
						death_count++;
					//	std::cout << "\n out of bounds kill \n";
						std::cout << "\n out of bounds kill at " << current_agent->x_coord << "," << current_agent->y_coord <<"\n";
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
	unsigned char oldparams [STUDYSIZE][7];

	int ams = agents_master.size();
	int count = 0;
	for(int i = 0; i < ams; i++) 
	{
		if (agents_master[i]->get_type() == 0 && agents_master[i]->is_alive()) 
		{
			count++;
			finch* current = (finch*) agents_master[i];
			for (int j = 0; j < 7; j++) 
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
	for(int i = 0; i < count; i++)
	{	
		int dad = rand()% count;
		int mom = rand()% count;

		int crosspoint = rand()%8;
		
		for(int j = 0; j < crosspoint; j++)
			{
				oldparams[i+count][j] = oldparams[dad][j];
			}

		for(int k = crosspoint; k < 7; k++)
			{
				oldparams[i+count][k] = oldparams[mom][k];
			}
	}


	//mutate
	for(int i = 0; i < STUDYSIZE; i++)
	{	
			//this will choose which genes mutate with chance (1/2)^5
			unsigned short x = rand()% 128;
			unsigned short y = rand()% 128;
			unsigned short z = rand()% 128;
			unsigned short a = rand()% 128;
			unsigned short b = rand()% 128;
			unsigned short M = x & y & z & a & b;

			for(int j = 0; j < 7; j++)
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
		unsigned char genes[7];
		for(int z = 0; z < 7; z++)
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

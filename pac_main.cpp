#include "world.h"
#include "helper_fcns.h"
#include <fstream>
#include <ctime>
#include <string>
#include <iostream>


double h_gamma_r[256][5626];
double exp_hund[151];
double exp_half[151];

int main()
{

	
for(int r = 0; r <= 5625; r++)
{
	for(int gamma = 0; gamma <= 255; gamma++)
	{
		
		h_gamma_r[gamma][r] = 1 / pow((1 + r), (double)gamma/ 250.0);
		
	}
}

for(int r = 0; r <= 150; r++)
{
	exp_hund[r] = exp(-r/100.0);
}

for(int r = 0; r <= 150; r++)
{
	exp_half[r] = exp(-r/2.0);
}


	//Set file path for output
	std::ofstream strm;
	std::string filepath = "C:\\Users\\dougyd\\Desktop\\pacman.txt";
	std::cout << "Data printed to " << filepath;
	strm.open(filepath.c_str());
	
	//setup
	time_t t = time(NULL);
	srand (t);
	
	//initialize world
	world w = world(velocity_wall_interaction, repellor);
	//world w = world();
	//w.populate_finches_std(55, pacman1);
	w.populate_prey_pacman(pacman1);
	w.add_predator(425, 125, predator_pac);
	//w.add_boundary(wall_interaction);

	/*for(int i = 0; i < DOMAIN_DIM_1; i++)
	{
		for(int j = 0; j < DOMAIN_DIM_2; j++)
		{
			std::cout << "\n";
			w.cellList[i][j]->print();
		}
	}

	system("PAUSE");*/

	w.run_pacman(strm, 200, 480000);
	//w.run(strm, 300, 120000);

	//cleanup
	strm.close();
	std::cout << "Data printed to " << filepath << "\n";
	system("PAUSE");
	return 0;
}

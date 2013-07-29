#include "world.h"
#include "helper_fcns.h"
#include <fstream>
#include <ctime>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>

double h_gamma_r[256][76];
double exp_hund[76];
double exp_half[76];



int main()
{


for(int r = 0; r <= 75; r++)
{
	for(int gamma = 0; gamma <= 255; gamma++)
	{
		
		h_gamma_r[gamma][r] = 1 / pow((1 + r*r), GAMMA);
	}
}

for(int r = 0; r <= 75; r++)
{
	exp_hund[r] = exp(-r/100.0);
}

for(int r = 0; r <= 75; r++)
{
	exp_half[r] = exp(-r/2.0);
}


	std::cout << "WAIT! Did you change the filepath?";
	system("PAUSE");

	int predator_size = 5;

	//Setup
	std::ofstream strm;
	time_t t = time(NULL);
	srand(t);
	world w = world();
	w.add_boundary(velocity_wall_interaction);
	w.populate_finches_rand(STUDYSIZE, finch1);
	w.populate_predator_rand(predator_size, predator_2012);
	
	

	for(int i = 1; i <= 200; i++)
	{
		std::stringstream ss;
		ss << i;
		std::string filepath = "C:\\Users\\dougyd\\Desktop\\withcrossover\\newtest" + ss.str() + ".txt";
		strm.open(filepath);
		std::cout << "Generation " << i << " initializing... \n";
		
		
		w.run_evolution();
		w.repopulate1(finch1, strm);
		w.add_boundary(wall_interaction);
		w.populate_predator_rand(predator_size, predator_2012);

		strm.close();
		std::cout << "Generation " << i << " complete! Genome saved to " << filepath << ". \n";
	}

	system("PAUSE");
	return 0;
}

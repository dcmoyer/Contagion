#include "world.h"
#include "helper_fcns.h"
#include <fstream>
#include <ctime>
#include <string>
#include <iostream>


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


	//Set file path for output
	std::ofstream strm;
	std::string filepath = "C:\\Users\\dougyd\\Desktop\\Tim.txt";
	std::cout << "Data printed to " << filepath;
	strm.open(filepath.c_str());
	
	//setup
	time_t t = time(NULL);
	srand (t);
	
	//initialize world
	world w = world();
	//w.populate_rand(55, prey_2012_fear);
	w.populate_finches_std(150, finch1);
	w.add_predator(125, 110, predator_2012);
	w.add_predator(105, 135, predator_2012);
	w.add_predator(130, 125, predator_2012);
	w.add_predator(145, 139, predator_2012);
	w.add_predator(150, 125, predator_2012);
	w.add_boundary(velocity_wall_interaction);

	w.run(strm, 175, 100000);

	//cleanup
	strm.close();
	std::cout << "Data printed to " << filepath << "\n";
	system("PAUSE");
	return 0;
}

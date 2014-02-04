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
	system("read -p 'Press [Enter] key to start backup...'");
	//Setup
	std::ofstream strm, runtime;
	time_t t = time(NULL);
	srand(t);
	world w = world();
	w.add_boundary(velocity_wall_interaction);
	w.populate_finches2_rand(STUDYSIZE ,finch_two, Bert_DOrg_util);
	
	std::stringstream timecheck;
  timecheck << t;
  
  std::string runtime_filepath = "./data/" + timecheck.str() + "_runtimes.txt";
  runtime.open(runtime_filepath.c_str());

	for(int i = 1; i <= STUDYLENGTH; i++)
	{
		std::stringstream ss;
		ss << i;
		std::string filepath = "./data/" + timecheck.str() + "_" + ss.str() + "_CS.txt";
		strm.open(filepath.c_str());
		std::cout << "Generation " << i << " initializing... \n";
		
		w.run_evolution_2(runtime);
		w.repopulate_CS_util(finch_two, Bert_DOrg_util, strm);
		w.add_boundary(wall_interaction);

		strm.close();
		std::cout << "Generation " << i << " complete! Genome saved to " << filepath << ". \n";
	}
  runtime.close();
	system("read -p 'Press [Enter] key to start backup...'");
	return 0;
}

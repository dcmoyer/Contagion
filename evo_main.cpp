#include "world.h"
#include "helper_fcns.h"
#include <fstream>
#include <ctime>
#include <string>
#include <iostream>
#include <sstream>


int main()
{
	//Setup
	std::ofstream strm;
	time_t t = time(NULL);
	srand(0);
	world w = world();
	w.add_boundary(wall_interaction);
	w.populate_finches_std(10, finch1);
	w.populate_predator_rand(1, predator_2012);
	

	for(int i = 1; i <= 20; i++)
	{
		std::stringstream ss;
		ss << i;
		std::string filepath = "C:\\Users\\dougyd\\Desktop\\simple" + ss.str() + ".txt";
		strm.open(filepath);
		std::cout << "Generation " << i << " initializing... \n";
		
		
		w.run_evolution();
		w.repopulate1(finch1, strm);
		w.add_boundary(wall_interaction);
		w.populate_predator_rand(1, predator_2012);

		strm.close();
		std::cout << "Generation " << i << " complete! Genome saved to " << filepath << ". \n";
	}

	system("PAUSE");
	return 0;
}

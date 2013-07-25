#include "world.h"
#include "helper_fcns.h"
#include <fstream>
#include <ctime>
#include <string>
#include <iostream>
#include <sstream>


int main()
{
	
	int predator_size = 5;

	//Setup
	std::ofstream strm;
	time_t t = time(NULL);
	srand(t);
	world w = world();
	w.add_boundary(wall_interaction);
	w.populate_finches_std(STUDYSIZE, finch1);
	w.populate_predator_rand(predator_size, predator_2012);
	
	

	for(int i = 1; i <= 5000; i++)
	{
		std::stringstream ss;
		ss << i;
		std::string filepath = "C:\\Users\\dougyd\\Desktop\\overnite" + ss.str() + ".txt";
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

#include "world.h"
#include "helper_fcns.h"
#include <fstream>
#include <ctime>
#include <string>
#include <iostream>


int main()
{
	//Set file path for output
	std::ofstream strm;
	std::string filepath = "C:\\Users\\dougyd\\Desktop\\simple.txt";
	std::cout << "Data printed to " << filepath;
	strm.open(filepath.c_str());
	
	//setup
	time_t t = time(NULL);
	srand (t);
	
	//initialize world
	world w = world();
	w.populate_rand(5, swarm1);
	//w.populate_finches_rand(45, finch1);
	//w.populate_predator_rand(1, predator_2012);

	w.run(strm, 100, 1000);

	//cleanup
	strm.close();
	std::cout << "Data printed to " << filepath << "\n";
	system("PAUSE");
	return 0;
}

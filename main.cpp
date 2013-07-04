#include "world.h"
#include "helper_fcns.h"
#include <fstream>
#include <ctime>
#include <string>

int main()
{
	std::ofstream str;
	std::string filepath = "C:\\Users\\dougyd\\Desktop\\data1.txt";
	time_t t = time(NULL);
	str.open(filepath);
	world w = world();
	w.populate_rand(75, swarm1);
	for(int i = 1; i <=50000; i++)
	{
		w.update_forward_velocs();
		w.update_agent_pos();
		w.move_to_cell();
		if(i % 100 == 0){
			std::cout << i << " " << time(NULL) - t << " total seconds elapsed" << "\n";
			w.print(str);
		}
		//w.print(str);
		//w.print(std::cout);
	}
	str.close();

	std::cout << "Data printed to " << filepath << "\n";
	system("PAUSE");


	return 0;
}

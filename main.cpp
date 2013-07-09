#include "world.h"
#include "helper_fcns.h"
#include <fstream>
#include <ctime>
#include <string>

int main()
{
	//Set file path for output
	std::ofstream str;
	std::string filepath = "C:\\Users\\dougyd\\Desktop\\test.txt";
	str.open(filepath.c_str());
	
	time_t t = time(NULL);

	//initialize world
	world w = world();
	w.populate_rand(50, swarm1);
    int jump_val = 4;
    int print_val = 100;

	//solve initial data with euler's method
    for(int i = 1; i <= jump_val; i++)
	{
        w.update_forward_velocs();
		w.update_agent_pos_euler();
		w.move_to_cell();
		if(i % print_val == 0){
			std::cout << i << " " << time(NULL) - t << " total seconds elapsed" << "\n";
			w.print(str);
		}
		//w.print(str);
		//w.print(std::cout);
    }

	//solve using AB4
	for(int i = jump_val + 1; i <=50000; i++)
	{
		w.update_forward_velocs();
		w.update_agent_pos_ab4();
		w.move_to_cell();
		if(i % print_val == 0){
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

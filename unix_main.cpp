#include "world.h"
#include "helper_fcns.h"
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>

int main()
{
	//std::string filename = "test_data.dat";
	time_t t = time(NULL);
	world w = world();
	w.populate_rand(45, swarm1);
    
    int jump_val = 4;
    int print_val = 200;
	for(int i = 1; i <=jump_val; i++)
	{
		w.update_forward_velocs();
		w.update_agent_pos_euler();
		w.move_to_cell();
		if(i % 200 == 0){
			std::cout << i << " " << time(NULL) - t << " total seconds elapsed" << "\n";
            std::stringstream silly;
            silly << (i/200);
			w.print_csv(silly.str());
		}
		//w.print(str);
		//w.print(std::cout);
	}
    for(int i = jump_val + 1; i <= 1000000; i++)
	{
		w.update_forward_velocs();
		w.update_agent_pos_ab4();
		w.move_to_cell();
		if(i % print_val == 0){
			std::cout << i << " " << time(NULL) - t << " total seconds elapsed" << "\n";
            std::stringstream silly;
            silly << (i/200);
			w.print_csv(silly.str());
		}
		//w.print(str);
		//w.print(std::cout);
	}
    
	//std::cout << "Data printed to " << filename << "\n";    
    
	return 0;
}

#include "world.h"
#include "helper_fcns.h"
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>

int main()
{
	std::string filename = "test_data.dat";
	time_t t = time(NULL);
	world w = world();
	w.populate_rand(75, swarm1);
	for(int i = 1; i <=100; i++)
	{
		w.update_forward_velocs();
		w.update_agent_pos();
		w.move_to_cell();
		if(i % 100 == 0){
			std::cout << i << " " << time(NULL) - t << " total seconds elapsed" << "\n";
            std::stringstream silly;
            silly << i;
			w.print_csv(silly.str());
		}
		//w.print(str);
		//w.print(std::cout);
	}
    
	std::cout << "Data printed to " << filename << "\n";    
    
	return 0;
}

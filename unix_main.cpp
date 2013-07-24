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
	w.add_boundary(velocity_wall_interaction);
	//w.add_boundary(wall_interaction);
	w.populate_rand(100, swarm1 );
	//w.add_agent(10,10, prey_2012_fear);
	//w.add_agent(40,10, prey_2012_fear);
	w.add_predator(40,40,predator_2012);
	//w.populate_predator_rand(1, predator_2012);
	//w.add_wall(100.0001, 100, 1, 0, 1000, wall_interaction);
	//w.add_wall(50, 50, -1, 0, 1000, wall_interaction);
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
    for(int i = jump_val + 1; i <= 100000; i++)
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

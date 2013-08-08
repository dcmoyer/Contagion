#include "grid_world.h"
#include "helper_fcns.h"
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>
#include <iostream>

int main()
{
	//std::string filename = "test_data.dat";
	time_t t = time(NULL);
	grid_world gw = grid_world();
	
	//gw.place_agent(20,10,NULL,NULL);
	gw.place_fire(10,10, fire_potential, NULL);
	gw.place_goal(37,105, exit_potential);
	//exterior walls
	gw.place_wall(37, 25, 1, 0, 84, wall_potential, wall_density);
	gw.place_wall(0, 25, 1, 0, 84, wall_potential, wall_density);
	
	//seats
	/*gw.place_wall(7, 6, 1, 0, 7, wall_potential, NULL);
	gw.place_wall(29, 6, 1, 0, 7, wall_potential, NULL);
	gw.place_wall(51, 6, 1, 0, 7, wall_potential, NULL);*/
	for(int i = 1; i < 7; i++){
		gw.place_wall(5, 15*i, 0, 1, 5, wall_potential, wall_density);
		gw.place_agent(5, 15*i - 2, NULL, agent_population_density);
		gw.place_agent(5-3, 15*i - 2, NULL, agent_population_density);
		gw.place_agent(5+3, 15*i - 2, NULL, agent_population_density);
		
		gw.place_wall(19, 15*i, 0, 1, 5, wall_potential, wall_density);
		gw.place_agent(19, 15*i - 2, NULL, agent_population_density);
		gw.place_agent(19+3, 15*i - 2, NULL, agent_population_density);
		gw.place_agent(19-3, 15*i - 2, NULL, agent_population_density);
		
		gw.place_wall(33, 15*i, 0, 1, 5, wall_potential, wall_density);
		gw.place_agent(33, 15*i - 2, NULL, agent_population_density);
		gw.place_agent(33+3, 15*i - 2, NULL, agent_population_density);
		gw.place_agent(33-3, 15*i - 2, NULL, agent_population_density);
		
	} 
	
	std::cout << "World Instantiated\n";
	gw.initialize_static_field();
	std::cout << "Field Initialized\n";
	gw.print_static_csv();
	gw.print_static_wall_csv();
	std::cout << "Statics Printed \n";
	int jump_val = 4;
	int print_val = 100;
	
	gw.print_field();
	
	for(int i = 1; i <=jump_val; i++)
	{
		//std::cout << "Step "<< i;
		gw.update_forward_accel();
		gw.update_agent_pos_euler();
		if(i % print_val == 0){
			std::cout << i << " " << time(NULL) - t << " total seconds elapsed" << "\n";
            std::stringstream silly;
            silly << (i/print_val);
			gw.print_csv(silly.str());
		}
		//w.print(str);
		//w.print(std::cout);
	}
    for(int i = jump_val + 1; i <= 20000; i++)
	{
		gw.update_forward_accel();
		gw.update_agent_pos_ab4();
		if(i % print_val == 0){
			std::cout << i << " " << time(NULL) - t << " total seconds elapsed" << "\n";
            std::stringstream silly;
            silly << (i/print_val);
			gw.print_csv(silly.str());
	}
		//w.print(str);
		//w.print(std::cout);
	}
    
	//std::cout << "Data printed to " << filename << "\n";    
	
    
	return 0;
}

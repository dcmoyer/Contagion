#include "world.h"
#include "helper_fcns.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <cmath>

using std::cout;
using std::endl;

int main()
{
	//Set file path for output
	std::ofstream str;
	std::string filepath = "C:\\Users\\dougyd\\Desktop\\test.txt";
	str.open(filepath.c_str());

	for (int i = 1; i<18; i++)
	  {
		  
	    long int num_agents = pow(2.0,(double)i);

	    //initialize world
	    world* pw = new world();
	    pw->populate_rand(num_agents, swarm1);

	    clock_t t = clock();
	
	    pw->update_forward_velocs();
	    pw->update_agent_pos_euler();
	    pw->move_to_cell();

	    clock_t s = clock();
	    
	    long int cycles = (long int)s -(long int)t;
	    double seconds = (double)cycles/(double)CLOCKS_PER_SEC;
	    cout << num_agents << " agents,  " 
		 << cycles << " cycles elapsed, " 
		 << seconds << " seconds elapsed" 
		 << endl;

	    delete pw;
	  }


	/*
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
	*/
	return 0;
}

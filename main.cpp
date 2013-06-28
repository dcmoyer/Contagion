#include "world.h"



int main()
{
	world w = world();
	
	
	w.add_agent(10,10);
	w.add_agent(40,40);

	double vx[] = {4,4,4,4};

	(*(w.agents_master[0])).set_x_veloc(vx);
	
	
	for(int i = 1; i <= 10; i++)
	{
	w.refresh_eul();
	w.print(std::cout);
	}


	std:: cout << "velocity is " << *(*(w.agents_master[0])).get_x_veloc();



	system("PAUSE");
	return 0;
}
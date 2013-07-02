#include "world.h"
#include <fstream>

int main()
{
	std::ofstream str;
	str.open("data.txt");
	world w = world();
	w.populate_rand(75);
	for(int i = 1; i <=200
		; i++)
	{
		w.update_forward_velocs();
		w.update_agent_pos();
		w.print(str);
		//w.print(std::cout);
	}
	str.close();
	//system("PAUSE");


	return 0;
}
#include "world.h"
#include <fstream>

int main()
{
	std::ofstream str;
	str.open("data.txt");
	world w = world();
	w.populate_rand(2500);
	for(int i = 1; i <=2500
		; i++)
	{
		w.update_forward_velocs();
		w.update_agent_pos();
		w.move_to_cell();
		if(i % 10 == 0){
			std::cout << i << "\n";
			w.print(str);
		}
		//w.print(std::cout);
	}
	str.close();
	system("PAUSE");


	return 0;
}
#include "world.h"
#include <fstream>
#include <ctime>

int main()
{
	std::ofstream str;
	time_t t = time(NULL);
	str.open("C:\\Users\\dougyd\\Desktop\\data1.txt");
	world w = world();
	w.populate_rand(100);
	for(int i = 1; i <=5000; i++)
	{
		w.update_forward_velocs();
		w.update_agent_pos();
		w.move_to_cell();
		if(i % 25 == 0){
			std::cout << i << " " << time(NULL) - t << " total seconds elapsed" << "\n";
			w.print(str);
		}
		//w.print(str);
		//w.print(std::cout);
	}
	str.close();
	system("PAUSE");


	return 0;
}
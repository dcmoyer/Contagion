#include "world.h"

int main()
{
	world w = world();
	w.populate_rand(4);
	for(int i = 1; i <= 25; i++)
	{
		w.update_forward_velocs();
		w.update_forward_velocs();
		w.print(std::cout);
	}
	system("PAUSE");


	return 0;
}
all : world.o cell.o agent.o

agent.o : agent.cpp
	g++ -o agent.o -c agent.cpp

cell.o : cell.cpp agent.o
	g++ -o cell.o -c cell.cpp agent.o

world.o : cell.o agent.o world.cpp
	g++ -o player.o -c world.cpp cell.o agent.o

#Trading_Thangs.BETA : Main_Interface.cpp cargo.2.o ship.o battle.o player.o mapgraph.o world.o
#	g++ -o Trading_Thangs.BETA Main_Interface.cpp world.cpp mapgraph.cpp battle.cpp player.cpp ship.cpp cargo.2.cpp -framework OpenGL -framework GLUT

.PHONY : clean
clean :
	-rm *.o

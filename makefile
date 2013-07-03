all : main.out world.o helper_fcns.o cell.o agent.o

agent.o : agent.cpp
	g++ -o agent.o -c agent.cpp

cell.o : cell.cpp agent.o
	g++ -o cell.o -c cell.cpp

world.o : cell.o agent.o world.cpp helper_fcns.o
	g++ -o world.o -c world.cpp

helper_fcns.o : helper_fcns.cpp
	g++ -o helper_fcns.o -c helper_fcns.cpp

#Trading_Thangs.BETA : Main_Interface.cpp cargo.2.o ship.o battle.o player.o mapgraph.o world.o
#	g++ -o Trading_Thangs.BETA Main_Interface.cpp world.cpp mapgraph.cpp battle.cpp player.cpp ship.cpp cargo.2.cpp -framework OpenGL -framework GLUT

main.out : main.cpp cell.o agent.o world.o helper_fcns.o
	g++ main.cpp helper_fcns.o world.o cell.o agent.o

.PHONY : clean
clean :
	-rm *.o a.out main.out

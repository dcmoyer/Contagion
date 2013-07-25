all : clean agent.o cell.o world.o helper_fcns.o main.out
test: test_agent test_cell test_world

agent.o : agent.cpp
	g++ -o agent.o -c agent.cpp

predator.o : predator.cpp agent.o
	g++ -o predator.o -c predator.cpp

wall.o : wall.cpp agent.o
	g++ -o wall.o -c wall.cpp

finch.o : finch.cpp agent.o
	g++ -o finch.o -c finch.cpp

cell.o : cell.cpp
	g++ -o cell.o -c cell.cpp

world.o : world.cpp predator.o helper_fcns.o
	g++ -o world.o -c world.cpp

helper_fcns.o : helper_fcns.cpp predator.o wall.o finch.o
	g++ -o helper_fcns.o -c helper_fcns.cpp

#Trading_Thangs.BETA : Main_Interface.cpp cargo.2.o ship.o battle.o player.o mapgraph.o world.o
#	g++ -o Trading_Thangs.BETA Main_Interface.cpp world.cpp mapgraph.cpp battle.cpp player.cpp ship.cpp cargo.2.cpp -framework OpenGL -framework GLUT

evo_main.out : main.cpp cell.o agent.o world.o helper_fcns.o predator.o finch.o wall.o
	g++ evo_main.cpp helper_fcns.o world.o cell.o agent.o predator.o finch.o wall.o

main.out : main.cpp cell.o agent.o world.o helper_fcns.o predator.o
	g++ main.cpp helper_fcns.o world.o cell.o agent.o predator.o

unix_main : unix_main.cpp cell.o agent.o world.o helper_fcns.o predator.o finch.o
	g++ -o unix_main -O3 unix_main.cpp helper_fcns.o world.o cell.o agent.o predator.o wall.o finch.o

test_agent: test_agent.o agent.o
	g++ -o test_agent agent.o test_agent.o

test_cell: test_cell.o cell.o
	g++ -o test_cell cell.o agent.o test_cell.o

test_world: test_world.o world.o predator.o
	g++ -o test_world world.o agent.o cell.o helper_fcns.o test_world.o predator.o

test_movement: test_movement.o world.o
	g++ -o test_movement world.o agent.o cell.o helper_fcns.o test_movement.o predator.o

timing: timing.o world.o
	g++ -O3 -o timing world.o agent.o cell.o helper_fcns.o timing.o predator.o

.PHONY : clean
clean :
	-rm *.o

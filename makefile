FLAGS=-lIL -Wall
all:	analizer
analizer: program.o plotno.o pixel.o maska.o
	g++ $(FLAGS) program.o plotno.o pixel.o maska.o -o analizer
maskatest:maskatest.cpp maska.o pixel.o
	g++ $(FLAGS) maskatest.cpp maska.o pixel.o -o maskatest
program.o: analizer.cpp
	g++ -c $(FLAGS) analizer.cpp -o program.o
plotno.o:plotno.cpp plotno.hpp
	g++ -c $(FLAGS) plotno.cpp -o plotno.o
pixel.o:pixel.cpp pixel.hpp
	g++ -c $(FLAGS) pixel.cpp -o pixel.o
maska.o:maska.cpp maska.hpp
	g++ -c $(FLAGS) maska.cpp -o maska.o
clean:	
	rm -f analizer
	rm -f *.o
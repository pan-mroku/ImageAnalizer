FLAGS=-lIL -Wall
analizer: program.o plotno.o pixel.o
	g++ $(FLAGS) program.o plotno.o pixel.o -o analizer
program.o: analizer.cpp plotno.o pixel.o
	g++ -c $(FLAGS) analizer.cpp -o program.o
plotno.o:plotno.h plotno.cpp pixel.o
	g++ -c $(FLAGS) plotno.cpp -o plotno.o
pixel.o:pixel.h pixel.cpp
	g++ -c $(FLAGS) pixel.cpp -o pixel.o
clean:	
	rm -f analizer
	rm -f *.o
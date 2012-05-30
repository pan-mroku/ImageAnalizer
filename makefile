FLAGS=-Wall
LIBS=-lIL
ifeq ($(OSTYPE), Windows_NT)
	LIBS=lib/DevIL.lib
endif

all:	analizer
analizer: program.o plotno.o pixel.o maska.o utils.o
	g++ $(FLAGS) program.o plotno.o pixel.o maska.o utils.o -o analizer $(LIBS)
program.o: analizer.cpp
	g++ -c $(FLAGS) analizer.cpp -o program.o
plotno.o:plotno.cpp plotno.hpp
	g++ -c $(FLAGS) plotno.cpp -o plotno.o
pixel.o:pixel.cpp pixel.hpp
	g++ -c $(FLAGS) pixel.cpp -o pixel.o
maska.o:maska.cpp maska.hpp
	g++ -c $(FLAGS) maska.cpp -o maska.o
utils.o:utils.cpp utils.hpp
	g++ -c $(FLAGS) utils.cpp -o utils.o
clean:	
	rm -f analizer
	rm -f *.o
	rm -f *.obj
	rm -f *.exe

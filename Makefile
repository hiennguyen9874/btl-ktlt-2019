all: main.o core.o framecode.o
	g++ -g main.o core.o framecode.o -o myapp.out
main.o: main.cpp core.h
	g++ -g -c main.cpp -o main.o
core.o: core.cpp core.h
	g++ -g -c core.cpp -o core.o
framecode.o: framecode.cpp
	g++ -g -c framecode.cpp -o framecode.o
clean:
	rm *.o myapp.out
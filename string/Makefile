program: main.o string.o
	rm -f main.o string.o
	g++ -c -o main.o main.cpp
	g++ -c -o string.o string.cpp ${FLAGS}
	g++ -o main main.o string.o
#clean:
#	rm -f main.o string.o main
debug:
	make FLAGS="-DDEBUG=1"

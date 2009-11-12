program: main.o stack.o
	rm -f main.o stack.o main
	g++ -c -o main.o main.cpp
	g++ -c -o stack.o stack.cpp ${FLAGS}
	g++ -o main main.o stack.o
#clean:
#	rm -f main.o stack.o main
debug:
	make FLAGS="-DDEBUG=1 -O0 -ggdb3"

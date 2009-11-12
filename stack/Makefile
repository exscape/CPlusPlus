TARGETS = main.o stack.o
APP = main
program: ${TARGETS}
	rm -f ${TARGETS} ${APP}
	g++ -c -o main.o main.cpp
	g++ -c -o stack.o stack.cpp ${FLAGS}
	g++ -o ${APP} main.o stack.o
#clean:
#	rm -f main.o stack.o main
debug:
	make FLAGS="-DDEBUG=1 -O0 -ggdb3"

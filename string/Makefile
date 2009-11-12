TARGETS = main.o string.o
APP = main
program: ${TARGETS}
	rm -f ${TARGETS} ${APP}
	g++ -c -o main.o main.cpp
	g++ -c -o string.o string.cpp ${FLAGS}
	g++ -o ${APP} main.o string.o
#clean:
#	rm -f main.o string.o main
debug:
	make FLAGS="-DDEBUG=1 -O0 -ggdb3"

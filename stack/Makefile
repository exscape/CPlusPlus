TARGETS = main.o
APP = main
program: ${TARGETS}
	rm -f ${TARGETS} ${APP}
	g++ -o main main.cpp ${FLAGS}
#clean:
#	rm -f main.o stack.o main
debug:
	make FLAGS="-DDEBUG=1 -O0 -ggdb3"

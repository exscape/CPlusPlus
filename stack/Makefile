TARGETS = tests.o
APP = tests
program: ${TARGETS}
	rm -f ${TARGETS} ${APP}
	g++ -o tests tests.cpp -Wall ${FLAGS}
#clean:
#	rm -f stack.o tests
debug:
	make FLAGS="-DDEBUG=1 -O0 -ggdb3"

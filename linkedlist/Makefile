APP = tests
#program: doc
program:
	rm -f ${APP}
	g++ -o ${APP} tests.cpp -Wall -Werror ${FLAGS}
#clean:
#	rm -f tests.o LinkedList.o tests
debug:
	make FLAGS="-DDEBUG=2 -O0 -ggdb3"
gdb:
	make FLAGS="-DDEBUG=0 -O0 -ggdb3"
doc:
	doxygen > /dev/null

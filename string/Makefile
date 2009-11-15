TARGETS = tests.o string.o
APP = tests
program: ${TARGETS}
	rm -f ${TARGETS} ${APP}
	g++ -c -o tests.o tests.cpp -Wall -Werror ${FLAGS}
	g++ -c -o string.o string.cpp -Wall -Werror ${FLAGS}
	g++ -o ${APP} tests.o string.o -Wall -Werror ${FLAGS}
#clean:
#	rm -f tests.o string.o tests
debug:
	make FLAGS="-DDEBUG=1 -O0 -ggdb3"
gdb:
	make FLAGS="-DDEBUG=0 -O0 -ggdb3"
test_substr:
	make program
	g++ -c -o test_substr.o test_substr.cpp -Wall
	g++ -o test_substr test_substr.o string.o -Wall

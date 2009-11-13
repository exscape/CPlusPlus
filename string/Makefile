TARGETS = main.o string.o
APP = main
program: ${TARGETS}
	rm -f ${TARGETS} ${APP}
	g++ -c -o main.o main.cpp -Wall
	g++ -c -o string.o string.cpp -Wall ${FLAGS}
	g++ -o ${APP} main.o string.o -Wall
#clean:
#	rm -f main.o string.o main
debug:
	make FLAGS="-DDEBUG=1 -O0 -ggdb3"
test_substr:
	make program
	g++ -c -o test_substr.o test_substr.cpp -Wall
	g++ -o test_substr test_substr.o string.o -Wall

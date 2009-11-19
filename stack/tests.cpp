#include <iostream>
//#include <deque>
//#include <vector>
//#include <list>
#include "stack.hpp"
#include "../linkedlist/LinkedList.hpp"

//#define STORAGE_TYPE std::vector
#define STORAGE_TYPE exscape::LinkedList

int main() {
	exscape::stack<int, STORAGE_TYPE<int> > s;
	s.push(10);
	s.push(20);
	s.push(30);
	s.dump();
	s.pop();
	s.dump();

	exscape::stack<int, STORAGE_TYPE<int> > s2;
	s2.push(10);
	s2.push(20);
	s2.push(30);
	s2.dump();
	s2.pop();
	s2.dump();

	if (s == s2)
		std::cerr << "OK: s == s2" << std::endl;
	else
		std::cerr << "ERROR: s != s2!" << std::endl;

	s2.pop();
	s2.push(50);

	if (s == s2)
		std::cerr << "ERROR: s == s2!" << std::endl;
	else
		std::cerr << "OK: s != s2" << std::endl;

	exscape::stack<int, STORAGE_TYPE<int> > s3;
	s3 = s2;
	if (s3 == s2)
		std::cerr << "OK: Copied s3 == s2" << std::endl;
	else
		std::cerr << "ERROR: Copied s3 != s2!" << std::endl;

	std::cerr << "Trying underflow and copy empty stack" << std::endl;
	exscape::stack<int, STORAGE_TYPE<int> > src;
	src.push(10);
	src.pop();
	src.pop();
	exscape::stack<int, STORAGE_TYPE<int> > dest;
	dest = src;
	dest.dump();

	if (src == dest)
		std::cerr << "OK: Copied src == dest" << std::endl;
	else
		std::cerr << "ERROR: Copied src != dest!" << std::endl;

	return 0;
}

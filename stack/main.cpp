#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <list>
#include "standalone_stack.hpp"
#include "../linkedlist/LinkedList.hpp"

int main() {
//	exscape::stack<int, exscape::LinkedList<int> > s;
	exscape::stack<int, std::list<int> > s;
	s.push(10);
	s.push(20);
	s.push(30);
	s.dump();
	s.pop();
	s.dump();

	std::list<int> mylist;
	mylist.push_back(500);
	mylist.push_back(1000);
	mylist.push_back(2000);

	exscape::stack<int, std::list<int> > s2 (mylist);
	s2.dump();

	if (s == s2)
		std::cerr << "ERROR: s == s2!" << std::endl;
	else
		std::cerr << "OK: s != s2" << std::endl;

	exscape::stack<int, std::list<int> > s3 (mylist);
	s3.dump();

	if (s2 != s3)
		std::cerr << "ERROR: s2 != s3!" << std::endl;
	else
		std::cerr << "OK: s2 == s3" << std::endl;

	return 0;
}

#include <iostream>
#include <string>
#include <deque>
#include "standalone_stack.hpp"
#include "../linkedlist/LinkedList.hpp"

int main() {
//	exscape::stack<int, exscape::LinkedList<int> > s;
	exscape::stack<int, std::deque<int> > s;
	s.push(10);
	s.push(20);
	s.push(30);
	s.dump();
	s.pop();
	s.dump();

	return 0;
}

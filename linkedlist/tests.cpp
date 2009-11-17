#include <iostream>
#include "LinkedList.hpp"

int main() {
	using namespace exscape;
	LinkedList<int> list;

	list.push_front(10);
	list.push_front(20);
	list.push_back(5);
	list.push_front(30);
	list.push_back(8);
	list.pop_front();
	list.push_back(2);
	list.push_front(0);
	list.push_back(100);
	list.pop_front();
	list.dump();

	return 0;
}

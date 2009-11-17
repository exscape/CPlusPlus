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
	list.front() += 2000;
	list.back() += 500;
	list.dump();

/*
	std::cout << std::endl << "Custom, temporary \"iterator\":" << std::endl;
	while (!list.empty()) {
		std::cout << list.front() << " ";
		list.pop_front();
	}
	std::cout << std::endl;
*/

	list.clear();
	list.dump();
	list.push_back(10);
	list.dump();

	return 0;
}

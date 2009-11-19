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
	list.push_front(200);
	list.pop_front();
	list.pop_back();
	list.front() += 2000;
	list.pop_back();
	list.push_front(60);
	list.back() += 500;
	list.dump(true);

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


	LinkedList<int> l1, l2;
	l1.push_back(10);
	l1.push_back(20);
	l1.push_back(30);

	l2 = l1;

	if (l1 == l2)
		std::cerr << "OK: l1 == l2" << std::endl;
	else
		std::cerr << "ERROR: l1 != l2" << std::endl;
	l2.pop_back();

	if (l1 != l2)
		std::cerr << "OK: l1 != l2" << std::endl;
	else
		std::cerr << "ERROR: l1 == l2" << std::endl;

	return 0;
}

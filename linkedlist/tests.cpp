#include <iostream>
#include "LinkedList.hpp"

int main() {
	using namespace exscape;
	LinkedList<int> list;

	list.prepend(10);
	list.prepend(20);
	list.append(5);
	list.prepend(30);
	list.append(8);
	list.append(2);
	list.dump();

	return 0;
}

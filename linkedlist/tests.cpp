#include <iostream>
#include <algorithm>
#include <list>
#include "LinkedList.hpp"

int main() {
	using namespace exscape;
//	LinkedList<int> list;
//	LinkedList<int>::iterator it;
	std::list<int> list;
	std::list<int>::iterator it;

	list.push_back(20);
	list.push_back(30);
	list.push_back(40);

	do {
		std::cout << "Permutation: ";
		for (it = list.begin(); it != list.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	} while (std::next_permutation(list.begin(), list.end()));

/*
	std::reverse(list.begin(), list.end());

	for (it = list.begin(); it != list.end(); ++it) {
		std::cout << "Element: " << *it << std::endl;
	}
*/

	return 0;
}

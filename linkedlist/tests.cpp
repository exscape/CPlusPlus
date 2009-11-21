#include <iostream>
#include <algorithm>
#include <list>
#include "LinkedList.hpp"

int main() {
	using namespace exscape;
	LinkedList<int> list;
	LinkedList<int>::iterator it;
//std::list<int> list;
//std::list<int>::iterator it;

	list.push_back(20);
	list.push_back(30);
	list.push_back(40);

	for (it = list.begin(); it != list.end(); ++it) {
		std::cout << "Element: " << *it << std::endl;
	}
	std::cout << std::endl;

	do {
		std::cout << "Permutation: ";
		for (it = list.begin(); it != list.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		//std::cout << "... permutation printed" << std::endl;
	} while (std::next_permutation(list.begin(), list.end()));
	std::cout << std::endl;

	std::reverse(list.begin(), list.end());
	std::cout << "Reversed:" << std::endl;
	for (it = list.begin(); it != list.end(); ++it) {
		std::cout << "Element: " << *it << std::endl;
	}
	std::cout << std::endl;

	LinkedList<int> cpy;
	std::copy(list.begin(), list.end(), std::back_inserter(cpy));
	std::cout << "Copied list:" << std::endl;
	for (LinkedList<int>::iterator cp_it = cpy.begin(); cp_it != cpy.end(); ++cp_it) {
		std::cout << *cp_it << std::endl;
	}

	std::cout << "Count of 10 in list: " << std::count(list.begin(), list.end(), 10) << std::endl;
	std::cout << "Count of 20 in list: " << std::count(list.begin(), list.end(), 20) << std::endl;

	return 0;
}

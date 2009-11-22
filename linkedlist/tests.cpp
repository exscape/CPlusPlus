#include <iostream>
#include <algorithm>
#include <list>
#include "LinkedList.hpp"

#define LIST_TYPE LinkedList
//#define LIST_TYPE std::list

int main() {
	using namespace exscape;
	LIST_TYPE<int> list;
	LIST_TYPE<int>::iterator it;

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
	} while (std::next_permutation(list.begin(), list.end()));
	std::cout << std::endl;

	std::reverse(list.begin(), list.end());
	std::cout << "Reversed:" << std::endl;
	for (it = list.begin(); it != list.end(); ++it) {
		std::cout << "Element: " << *it << std::endl;
	}
	std::cout << std::endl;

	LIST_TYPE<int> cpy;
	LIST_TYPE<int>::iterator cp_it;
	std::copy(list.begin(), list.end(), std::back_inserter(cpy));
	std::cout << "Copied list:" << std::endl;
	for (cp_it = cpy.begin(); cp_it != cpy.end(); ++cp_it) {
		std::cout << *cp_it << std::endl;
	}

	std::cout << "Adding a 20 to cpy..." << std::endl;
	cpy.push_back(20);

	std::cout << "Count of 10 in copied list: " << std::count(cpy.begin(), cpy.end(), 10) << std::endl;
	std::cout << "Count of 20 in copied list: " << std::count(cpy.begin(), cpy.end(), 20) << std::endl;
	std::cout << std::endl;

	/*
	 * Start const_iterator tests
	 */

	LIST_TYPE<int>::const_iterator ci;
	for (ci = cpy.begin(); ci != cpy.end(); ++ci) {
		std::cout << "const iterator over non-const cpy: " << *ci << std::endl;
		// *ci += 2; // Fails, as it should
	}
	std::cout << std::endl;

	const LIST_TYPE<int> const_list (list);
	for (LIST_TYPE<int>::const_iterator ci = const_list.begin(); ci != const_list.end(); ++ci) {
//		*ci += 2;
//		std::cout << "ERROR: MODIFIED CONST LIST" << std::endl;
		std::cout << "const iterator in const list: " << *ci << std::endl;
	}
	std::cout << std::endl;

	return 0;
}

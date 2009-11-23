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

	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

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

	// 
	// Start const_iterator tests
	//

	for (LIST_TYPE<int>::const_iterator ci = list.begin(); ci != list.end(); ++ci) {
		std::cout << "const iterator over non-const list: " << *ci << std::endl;
		// *ci += 2; // Fails, as it should
	}
	std::cout << std::endl;

	std::cout << "\n\nStarting copy of list to const_list\n\n" << std::endl;
	const LIST_TYPE<int> const_list (list);
	std::cout << "\n\nFinished copy of list to const_list\n\n" << std::endl;
	for (LIST_TYPE<int>::const_iterator ci = const_list.begin(); ci != const_list.end(); ++ci) {
//		*ci += 2;
//		std::cout << "ERROR: MODIFIED CONST LIST" << std::endl;
		std::cout << "const iterator in const list: " << *ci << std::endl;
	}
	std::cout << std::endl;

	//
	// Start reverse iterator testing
	//

	std::cout << "\n\nReverse iterator testing (correct output: 4 3 2 1):" << std::endl;

	cpy.clear();
	cpy.push_back(1);
	cpy.push_back(2);
	cpy.push_back(3);
	cpy.push_back(4);
	LIST_TYPE<int> list_1234 = cpy;

	for (LIST_TYPE<int>::reverse_iterator ri = cpy.rbegin(); ri != cpy.rend(); ++ri) {
		std::cout << "Reverse iterator over cpy: " << *ri << std::endl;
	}
	std::cout << std::endl;

	for (LIST_TYPE<int>::const_reverse_iterator cri = const_list.rbegin(); cri != const_list.rend(); ++cri) {
		std::cout << "Reverse const iterator over const_list: " << *cri << std::endl;
	}
	std::cout << std::endl;

	for (LIST_TYPE<int>::const_reverse_iterator cri = list.rbegin(); cri != list.rend(); ++cri) {
		std::cout << "Reverse const iterator over non-const list: " << *cri << std::endl;
	}

	//
	// Iterator copy constructor + assign() tests
	//
	
	LIST_TYPE<int> cpy2 (list.begin(), list.end());
	for (LIST_TYPE<int>::const_iterator ci = cpy2.begin(); ci != cpy2.end(); ++ci) {
		std::cout << "iterator copy constructed list copy: " << *ci << std::endl;
	}
	std::cout << std::endl;
	
	list.assign(cpy.begin(), cpy.end());
	for (LIST_TYPE<int>::const_iterator ci = list.begin(); ci != list.end(); ++ci) {
		std::cout << "list after assign(cpy): " << *ci << std::endl;
	}
	std::cout << std::endl;

	//
	// erase() tests
	//
	LIST_TYPE<int>::iterator erase_it = list.begin();
	cpy = list;
	++erase_it;
	list.erase(erase_it);
	for (LIST_TYPE<int>::const_iterator ci = list.begin(); ci != list.end(); ++ci) {
		std::cout << "list after erase(begin+1): " << *ci << std::endl;
	}
	std::cout << std::endl;
//	list.dump(true);

	LIST_TYPE<int> one;
	one.push_back(1);

	std::cout << "One pre-erase: " << std::endl;
//	one.dump(true);
	for (LIST_TYPE<int>::const_iterator ci = one.begin(); ci != one.end(); ++ci) {
		std::cout << "one-pre-erase: " << *ci << std::endl;
	}
	one.erase(one.begin());
	std::cout << "One post-erase: " << std::endl;
//	one.dump(true);
	for (LIST_TYPE<int>::const_iterator ci = one.begin(); ci != one.end(); ++ci) {
		std::cout << "one-pre-erase: " << *ci << std::endl;
	}

	for (int i=10; i<=70; i+=10)
		list.push_back(i);

	std::cout << "\n\nList pre-random-deletes: \n" << std::endl;
	//list.dump();
	for (LIST_TYPE<int>::const_iterator ci = list.begin(); ci != list.end(); ++ci) {
		std::cout << "List pre-random-deletes: " << *ci << std::endl;
	}
	std::cout << std::endl;

	LIST_TYPE<int>::iterator del_i; 
	del_i = list.begin(); list.erase(del_i);			// Delete first element
	del_i = list.begin(); ++del_i; list.erase(del_i);	// Delete second element
	del_i = list.end(); --del_i; list.erase(del_i);		// Delete last element
	del_i = list.end(); --del_i; --del_i; --del_i; list.erase(del_i); // Delete middle(?) element

	std::cout << "\n\nList post-random-deletes: \n" << std::endl;
//	list.dump();
	for (LIST_TYPE<int>::const_iterator ci = list.begin(); ci != list.end(); ++ci) {
		std::cout << "List post-random-deletes: " << *ci << std::endl;
	}

	std::cout << "\n\ncpy pre-range-erase: \n" << std::endl;
	for (LIST_TYPE<int>::const_iterator ci = cpy.begin(); ci != cpy.end(); ++ci) {
		std::cout << "cpy pre-range-erase: " << *ci << std::endl;
	}
	//cpy.dump();
	LIST_TYPE<int>::iterator cpy_before_end = --cpy.end();
	cpy.erase(cpy.begin(), cpy_before_end);
	std::cout << "\n\ncpy post-range-erase: \n" << std::endl;
	//cpy.dump();
	for (LIST_TYPE<int>::const_iterator ci = cpy.begin(); ci != cpy.end(); ++ci) {
		std::cout << "cpy post-range-erase: " << *ci << std::endl;
	}
	//
	// Start insert tests
	//

	std::cout << "\n\nList pre-insert: \n" << std::endl;
	for (LIST_TYPE<int>::const_iterator ci = list.begin(); ci != list.end(); ++ci) {
		std::cout << "List pre-insert: " << *ci << std::endl;
	}

	it = list.begin();
	list.insert(it, 1000); // Insert at start
	
	it = list.end();
	list.insert(it, 9000); // Insert at end
	it = ++list.begin(); ++it; ++it;
	list.insert(it, 5000); // Insert in the middle
	list.insert(list.begin(), 400); // Insert at the start again

	std::cout << "\n\nList post-insert: \n" << std::endl;
	for (LIST_TYPE<int>::const_iterator ci = list.begin(); ci != list.end(); ++ci) {
		std::cout << "List post-insert: " << *ci << std::endl;
	}

	// "Mass insert" tests

	list.insert(list.end(), list_1234.begin(), list_1234.end());

	std::cout << "\n\nList post-insert-1234 (size " << list.size() << "): \n" << std::endl;
	for (LIST_TYPE<int>::const_iterator ci = list.begin(); ci != list.end(); ++ci) {
		std::cout << "List post-insert-1234: " << *ci << std::endl;
	}

	//
	// Remove tests
	//
	list.remove(3);
	std::cout << "\n\nList post-remove-3 (size " << list.size() << "): \n" << std::endl;
	for (LIST_TYPE<int>::const_iterator ci = list.begin(); ci != list.end(); ++ci) {
		std::cout << "List post-remove-3: " << *ci << std::endl;
	}

	return 0;
}

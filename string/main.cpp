#include <iostream>
#include <algorithm>
#include <string>
#include "string.hpp"

int main() {
	exscape::string s = "FABECDA";
	exscape::string::iterator i = s.begin();
	for (i = s.begin(); i != s.end(); ++i)
		std::cout << *i << std::endl;

	std::sort(s.begin(), s.end());
	std::cout << "Sorted: " << s << std::endl;

	std::cout << "Count of A in \"" << s << "\": " << std::count(s.begin(), s.end(), 'A') << std::endl;
	std::cout << "Count of B in \"" << s << "\": " << std::count(s.begin(), s.end(), 'B') << std::endl;
	std::cout << "Count of X in \"" << s << "\": " << std::count(s.begin(), s.end(), 'X') << std::endl;



	exscape::string str = "ABCDEF";
	exscape::string::iterator b = str.begin(), e = str.end()-2;
	std::cout << "AE: " << *b << *e << std::endl; // breakpoint line



	// Permutation test
	exscape::string perm = "012";
	do {
		std::cout << "Permutation: " << perm << std::endl;
	} while (next_permutation(perm.begin(), perm.end()));

	// Copy test
	exscape::string src = "ABCDEF";
	exscape::string dest;
//	std::string dest;
	dest.resize(src.length());
	std::cout << "src length: " << src.length() << ", dest capacity: " << dest.capacity() << std::endl;
	std::copy(src.begin(), src.end(), dest.begin());
	std::cout << "Source: " << src << ", copy: " << dest << std::endl;

	return 0;
}

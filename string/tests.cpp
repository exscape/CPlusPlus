#include <iostream>
#include <algorithm>
#include <string>
#include "string.hpp"

#define STR_TYPE exscape
//#define STR_TYPE std

char swap_case (char in) {
	return in ^ 0x20;
}

int main() {
	// Simple forward iterator test
	STR_TYPE::string s = "FABECDA";
	STR_TYPE::string::iterator i = s.begin();
	for (i = s.begin(); i != s.end(); ++i)
		std::cout << *i << std::endl;

	// std::sort test
	std::sort(s.begin(), s.end());
	std::cout << "Sorted: " << s << std::endl;

	// std::count test
	std::cout << "Count of A in \"" << s << "\": " << std::count(s.begin(), s.end(), 'A') << std::endl;
	std::cout << "Count of B in \"" << s << "\": " << std::count(s.begin(), s.end(), 'B') << std::endl;
	std::cout << "Count of X in \"" << s << "\": " << std::count(s.begin(), s.end(), 'X') << std::endl;

	// End iterator backwards seek test
	STR_TYPE::string str = "ABCDEF";
	STR_TYPE::string::iterator b = str.begin(), e = str.end()-2;
	std::cout << "AE: " << *b << *e << std::endl; // breakpoint line

	// std::next_permutation test
	STR_TYPE::string perm = "012";
	do {
		std::cout << "Permutation: " << perm << std::endl;
	} while (next_permutation(perm.begin(), perm.end()));

	// std::copy test
	const STR_TYPE::string src = "ABCDEF";
	STR_TYPE::string dest;
	dest.resize(src.length());
	std::cout << "src length: " << src.length() << ", dest capacity: " << dest.capacity() << std::endl;
	std::copy(src.begin(), src.end(), dest.begin());
	std::cout << "Source: " << src << ", copy: " << dest << std::endl;

	// std::transform test
	const STR_TYPE::string trans_src = "Testing";
	STR_TYPE::string trans_dest;
	trans_dest.resize(trans_src.length());
	std::transform(trans_src.begin(), trans_src.end(), trans_dest.begin(), swap_case);
	std::cout << "Transform: in=" << trans_src << ", out=" << trans_dest << std::endl;

	// std::remove_copy test
	const STR_TYPE::string remove_str = "ABCDEF";
	STR_TYPE::string remove_dest;
	remove_dest.resize(remove_str.length());
	std::remove_copy(remove_str.begin(), remove_str.end(), remove_dest.begin(), 'C');

	std::cout << "remove_copy: in=" << remove_str << ", out=" << remove_dest << std::endl;

	// std::reverse test
	STR_TYPE::string reverse_str = "ABCDEF";
	std::cout << "std::reverse: in=" << reverse_str;
	std::reverse(reverse_str.begin(), reverse_str.end());
	std::cout << ", out=" << reverse_str << std::endl;

	// constness test - FAILS, the iterator shouldn't be allowed to change the string (or even be created)
	const STR_TYPE::string c = "ABCDEF";
	STR_TYPE::string::iterator c_iter = c.begin();
	*c_iter = 'X';
	std::cout << c << std::endl;

	return 0;
}
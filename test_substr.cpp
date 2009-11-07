#include <iostream>
#include "string.cpp"

/* The following was ported from C, with some minor rewrites rather than a C++ish way, so it's not very pretty... */

size_t /* num_errors */ test_substr(const exscape::string str, ssize_t start, ssize_t length, const char *expect) {
	exscape::string sub;
	try {
		sub = str.substr(start, length);
	}
	catch (std::out_of_range &e) {
		std::cerr << "FAIL1 in " << str << ".substr(" << start << ", " << length << "), caught exception \"" << e.what() << "\", expected \"" << expect << "\"" << std::endl;
		return 1;
	}
	catch (std::exception &e) {
		std::cerr << "Caught unknown exception!" << std::endl;
	}

	if (sub == NULL && strcmp(expect, "")) {
		std::cerr << "FAIL2 in " << str << ".substr(" << start << ", " << length << "), got NULL, expected \"" << expect << "\"" << std::endl;
		return 1;
	}
	else if (sub == NULL) {
		std::cerr << "FAIL3 in " << str << ".substr(" << start << ", " << length << "), got NULL, expected \"" << expect << "\"" << std::endl;
		return 1;
	}

	if (strcmp(sub.c_str(), expect) != 0 && strcmp(expect, "")) {
		std::cerr << "FAIL4 in " << str << ".substr(" << start << ", " << length << "), got \"" << sub << "\", expected \"" << expect << "\"" << std::endl;
		return 1;
	}
	else {
		std::cerr << "PASS in " << str << ".substr(" << start << ", " << length << "), got \"" << sub << "\", expected \"" << expect << "\"" << std::endl;
		return 0;
	}
}

void test_substr_all(void) {
	size_t errcount = 0;
	exscape::string str = "ABCDEF";

	std::cout << "Positive start tests:\n";
	errcount += test_substr(str, 0, 6, "ABCDEF");
	errcount += test_substr(str, 1, 5, "BCDEF");
	errcount += test_substr(str, 0, 3, "ABC");
	errcount += test_substr(str, 4, 2, "EF");
	errcount += test_substr(str, 5, 1, "F");
	errcount += test_substr(str, 3, 2, "DE");
	errcount += test_substr("Hello, world!", 1, 4, "ello");
	errcount += test_substr("1 2 3, anyone there?", 2, 1, "2");
	if (errcount == 0)
		std::cout << "All OK\n";

	std::cout << "\n";
	std::cout << "Negative start tests:\n";
	errcount += test_substr(str, -3, 1, "D");
	errcount += test_substr(str, -4, 3, "CDE");
	errcount += test_substr(str, -4, 1, "C");
	errcount += test_substr(str, -5, 1, "B");
	errcount += test_substr(str, -6, 6, "ABCDEF");
	errcount += test_substr("Testing, testing", -7, 4, "test");
	if (errcount == 0)
		std::cout << "All OK\n";

	std::cout << "\n";
	std::cout << "Zero length tests:\n";
	errcount += test_substr(str, 0, 0, "ABCDEF");
	errcount += test_substr(str, 1, 0, "BCDEF");
	errcount += test_substr(str, 4, 0, "EF");
	errcount += test_substr(str, 5, 0, "F");
	errcount += test_substr("", 0, 0, "");
	if (errcount == 0)
		std::cout << "All OK\n";

	std::cout << "\n";
	std::cout << "Zero length AND negative start tests:\n";
	errcount += test_substr(str, -1, 0, "F");
	errcount += test_substr(str, -4, 0, "CDEF");
	errcount += test_substr(str, -2, 0, "EF");
	if (errcount == 0)
		std::cout << "All OK\n";

	std::cout << "\n";
	std::cout << "Negative length (and also start) tests:\n";
	errcount += test_substr(str, 0, -1, "ABCDE");
	errcount += test_substr(str, 0, -3, "ABC");
	errcount += test_substr(str, 0, -4, "AB");
	errcount += test_substr(str, 2, -1, "CDE");
	errcount += test_substr(str, -3, -1, "DE");
	errcount += test_substr(str, 4, -1, "E");
	errcount += test_substr(str, 0, -6, "");
	if (errcount == 0)
		std::cout << "All OK\n";
/*
	std::cout << "\n";
	std::cout << "The following should fail:\n";
	test_substr(str, 6, 2, "(null)");
	test_substr(str, 1, 10, "(null)");
	test_substr(str, -10, 0, "(null)");
	test_substr(str, -10, 12, "(null)");
	test_substr(str, -7, 3, "(null)");
	test_substr(str, 0, -7, "(null)");
	test_substr(str, -3, -4, "(null)");
	test_substr(str, 4, -4, "(null)"); // this would return "" in PHP, but screw that.
*/
	std::cout << "Done testing substr(), " << errcount << " errors" << std::endl;
}
int main() {
	test_substr_all();
	return 0;
}


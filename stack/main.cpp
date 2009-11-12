#include <iostream>
#include <string>
#include "stack.hpp"

int main() {
	exscape::stack<int> s;
	s.push(10);

	s.dump();

	return 0;
}

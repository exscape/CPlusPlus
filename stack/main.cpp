#include <iostream>
#include <string>
#include "stack.hpp"

int main() {
	exscape::stack<int> s;
	s.push(10);
	s.push(20);
	s.push(30);
	s.dump();
	s.pop();
	s.dump();

	return 0;
}

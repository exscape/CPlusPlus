#include <iostream>
#include <exception>
#include "stack.hpp"

/*
 * This file implements a stack with automatic memory management, based on linked lists.
 * Its sole purpose is for me to learn C++, and I do know about std::stack.
 */

/* Written: 2009-11-02, 2009-11-03, XXX */

namespace exscape {
	class stack {

		typedef struct _node {
			struct _node *next;
			int data;
		} node;

		private:
			node *head;

		public:
			stack();
			~stack();
			size_t size(void);
			void push(int const &elem);
			int pop(void);
			void free();
			int &top(void);
	};

	stack::stack() {
		std::cout << "Hello, stack!" << std::endl;
		this->head = NULL;
	}

	stack::~stack() {
		stack::free();
		std::cout << "Goodbye, stack." << std::endl;
	}

	size_t stack::size(void) {
		size_t len = 0;
		for (node *n = this->head; n != NULL; n = n->next)
			len++;

		return len;
	}

	void stack::push(int const &elem) {
		node *n = new node;
		n->data = elem;
		n->next = this->head;
		this->head = n;
		std::cout << "Push " << elem << std::endl;
	}

	int stack::pop(void) {
		if (stack::size() == 0)
			throw StackUnderflowException();

		int data = this->head->data;
		node *new_head = this->head->next;
		delete this->head;
		this->head = new_head;

		return data;
	}

	int &stack::top(void) {
		if (stack::size() == 0)
			throw StackUnderflowException();
		int &data = this->head->data;
		return data;
	}

	void stack::free() {
		node *cur = this->head;
		node *next;
		while (cur != NULL) {
			next = cur->next;
			delete cur;
			cur = next;
		}
		this->head = NULL;
	}
}

int main() {
	exscape::stack *s = new exscape::stack;
	s->push(10);
	s->push(20);
	s->push(30);
//	std::cout << "Pop " << s->pop() << std::endl;
//	std::cout << "Pop " << s->pop() << std::endl;
//	std::cout << "Pop " << s->pop() << std::endl;
	try {
		std::cout << "Pop " << s->pop() << std::endl; // One pop too much
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "Top: " << s->top() << std::endl;
	s->top() -= 3;
	std::cout << "Top is now " << s->top() << std::endl;
	std::cout << "Pop " << s->pop() << std::endl;
	delete s;
	return 0;
}

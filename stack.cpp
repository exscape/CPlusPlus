#include <iostream>
#include <exception>
#include "stack.hpp"

/*
 * This file implements a stack with automatic memory management, based on linked lists.
 * Its sole purpose to teach me C++; I do know about std::stack.
 */

/* Written: 2009-11-02, 2009-11-03, XXX */

namespace exscape {
	template <typename Type>
	class stack {

		typedef struct _node {
			struct _node *next;
			Type data;
		} node;

		private:
			node *head;

		public:
			stack();
			stack(Type const &elem);
			~stack();
			void init(void);
			size_t size(void);
			void push(Type const &elem);
			Type pop(void);
			void free();
			Type &top(void);
	};

	template <typename Type> void stack<Type>::init() {
		this->head = NULL;
	}
	template <typename Type> stack<Type>::stack() {
		std::cout << "Hello, stack!" << std::endl;
		stack::init();
	}

	template <typename Type> stack<Type>::stack(Type const &elem) {
		stack::init();
		std::cout << "Hello, stack, with an argument!" << std::endl;
		stack::push(elem);
	}

	template <typename Type> stack<Type>::~stack() {
		stack::free();
		std::cout << "Goodbye, stack." << std::endl;
	}

	template <typename Type> size_t stack<Type>::size(void) {
		size_t len = 0;
		for (node *n = this->head; n != NULL; n = n->next)
			len++;

		return len;
	}

	template <typename Type> void stack<Type>::push(Type const &elem) {
		node *n = new node;
		n->data = elem;
		n->next = this->head;
		this->head = n;
		std::cout << "Push " << elem << std::endl;
	}

	template <typename Type> Type stack<Type>::pop(void) {
		if (stack::size() == 0)
			throw StackUnderflowException();

		Type data = this->head->data;
		node *new_head = this->head->next;
		delete this->head;
		this->head = new_head;

		return data;
	}

	template <typename Type> Type &stack<Type>::top(void) {
		if (stack::size() == 0)
			throw StackUnderflowException();
		Type &data = this->head->data;
		return data;
	}

	template <typename Type> void stack<Type>::free() {
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
	exscape::stack<std::string> *s = new exscape::stack<std::string>;
//	exscape::stack<std::string> *s = new exscape::stack<std::string>("First");
	s->push(std::string("Alpha"));
	s->push(std::string("Beta"));
	s->push(std::string("Gamma"));
	try {
		std::cout << "Pop " << s->pop() << std::endl;
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "Top: " << s->top() << std::endl;
	std::cout << "Pop " << s->pop() << std::endl;
	delete s;
	return 0;
}

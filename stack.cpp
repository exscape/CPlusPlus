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

		/*
		 * The linked list struct that holds all the data.
		 */
		typedef struct _node {
			struct _node *next;
			Type data;
		} node;

		private:
			node *head;
			size_t _size;
			void init(void);
			void free();

		public:
		/* Constructors */
			stack();
			stack(Type const &elem);
			stack(stack<Type> const &other);
		/* Descructor */
			~stack();
		/* Various public functions */
			size_t size(void) const;
			void push(Type const &elem);
			Type pop(void);
			Type &top(void) const;
			void dump(void) const; // For debugging purposes
			bool operator==(const stack<Type> &other) const;
			bool operator!=(const stack<Type> &other) const;
			stack<Type> & operator=(const stack<Type> &other);
	};

	template <typename Type> void stack<Type>::init() {
		std::cout << "In init() for stack " << this << std::endl;
		this->head = NULL;
		this->_size = 0;
	}

	template <typename Type> stack<Type>::stack() {
		std::cout << "Hello, stack!" << std::endl;
		this->init();
	}

	template <typename Type> stack<Type>::stack(Type const &elem) {
		std::cout << "Hello, stack, with an argument!" << std::endl;
		this->init();
		this->push(elem);
	}

	template <typename Type> stack<Type>::stack(stack<Type> const &other) {
		std::cout << "In copy constructor" << std::endl;
		this->init();

		// XXX: MEMORY WASTING!
		Type *arr = new Type[other._size];
		int i = 0;
		for (node *n = other.head; n != NULL; n = n->next, i++) {
			arr[i] = n->data;
		}

		for (int j = i-1; j >= 0; j--)
			this->push(arr[j]);

		delete [] arr;
	}

	template <typename Type> stack<Type>::~stack() {
		this->free();
		std::cout << "Goodbye, stack " << this << "." << std::endl;
	}

	template <typename Type> size_t stack<Type>::size(void) const {
		return this->_size;
	}

	template <typename Type> void stack<Type>::push(Type const &elem) {
		node *n = new node;
		n->data = elem;
		n->next = this->head;
		this->head = n;
		std::cout << "Stack " << this << ": push " << elem << std::endl;
		this->_size++;
	}

	template <typename Type> Type stack<Type>::pop(void) {
		if (this->size() == 0)
			throw StackUnderflowException();

		Type data = this->head->data;
		node *new_head = this->head->next;
		delete this->head;
		this->head = new_head;
		this->_size--;

		return data;
	}

	template <typename Type> Type &stack<Type>::top(void) const {
		if (this->size() == 0)
			throw StackUnderflowException();
		Type &data = this->head->data;
		return data;
	}

	template <typename Type> void stack<Type>::free(void) {
		node *cur = this->head;
		node *next;
		while (cur != NULL) {
			next = cur->next;
			delete cur;
			cur = next;
		}
		this->_size = 0;
		this->head = NULL;
	}

	template <typename Type> void stack<Type>::dump(void) const {
		std::cout << std::endl << "Dumping stack at " << this << ":" << std::endl;
		for (node *n = this->head; n != NULL; n = n->next) {
			std::cout << n->data << std::endl;
		}
		std::cout << "Done dumping stack at " << this << "." << std::endl << std::endl;
	}
	template <typename Type> bool stack<Type>::operator==(const stack<Type> &other) const {
		std::cout << "Comparing stack " << this << " with stack " << &other << std::endl;
		if (this == &other)
			return true;
		if (this->size() != other.size())
			return false;

		node *a = this->head;
		node *b = other.head;
		for (; a != NULL; a = a->next, b = b->next) {
			if (a->data != b->data)
				return false;
		}

		return true;
	}

	template <typename Type> bool stack<Type>::operator!=(const stack<Type> &other) const {
		return !(*this == other);
	}

	template <typename Type> stack<Type> & stack<Type>::operator=(const stack<Type> &other) {
		std::cout << "In operator= for stacks " << this << " and " << &other << std::endl;
		if (this == &other)
			return *this;

		this->free();
		if (other.size() == 0)
			return *this; // Other stack is empty, so we're done

		// XXX: MEMORY WASTING + DRY!
		Type *arr = new Type[other._size];
		int i = 0;
		for (node *n = other.head; n != NULL; n = n->next, i++) {
			arr[i] = n->data;
		}

		for (int j = i-1; j >= 0; j--)
			this->push(arr[j]);

		delete [] arr;

		return *this;
	}
}

int main() {
	exscape::stack<std::string> s;
	s.push(std::string("Alpha"));
	s.push(std::string("Beta"));
	s.push(std::string("Gamma"));
	s.dump();

	exscape::stack<std::string> s2;
	s2 = s;
	if (s != s2)
		std::cout << "Just copied stacks ARE NOT equal!" << std::endl;
	else
		std::cout << "Just copied stacks are equal; all is well." << std::endl;

	s.pop();
	if (s != s2)
		std::cout << "Stacks aren't equal anymore; things are as they should be" << std::endl;

	s.dump();
	s2.dump();

	return 0;
}

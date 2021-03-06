#ifndef _OLD_STACK_HPP
#define _OLD_STACK_HPP

#include <iostream>
#include <stdexcept>
#include <exception> // Unnecessary?

#ifndef DEBUG
#define DEBUG 0
#endif

/*
 * This file implements a stack with automatic memory management, based on linked lists.
 * Its sole purpose to teach me C++; I do know about std::stack.
 */

/* Written: 2009-11-02, 2009-11-03, 2009-11-04, 2009-11-12 (refactoring), XXX */

namespace exscape {
	class StackUnderflowException : public std::runtime_error {
		public:
			StackUnderflowException() : std::runtime_error("StackUnderflowException") {}
	};

	template <typename Type>
	class stack {
		private:
		/* The linked list struct that holds all the data. */
		typedef struct _node {
			struct _node *next;
			Type data;
		} node;

		protected:
		/* Member variables */
			node *head;
			size_t _size;
		/* Protected methods */
			void init(void);
			void free();
			static void copy(stack<Type> &dst, const stack<Type> &src);

		public:
		/* Constructors */
			stack();
			stack(const Type &elem);
			stack(const stack<Type> &other);
		/* Destructor */
			~stack();
		/* Various public methods */
			size_t size(void) const;
			bool empty(void) const;
			void push(const Type &elem);
			Type pop(void);
			Type &top(void);
			void dump(void) const; // For debugging purposes
		/* Overloaded operators */
			bool operator==(const stack<Type> &other) const;
			bool operator!=(const stack<Type> &other) const;
			stack<Type> & operator=(const stack<Type> &other);
	};

	/* A STATIC class method that copies one stack to another */
	template <typename Type> void stack<Type>::copy(stack<Type> &dst, const stack<Type> &src) {
		if (DEBUG) std::cerr << "In stack::copy() for destination stack=" << &dst << " and source stack=" << &src << std::endl;
		
		if (&dst == &src) /* Don't copy self to self */
			return;
		
		if (src.size() == 0)
			return; // We're copying an empty stack - we have an empty stack. Our work here is done.
		
		node *tail = NULL; // Pointer to the last element in the new list
		for (node *src_node = src.head; src_node != NULL; src_node = src_node->next, dst._size++) {
			if (dst.head == NULL) { // First node
				dst.head = new node;
				dst.head->data = src_node->data;
				dst.head->next = NULL;
				tail = dst.head;
			}
			else { // Any other node
				tail->next = new node;
				tail = tail->next;
				tail->data = src_node->data;
				tail->next = NULL;
			}
		}

		// XXX: DEBUGGING ONLY!
		if (dst.size() != src.size()) {
			std::cerr << "COPY FAILED! Sizes differ!" << std::endl;
		}

		// XXX: DEBUGGING ONLY!
		if (dst != src) {
			std::cerr << "COPY FAILED! operator!= returned true!" << std::endl;
		}
		else
			if (DEBUG) std::cerr << "Copy successful!" << std::endl;
	}

	/* Initialize the member variables to an empty stack-state */
	template <typename Type> void stack<Type>::init() {
		if (DEBUG) std::cerr << "In init() for stack " << this << std::endl;
		this->head = NULL;
		this->_size = 0;
	}

	/* Default constructor; create an empty stack */
	template <typename Type> stack<Type>::stack() {
		if (DEBUG) std::cerr << "Hello, stack " << this << "!" << std::endl;
		this->init();
	}

	/* Create a stack containing "elem" */
	template <typename Type> stack<Type>::stack(const Type &elem) {
		if (DEBUG) std::cerr << "Hello, stack " << this << ", with an argument!" << std::endl;
		this->init();
		this->push(elem);
	}

	/* Copy constructor; create an exact copy of "other" */
	template <typename Type> stack<Type>::stack(const stack<Type> &other) {
		if (DEBUG) std::cerr << "In copy constructor for stack " << this << std::endl;
		this->init();
		stack::copy(*this, other);
	}

	/* Destructor */
	template <typename Type> stack<Type>::~stack() {
		this->free();
		if (DEBUG) std::cerr << "Goodbye, stack " << this << "." << std::endl;
	}

	/* Returns the list size/length */
	template <typename Type> size_t stack<Type>::size(void) const {
		return this->_size;
	}

	template <typename Type> bool stack<Type>::empty(void) const {
		return (this->_size == 0);
	}

	/* Adds an element to the top of the stack */
	template <typename Type> void stack<Type>::push(const Type &elem) {
		node *n = new node;
		n->data = elem;
		n->next = this->head;
		this->head = n;
		if (DEBUG) std::cerr << "Stack " << this << ": push " << elem << std::endl;
		this->_size++;
	}

	/* Removes the top element and returns it - if one exists */
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

	/* Returns a reference to the top element, without removing it */
	template <typename Type> Type &stack<Type>::top(void) {
		if (this->size() == 0)
			throw StackUnderflowException();
		Type &data = this->head->data;
		return data;
	}

	/* Frees the memory for the storage list and (re)sets size to 0 */
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

	/* Dump the contents of the stack, if possible with the type contained; used for debugging */
	template <typename Type> void stack<Type>::dump(void) const {
		std::cerr << std::endl << "Dumping stack at " << this << ":" << std::endl;
		for (node *n = this->head; n != NULL; n = n->next) {
			std::cerr << n->data << std::endl;
		}
		if (DEBUG) std::cerr << "Done dumping stack at " << this << "." << std::endl << std::endl;
	}

	/* operator==, check if two stacks are equal (in size, elements and order) */
	template <typename Type> bool stack<Type>::operator==(const stack<Type> &other) const {
		if (DEBUG) std::cerr << "Comparing stack " << this << " with stack " << &other << std::endl;
		if (this == &other)
			return true;
		if (this->size() != other.size())
			return false;

		node *a = this->head;
		node *b = other.head;
		for (; b != NULL; a = a->next, b = b->next) {
			if (a->data != b->data)
				return false;
		}

		return true;
	}

	/* operator!=, check if two stacks are NOT equal - see operator== above */
	template <typename Type> bool stack<Type>::operator!=(const stack<Type> &other) const {
		return !(*this == other);
	}

	/* operator=, replace the contents of this stack with "other" */
	template <typename Type> stack<Type> & stack<Type>::operator=(const stack<Type> &other) {
		if (DEBUG) std::cerr << "In operator= for stacks " << this << " and " << &other << std::endl;
		if (this == &other)
			return *this;

		this->free();
		if (other.size() == 0)
			return *this; // Other stack is empty, so we're done

		stack::copy(*this, other);
		return *this;
	}
} // end namespace
#endif

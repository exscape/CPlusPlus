#ifndef _STANDALONE_STACK_HPP
#define _STANDALONE_STACK_HPP

#include <iostream>
#include <typeinfo>

#ifndef DEBUG
#define DEBUG 2
#endif

/* Written: 2009-11-02, 2009-11-03, 2009-11-04, 2009-11-12 (refactoring), 2009-11-19 (remake to use any container), XXX */

namespace exscape {
	template <typename Type, class Container>
	class stack {
		private:
			Container storage;

		public:
		/* Constructors */
			stack();
			stack(const Type &elem);
			//stack(const stack<Type> &other);
		/* Destructor */
			~stack();
		/* Various public methods */
			size_t size(void) const;
			bool empty(void) const;
			void push(const Type &elem);
			void pop(void);
			Type &top(void);
			const Type &top(void) const;
			void clear();
			void dump(void); // For debugging purposes
		/* Overloaded operators */
//			bool operator==(const stack<Type> &other) const;
//			bool operator!=(const stack<Type> &other) const;
//			stack<Type> & operator=(const stack<Type> &other);
	};

	/* Default constructor; create an empty stack */
	template <typename Type, typename Container> stack<Type, Container>::stack() {
		if (DEBUG) std::cerr << "Hello, stack " << this << "! Container type = " << typeid(Container).name() << std::endl;
	}

	/* Create a stack containing "elem" */
	template <typename Type, typename Container> stack<Type, Container>::stack(const Type &elem) {
		if (DEBUG) std::cerr << "Hello, stack " << this << ", with an argument!" << std::endl;
		this->push(elem);
	}

	/* Copy constructor; create an exact copy of "other" */
/*
	template <typename Type, typename Container> stack<Type, Container>::stack(const stack<Type, Container> &other) {
		if (DEBUG) std::cerr << "In copy constructor for stack " << this << std::endl;
		this->init();
		stack::copy(*this, other);
	}
*/

	/* Destructor */
	template <typename Type, typename Container> stack<Type, Container>::~stack() {
		this->clear();
		if (DEBUG) std::cerr << "Goodbye, stack " << this << "." << std::endl;
	}

	/* Returns the list size/length */
	template <typename Type, typename Container> inline size_t stack<Type, Container>::size(void) const {
		return storage.size();
	}

	template <typename Type, typename Container> inline bool stack<Type, Container>::empty(void) const {
		return (this->size() == 0);
	}

	/* Adds an element to the top of the stack */
	template <typename Type, typename Container> inline void stack<Type, Container>::push(const Type &elem) {
		storage.push_back(elem);
		if (DEBUG) std::cerr << "Stack " << this << ": push " << elem << std::endl;
	}

	/* Removes the top element and returns it - if one exists */
	template <typename Type, typename Container> void stack<Type, Container>::pop(void) {
		if (this->size() == 0)
			return; // XXX: Exception?

		this->storage.pop_back();
	}

	/* Returns a reference to the top element, without removing it */
	template <typename Type, typename Container> Type &stack<Type, Container>::top(void) {
		if (this->size() == 0)
			throw StackUnderflowException();

		return storage.back();
	}

	/* Returns a reference to the top element, without removing it */
	template <typename Type, typename Container> const Type &stack<Type, Container>::top(void) const {
		if (this->size() == 0)
			throw StackUnderflowException();

		return storage.back();
	}

	/* Frees the memory for the storage list and (re)sets size to 0 */
	template <typename Type, typename Container> void stack<Type, Container>::clear(void) {
		storage.clear(); // XXX: Does this work with std:: classes?
	}

	/* Dump the contents of the stack, if possible with the type contained; used for debugging */
	template <typename Type, typename Container> void stack<Type, Container>::dump(void) {
		std::cerr << std::endl << "Dumping AND CLEARING stack at " << this << ":" << std::endl;
		while (!this->empty()) {
			std::cout << this->top() << std::endl;
			this->pop();
		}

		if (DEBUG) std::cerr << "Done dumping stack at " << this << "." << std::endl << std::endl;
	}

	/* operator==, check if two stacks are equal (in size, elements and order) */
/*
	template <typename Type, typename Container> bool stack<Type, Container>::operator==(const stack<Type, Container> &other) const {
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
*/
	/* operator!=, check if two stacks are NOT equal - see operator== above */
/*
	template <typename Type, typename Container> bool stack<Type, Container>::operator!=(const stack<Type, Container> &other) const {
		return !(*this == other);
	}
*/

	/* operator=, replace the contents of this stack with "other" */
/*
	template <typename Type, typename Container> stack<Type, Container> & stack<Type, Container>::operator=(const stack<Type, Container> &other) {
		if (DEBUG) std::cerr << "In operator= for stacks " << this << " and " << &other << std::endl;
		if (this == &other)
			return *this;

		this->free();
		if (other.size() == 0)
			return *this; // Other stack is empty, so we're done

		stack::copy(*this, other);
		return *this;
	}
*/
} // end namespace
#endif

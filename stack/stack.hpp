#ifndef _STACK_HPP
#define _STACK_HPP

#include <iostream>
#include <stdexcept>
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

		protected:
			void clear();

		public:
		/* Constructors */
			stack();
			stack(const Container &);
		/* Destructor */
			~stack();
		/* Various public methods */
			size_t size(void) const;
			bool empty(void) const;
			void push(const Type &elem);
			void pop(void);
			Type &top(void);
			const Type &top(void) const;
			void dump(void); // For debugging purposes
		/* Overloaded operators */
			bool operator==(const stack<Type, Container> &other) const;
			bool operator!=(const stack<Type, Container> &other) const;
			stack<Type, Container> & operator=(const stack<Type, Container> &other);
	};

	/* Default constructor; create an empty stack */
	template <typename Type, typename Container> stack<Type, Container>::stack() {
		if (DEBUG) std::cerr << "Hello, stack " << this << "! Container type = " << typeid(Container).name() << std::endl;
	}

	/* Create a stack with the contents of an existing container */
	template <typename Type, typename Container> stack<Type, Container>::stack(const Container &other) {
		if (DEBUG) std::cerr << "In copy constructor for stack " << this << std::endl;
		this->storage = other;
	}

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
			throw std::out_of_range("Stack underflow in stack::top()");

		return storage.back();
	}

	/* Returns a reference to the top element, without removing it */
	template <typename Type, typename Container> const Type &stack<Type, Container>::top(void) const {
		if (this->size() == 0)
			throw std::out_of_range("Stack underflow in stack::top");

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

		if (DEBUG) std::cerr << "Done dumping AND CLEARING stack at " << this << "." << std::endl << std::endl;
	}

	/* operator==, check if two stacks are equal (in size, elements and order) */
	template <typename Type, typename Container> bool stack<Type, Container>::operator==(const stack<Type, Container> &other) const {
		if (DEBUG) std::cerr << "Comparing stack " << this << " with stack " << &other << std::endl;
		if (this == &other)
			return true;
		if (this->size() != other.size())
			return false;
		
		return (this->storage == other.storage);
	}

	/* operator!=, check if two stacks are NOT equal - see operator== above */
	template <typename Type, typename Container> bool stack<Type, Container>::operator!=(const stack<Type, Container> &other) const {
		return !(*this == other);
	}

	/* operator=, replace the contents of this stack with "other" */
	template <typename Type, typename Container> stack<Type, Container> & stack<Type, Container>::operator=(const stack<Type, Container> &other) {
		if (DEBUG) std::cerr << "In operator= for stacks " << this << " and " << &other << std::endl;
		if (this == &other)
			return *this;

		this->clear();
		if (other.size() == 0)
			return *this; // Other stack is empty, so we're done

		this->storage = other.storage;
		return *this;
	}
} // end namespace
#endif

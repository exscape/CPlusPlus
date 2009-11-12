#ifndef _STACK_HPP
#define _STACK_HPP

#include <iostream>
#include <stdexcept>
#include <exception> // Unnecessary?

#ifndef DEBUG
#define DEBUG 0
#endif

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
			static void copy(stack<Type> &dst, stack<Type> const &src);

		public:
		/* Constructors */
			stack();
			stack(Type const &elem);
			stack(stack<Type> const &other);
		/* Destructor */
			~stack();
		/* Various public methods */
			size_t size(void) const;
			bool empty(void) const;
			void push(Type const &elem);
			Type pop(void);
			Type &top(void);
			void dump(void) const; // For debugging purposes
		/* Overloaded operators */
			bool operator==(const stack<Type> &other) const;
			bool operator!=(const stack<Type> &other) const;
			stack<Type> & operator=(const stack<Type> &other);
	};
} // end namespace

#endif

#ifndef _LINKEDLIST_HPP
#define _LINKEDLIST_HPP

#include <iostream> /* debugging */
#include <assert.h>

#ifndef DEBUG
#define DEBUG 1
#endif

namespace exscape {
	template <typename Type>
	class LinkedList {
		private:
			struct node {
				struct node *next;
				Type data;
			};

		public:
			LinkedList();
			~LinkedList();
			void init();
			void clear();
			void prepend(const Type &);
			void append(const Type &);
			void dump() const; // XXX: Debugging only, until iterator support is added

		private:
			struct node *head;
			struct node *tail;
	};

	template <typename Type> LinkedList<Type>::LinkedList() : head(NULL), tail(NULL) {
		if (DEBUG) std::cerr << "Hello, LinkedList " << this << std::endl;
	}

	template <typename Type> LinkedList<Type>::~LinkedList() {
		if (DEBUG) std::cerr << "Goodbye, LinkedList " << this << std::endl;
		this->clear();
	}

	template <typename Type> void LinkedList<Type>::init() {
		// XXX: Is this function required?
		if (DEBUG) std::cerr << "In LinkedList::init() for list " << this << std::endl;
	}

	template <typename Type> void LinkedList<Type>::clear() {
		if (DEBUG) std::cerr << "In LinkedList::clear() for list " << this << std::endl;
		/* Free memory, reset all pointers */ 
	}

	template <typename Type> void LinkedList<Type>::prepend(const Type &obj) {
		if (DEBUG) std::cerr << "In LinkedList::prepend(" << obj << ") for list " << this << std::endl;
		node *new_node = new node;
		new_node->next = this->head;
		new_node->data = obj;
		this->head = new_node;
		if (this->tail == NULL) {
			if (DEBUG) std::cerr << " setting tail to head" << std::endl;
			this->tail = this->head;
		}
	}

	template <typename Type> void LinkedList<Type>::append(const Type &obj) {
		if (DEBUG) std::cerr << "In LinkedList::append(" << obj << ") for list " << this << std::endl;
		if (this->head == NULL) {
			this->prepend(obj);
			return;
		}
		assert(this->tail != NULL);

		node *new_node = new node;
		new_node->next = NULL;
		new_node->data = obj;
		this->tail->next = new_node;
		this->tail = new_node;
	}

	template <typename Type> void LinkedList<Type>::dump() const {
		if (DEBUG) std::cerr << "In LinkedList::dump() for list" << this << std::endl;
		for (node *current = this->head; current != NULL; current = current->next) {
			std::cout << current->data << std::endl;
		}
	}

} // end namespace
#endif

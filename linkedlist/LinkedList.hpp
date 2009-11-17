#ifndef _LINKEDLIST_HPP
#define _LINKEDLIST_HPP

#include <iostream> /* debugging */
#include <assert.h>

#ifndef DEBUG
#define DEBUG 2
#endif

namespace exscape {
	template <typename Type>
	/*
	 * Implements a singly-linked list. Quite useless; I might change it to a doubly-linked at some point,
	 * so that at least BidirectionalIterators can be supported.
	 */
	class LinkedList {
		private:
			struct node {
				struct node *next;
				Type data;
			};

		public:
			LinkedList();
			~LinkedList();
			//void init();
			void clear();
			size_t length() const;
			void prepend(const Type &);
			void append(const Type &);
			void dump() const; // XXX: Debugging only, until iterator support is added

		private:
			struct node *head;
			struct node *tail;
			size_t _length;
	};

	template <typename Type> LinkedList<Type>::LinkedList() : head(NULL), tail(NULL), _length(0) {
		if (DEBUG) std::cerr << "Hello, LinkedList " << this << std::endl;
	}

	template <typename Type> LinkedList<Type>::~LinkedList() {
		this->clear();
		if (DEBUG) std::cerr << "Goodbye, LinkedList " << this << std::endl;
	}

/*
	template <typename Type> void LinkedList<Type>::init() {
		// XXX: Is this function required?
		if (DEBUG) std::cerr << "In LinkedList::init() for list " << this << std::endl;
	}
*/

	/* Add a node before the beginning of the list */
	template <typename Type> void LinkedList<Type>::prepend(const Type &obj) {
		if (DEBUG) std::cerr << "In LinkedList::prepend(" << obj << ") for list " << this << std::endl;
		// Create the new node
		node *new_node = new node;
		new_node->next = this->head;
		new_node->data = obj;

		// Add the node to the list
		this->head = new_node;
		this->_length++;
		
		// If this is the first node, make sure we have a valid tail pointer, too
		if (this->tail == NULL) {
			if (DEBUG) std::cerr << " setting tail to head" << std::endl;
			this->tail = this->head;
		}

		if (DEBUG) this->dump();
	}

	/* Append a node to the list */
	template <typename Type> void LinkedList<Type>::append(const Type &obj) {
		if (DEBUG) std::cerr << "In LinkedList::append(" << obj << ") for list " << this << std::endl;
		
		// If the list is empty, appending == prepending, so...
		if (this->head == NULL) {
			this->prepend(obj);
			return;
		}

		assert(this->tail != NULL);

		// Create the new node
		node *new_node = new node;
		new_node->next = NULL;
		new_node->data = obj;

		// Add the new node to the list
		this->tail->next = new_node;
		this->tail = new_node;
		this->_length++;

		if (DEBUG) this->dump();
	}

	template <typename Type> inline size_t LinkedList<Type>::length() const {
		return this->_length;
	}

	template <typename Type> void LinkedList<Type>::clear() {
		if (DEBUG) std::cerr << "In LinkedList::clear() for list " << this << std::endl;

		if (head == NULL) {
			this->tail = NULL; // just to be sure that both are NULL
			return;
		}

		node *current = this->head;
		while (current != NULL) {
			node *next = current->next;
			if (DEBUG >= 2) std::cerr << " deleting node " << current << " (value: " << current->data << ")" << std::endl;
			delete current;
			current = next;
		}

		this->head = NULL;
		this->tail = NULL;
	}

	template <typename Type> void LinkedList<Type>::dump() const {
//		if (DEBUG) std::cerr << "In LinkedList::dump() for list " << this << std::endl;
		std::cout << "List " << this << " (length " << this->length() << "): ";
		for (node *current = this->head; current != NULL; current = current->next) {
			std::cout << current->data << " ";
		}
		std::cout << std::endl;
	}

} // end namespace
#endif

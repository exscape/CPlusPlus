#ifndef _LINKEDLIST_HPP
#define _LINKEDLIST_HPP

#include <iostream> /* debugging */
#include <stdexcept>
#include <assert.h>

#ifndef DEBUG
#define DEBUG 2
#endif

// TODO:
// * Doubly-linked list, with pop_back() functionality
//   * XXX: Add this before it gets too complicated!
// * Iterators, when everything else is done.
//   * Including const_iterator, and perhaps even reverse_iterator and const_reverse_iterator

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
			size_t size() const;
			bool empty() const;
			void push_front(const Type &);
			void push_back(const Type &);
			void pop_front();
			Type &front();
			const Type &front() const;
			Type &back();
			const Type &back() const;
			void dump(bool verbose) const; // XXX: Debugging only, until iterator support is added

		private:
			struct node *head;
			struct node *tail;
			size_t _size;
	};

	template <typename Type> LinkedList<Type>::LinkedList() : head(NULL), tail(NULL), _size(0) {
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
	template <typename Type> void LinkedList<Type>::push_front(const Type &obj) {
		if (DEBUG) std::cerr << "In LinkedList::push_front(" << obj << ") for list " << this << std::endl;

		// Create the new node
		node *new_node = new node;
		new_node->next = this->head;
		new_node->data = obj;

		// Add the node to the list
		this->head = new_node;
		this->_size++;
		
		// If this is the first node, make sure we have a valid tail pointer, too
		if (this->tail == NULL) {
			if (DEBUG) std::cerr << " setting tail to head" << std::endl;
			this->tail = this->head;
		}

		if (DEBUG) this->dump();
	}

	/* push_back a node to the list */
	template <typename Type> void LinkedList<Type>::push_back(const Type &obj) {
		if (DEBUG) std::cerr << "In LinkedList::push_back(" << obj << ") for list " << this << std::endl;
		
		// If the list is empty, push_back == push_front, so...
		if (this->head == NULL) {
			this->push_front(obj);
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
		this->_size++;

		if (DEBUG) this->dump();
	}

	template <typename Type> inline size_t LinkedList<Type>::size() const {
		return this->_size;
	}

	template <typename Type> inline bool LinkedList<Type>::empty() const {
		return (this->_size == 0);
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
		this->_size = 0;
	}

	/* Removes the frontmost (head) element */
	template <typename Type> void LinkedList<Type>::pop_front() {
		if (DEBUG) std::cerr << "In LinkedList::pop_front() for list " << this << std::endl;
		if (this->head == NULL)
			return; // XXX: throw exception?
		
		node *new_head = this->head->next;
		delete this->head;
		this->head = new_head;
		this->_size--;

		if (DEBUG) this->dump();
	}

	template <typename Type> inline Type &LinkedList<Type>::front() {
		if (DEBUG >= 2) std::cerr << "In Type &LinkedList::front for list " << this << std::endl;
		if (this->head == NULL)
			throw std::runtime_error("Tried to call LinkedList::front() on an empty list");

		return this->head->data;
	}

	template <typename Type> inline const Type &LinkedList<Type>::front() const {
		if (DEBUG >= 2) std::cerr << "In const Type &LinkedList::front for list " << this << std::endl;
		if (this->head == NULL)
			throw std::runtime_error("Tried to call LinkedList::front() on an empty list");

		return this->head->data;
	}

	template <typename Type> inline Type &LinkedList<Type>::back() {
		if (DEBUG >= 2) std::cerr << "In Type &LinkedList::back for list " << this << std::endl;
		if (this->tail == NULL)
			throw std::runtime_error("Tried to call LinkedList::back() on an empty list");

		return this->tail->data;
	}

	template <typename Type> inline const Type &LinkedList<Type>::back() const {
		if (DEBUG >= 2) std::cerr << "In const Type &LinkedList::back for list " << this << std::endl;
		if (this->tail == NULL)
			throw std::runtime_error("Tried to call LinkedList::back() on an empty list");

		return this->tail->data;
	}

	template <typename Type> void LinkedList<Type>::dump(bool verbose = false) const {
//		if (DEBUG) std::cerr << "In LinkedList::dump() for list " << this << std::endl;
		if (verbose == false) {
			std::cout << "List " << this << " (size " << this->size() << "): " << std::endl;
			for (node *current = this->head; current != NULL; current = current->next) {
				std::cout << current->data << " ";
			}
		}
		else {
			std::cout << std::endl << "Verbose dump of list " << this << " (size " << this->size() << "): ";
			for (node *current = this->head; current != NULL; current = current->next) {
				std::cout << " node " << current << ", next " << current->next << ": " << current->data << std::endl;
			}
		}
			std::cout << std::endl;
	}

} // end namespace
#endif

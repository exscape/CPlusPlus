/**
 * \file LinkedList.hpp
 * \brief Implements a doubly-linked list storage container.
 */
#ifndef _LINKEDLIST_HPP
#define _LINKEDLIST_HPP

#include <iostream> /* debugging */
#include <stdexcept>
#include <assert.h>

#ifndef DEBUG
#define DEBUG 2 //!< Sets the debug level. 0 = no debug output, 1 = very verbose, 2 = ridiculously verbose.
#endif

// TODO:
// * Iterators, when everything else is done.
//   * Including const_iterator, and perhaps even reverse_iterator and const_reverse_iterator

/** My namespace. */
namespace exscape {
	template <typename Type>
	/**
	 * A class that implements a doubly-linked list.
	 */
	class LinkedList {
		private:
			/** A basic doubly-linked list structure */
			struct node {
				struct node *prev;
				struct node *next;
				Type data;
			};

		public:
			typedef Type value_type; //!< A typedef to help compatibility with existing classes
			typedef Type & reference; //!< A typedef to help compatibility with existing classes
			typedef const Type & const_reference; //!< A typedef to help compatibility with existing classes
			typedef size_t size_type; //!< A typedef to help compatibility with existing classes

		/* Constructors and destructors */
			LinkedList();
			~LinkedList();
		/* Public methods */
			void clear();
			size_t size() const;
			bool empty() const;
			void push_front(const Type &);
			void push_back(const Type &);
			void pop_front();
			void pop_back();
			Type &front();
			const Type &front() const;
			Type &back();
			const Type &back() const;
			void dump(bool verbose) const; // XXX: Debugging only, until iterator support is added

		/* Overloaded operators */
			bool operator==(const LinkedList<Type> &) const;
			bool operator!=(const LinkedList<Type> &) const;
			LinkedList<Type> &operator=(const LinkedList<Type> &);

		private:
			struct node *head; //!< A pointer to the first element of the linked list
			struct node *tail; //!< A pointer to the last element of the linked list
			size_t _size; //!< The size/length of the linked list, in number of elements
	};

	/**
	 * \brief The default constructor, does nothing but initialize all members to zero, thus creating an empty list 
	 */
	template <typename Type> LinkedList<Type>::LinkedList() : head(NULL), tail(NULL), _size(0) {
		if (DEBUG) std::cerr << "Hello, LinkedList " << this << std::endl;
	}

	/** 
	 * \brief The destructor. Frees all memory associated with the list.
	 */
	template <typename Type> LinkedList<Type>::~LinkedList() {
		this->clear();
		if (DEBUG) std::cerr << "Goodbye, LinkedList " << this << std::endl;
	}

	/** 
	 * \brief Add a node before the beginning of the list.
	 * \param obj The object to add to the list
	 */
	template <typename Type> void LinkedList<Type>::push_front(const Type &obj) {
		if (DEBUG) std::cerr << "In LinkedList::push_front(" << obj << ") for list " << this << std::endl;

		// Create the new node
		node *new_node = new node;
		new_node->prev = NULL;
		new_node->next = this->head;
		new_node->data = obj;

		// Add the node to the list
		node *old_head = this->head;
		this->head = new_node;
		this->_size++;

		// Make sure the old head points back at the new one
		if (old_head != NULL)
			old_head->prev = this->head;
		
		// If this is the first node, make sure we have a valid tail pointer, too
		if (this->tail == NULL) {
			if (DEBUG) std::cerr << " setting tail to head" << std::endl;
			this->tail = this->head;
		}

		if (DEBUG) this->dump();
	}

	/** 
	 * \brief Add a node after the end of the list.
	 * \param obj The object to add to the list
	 */
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
		new_node->prev = this->tail;
		new_node->data = obj;

		// Add the new node to the list
		this->tail->next = new_node;
		this->tail = new_node;
		this->_size++;

		if (DEBUG) this->dump();
	}

	/**
	 * \brief Returns the size/length of the link, in number of elements.
	 * \return The number of elements in the list.
	 */
	template <typename Type> inline size_t LinkedList<Type>::size() const {
		if (DEBUG) { // XXX: Remove this whole block sooner or later
			size_t len = 0;
			for (node *current = this->head; current != NULL; current = current->next)
				len++;
			assert(len == this->_size);
		}

		return this->_size;
	}

	/**
	 * \brief Returns whether this list is empty or not.
	 * \return true if the list is empty (size is 0), otherwise false.
	 */
	template <typename Type> inline bool LinkedList<Type>::empty() const {
		return (this->_size == 0);
	}

	/**
	 * \brief Frees all memory associated with the list and resets it to its "ground state".
	 */
	template <typename Type> void LinkedList<Type>::clear() {
		if (DEBUG) std::cerr << "In LinkedList::clear() for list " << this << std::endl;

		if (this->tail == NULL)
			this->head = NULL; // This can happen in pop_back(), and causes a double free

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

	/** 
	 * \brief Removes the frontmost (head) element.
	 */
	template <typename Type> void LinkedList<Type>::pop_front() {
		if (DEBUG) std::cerr << "In LinkedList::pop_front() for list " << this << std::endl;
		if (this->head == NULL)
			return;
		
		// "Create" the new head
		node *new_head = this->head->next;
		// Delete the old one
		delete this->head;
		// Set the new one
		this->head = new_head;
		this->_size--;

		// Set the prev pointer correctly for the new head
		if (this->head != NULL)
			this->head->prev = NULL;

		// If the list is now empty, reset all member variables to 0
		if (this->head == NULL)
			this->clear();

		if (DEBUG) this->dump();
	}

	/** 
	 * \brief Removes the last (tail) element 
	 */
	template <typename Type> void LinkedList<Type>::pop_back() {
		if (DEBUG) std::cerr << "In LinkedList::pop_back() for list " << this << std::endl;
		if (this->tail == NULL)
			return;

		// "Create" the new tail
		node *new_tail = this->tail->prev;
		// Delete the old one
		delete this->tail;
		// Set the new one
		this->tail = new_tail;
		this->_size--;
		
		if (this->tail != NULL)
			this->tail->next = NULL;
		else if (this->tail == NULL)
			this->clear(); // If the list is now empty, reset all member variables to 0

		if (DEBUG) this->dump();
	}

	/** 
	 * \brief Gets a read-write reference to the first element of the list.
	 * \return A read-write reference to the first element of the list.
	 */
	template <typename Type> inline Type &LinkedList<Type>::front() {
		if (DEBUG >= 2) std::cerr << "In Type &LinkedList::front for list " << this << std::endl;
		if (this->head == NULL)
			throw std::runtime_error("Tried to call LinkedList::front() on an empty list");

		return this->head->data;
	}

	/** 
	 * \brief Gets a const reference to the first element of the list.
	 * \return A const reference to the first element of the list.
	 */
	template <typename Type> inline const Type &LinkedList<Type>::front() const {
		if (DEBUG >= 2) std::cerr << "In const Type &LinkedList::front for list " << this << std::endl;
		if (this->head == NULL)
			throw std::runtime_error("Tried to call LinkedList::front() on an empty list");

		return this->head->data;
	}

	/**
	 * \brief Gets a read-write reference to the last element of the list.
	 * \return A read-write reference to the last element of the list.
	 */
	template <typename Type> inline Type &LinkedList<Type>::back() {
		if (DEBUG >= 2) std::cerr << "In Type &LinkedList::back for list " << this << std::endl;
		if (this->tail == NULL)
			throw std::runtime_error("Tried to call LinkedList::back() on an empty list");

		return this->tail->data;
	}

	/** 
	 * \brief Gets a const reference to the last element of the list.
	 * \return A const reference to the last element of the list.
	 */
	template <typename Type> inline const Type &LinkedList<Type>::back() const {
		if (DEBUG >= 2) std::cerr << "In const Type &LinkedList::back for list " << this << std::endl;
		if (this->tail == NULL)
			throw std::runtime_error("Tried to call LinkedList::back() on an empty list");

		return this->tail->data;
	}

	/** 
	 * \brief Compares two lists.
	 * \param other The list to compare this one with.
	 * \return true if the lists are equal, false otherwise.
	 */
	template <typename Type> bool LinkedList<Type>::operator==(const LinkedList<Type> &other) const {
		if (this == &other)
			return true;
		if (this->size() != other.size())
			return false;

		node *n1 = this->head;
		node *n2 = other.head;
		while (n1 != NULL) {
			if (n1->data != n2->data)
				return false;

			n1 = n1->next;
			n2 = n2->next;
		}

		return true;
	}

	/** 
	 * \brief Compares two lists.
	 * \param other The list to compare this one with.
	 * \return true if the lists differ, false otherwise.
	 */
	template <typename Type> bool LinkedList<Type>::operator!=(const LinkedList<Type> &other) const {
		return !(*this == other);
	}

	/** 
	 * \brief Replaces this lists contents with the contents of list \a other.
	 * \param other The list to copy from.
	 * \return A reference to the new list.
	 */
	template <typename Type> LinkedList<Type> &LinkedList<Type>::operator=(const LinkedList<Type> &other) {
		if (DEBUG) std::cerr << "In operator= for LinkedList " << this << std::endl;
		if (this == &other)
			return *this;

		this->clear();

		for (node *other_n = other.head; other_n != NULL; other_n = other_n->next) {
			this->push_back(other_n->data);
		}

		return *this;
	}

	/** 
	 * \brief A debugging function that dumps the entire content of the list.
	 */
	template <typename Type> void LinkedList<Type>::dump(bool verbose = false) const {
//		if (DEBUG) std::cerr << "In LinkedList::dump() for list " << this << std::endl;
		if (verbose == false) {
			std::cout << "List " << this << " (size " << this->size() << "): ";
			for (node *current = this->head; current != NULL; current = current->next) {
				std::cout << current->data << " ";
			}
		}
		else {
			std::cout << std::endl << "Verbose dump of list " << this << " (size " << this->size() << "):" << std::endl;
			for (node *current = this->head; current != NULL; current = current->next) {
			//	std::cout << " node " << current << ", prev " << current->prev << ", next " << current->next << ": " << current->data << std::endl;
				std::cout << current->prev << " <- " << current << " -> " << current->next << ": " << current->data << std::endl;
			}
		}
			std::cout << std::endl;
	}

} // end namespace
#endif

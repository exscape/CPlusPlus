/**
 * \file LinkedList.hpp
 * \brief Implements a doubly-linked list storage container.
 */
#ifndef _LINKEDLIST_HPP
#define _LINKEDLIST_HPP

#include <iostream> /* debugging */
#include <stdexcept>
#include <iterator>
#include <assert.h>

#ifndef DEBUG
#define DEBUG 2 //!< Sets the debug level. 0 = no debug output, 1 = very verbose, 2 = ridiculously verbose.
#endif

/*
 * The sometimes excessive comments is for Doxygen; one purpose is to shut it up (when not documenting a simple method), another is to get nice documentation for free. The namespace comment feels totally unnecessary, for instance. */

// TODO:
// * Document the iterator classes and functions

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
			typedef ptrdiff_t difference_type; //!< A typedef to help compatibility with existing classes

			class iterator; // Forward delaration to allow for the const_iterator(iterator) constructor

			class const_iterator : public std::iterator<std::bidirectional_iterator_tag, Type, difference_type> {
				public:
					const_iterator(const LinkedList<Type> *in_list, struct node *in_node) : list(in_list), p(in_node) {}
					const_iterator(const const_iterator &other) : list(other.list), p(other.p) {}
					const_iterator(const iterator &other) : list(other.list), p(other.p) {}

					bool operator==(const const_iterator &other) const { return (this->p == other.p); }
					bool operator!=(const const_iterator &other) const { return (this->p != other.p); }

					const Type &operator*() const { return this->p->data; }
					const Type *operator->() const { return &(**this); /* XXX: Hmm? */ }

					const_iterator &operator++() { if (this->p != NULL) this->p = this->p->next; return *this; }
					const_iterator &operator--() { if (this->p != NULL) this->p = this->p->prev; 
												   else if (this->list->tail != NULL) this->p = this->list->tail; 
												   return *this; 
					}
					const_iterator operator++(int) { const_iterator out (*this); return ++out; }
					const_iterator operator--(int) { const_iterator out (*this); return --out; }

				protected:
					const LinkedList<Type> *list;
					node *p;
			};

			class iterator : public std::iterator<std::bidirectional_iterator_tag, Type, difference_type> {
				friend class LinkedList<Type>;
				friend class const_iterator;
				public:
					iterator(const LinkedList<Type> *in_list = NULL, struct node *in_node = NULL) : list(in_list), p(in_node) {}
					iterator(const iterator &other) : list(other.list), p(other.p) {}

					bool operator==(const iterator &other) const { return (this->p == other.p); }
					bool operator!=(const iterator &other) const { return (this->p != other.p); }

					Type &operator*() { return this->p->data; }
					Type *operator->() { return &(**this); /* XXX: Hmm? */ }

					iterator &operator++() { if (this->p != NULL) this->p = this->p->next; return *this; }
					iterator &operator--() { if (this->p != NULL) this->p = this->p->prev; 
												   else if (/* this->p == NULL && */ this->list->tail != NULL) this->p = this->list->tail; 
												   return *this; 
					}
					iterator operator++(int) { iterator out (*this); return ++out; }
					iterator operator--(int) { iterator out (*this); return --out; }

				protected:
					const LinkedList<Type> *list;
					node *p;
			};

			class reverse_iterator : public iterator {
				public:
					reverse_iterator(const LinkedList<Type> *in_list, struct node *in_node) : iterator(in_list, in_node) {}
					reverse_iterator(const reverse_iterator &other) : iterator(other) {}
					reverse_iterator(const iterator &other) : iterator(other) {}

					reverse_iterator &operator++() { if (this->p != NULL) this->p = this->p->prev; return *this; }
					reverse_iterator &operator--() { if (this->p != NULL) this->p = this->p->next; return *this; }
					reverse_iterator operator++(int) { reverse_iterator out (*this); return ++out; }
					reverse_iterator operator--(int) { reverse_iterator out (*this); return --out; }
			};

			class const_reverse_iterator : public const_iterator {
				public:
					const_reverse_iterator(const LinkedList<Type> *in_list, struct node *in_node) : const_iterator(in_list, in_node) {}
					const_reverse_iterator(const const_reverse_iterator &other) : const_iterator(other) {}
					const_reverse_iterator(const const_iterator &other) : const_iterator(other) {}
					const_reverse_iterator(const reverse_iterator &other) : const_iterator(other) {}

					const_reverse_iterator &operator++() { if (this->p != NULL) this->p = this->p->prev; return *this; }
					const_reverse_iterator &operator--() { if (this->p != NULL) this->p = this->p->next; return *this; }
					const_reverse_iterator operator++(int) { const_reverse_iterator out (*this); return ++out; }
					const_reverse_iterator operator--(int) { const_reverse_iterator out (*this); return --out; }
			};

		public:

		/* Constructors and destructors */

		/** \brief Default constructor, creates an empty list. */
		LinkedList() : head(NULL), tail(NULL), _size(0) {}

		/** \brief Copy constructor, sets this to a copy of \a other */
		LinkedList(const LinkedList<Type> &other) : head(NULL), tail(NULL), _size(0) { *this = other; }

		/** \brief A copy constructor that takes two InputIterators and copies everything between them (including begin) */
		template <typename InputIterator>
		LinkedList(InputIterator start, InputIterator end) : head(NULL), tail(NULL), _size(0) {
			this->assign(start, end);
		}

		/** \brief Destructor, frees all memory associated with this list. */
		~LinkedList() { this->clear(); }

		/* Public methods */
			void clear();
			size_t size() const;

			/** \brief Returns whether this list is empty or not. */
			bool empty() const { return (this->_size == 0); }

			/* Methods that add items to the list */
			void push_front(const Type &);
			void push_back(const Type &);

			/** \brief Copies everything between InputIterators \a start and \a end, \a start included */
			template <typename InputIterator> void assign (InputIterator start, InputIterator end) {
				this->clear();
				for (; start != end; ++start)
					this->push_back(*start);
			}

			/* Methods that remove items from the list */
			void pop_front();
			void pop_back();
			iterator erase(iterator pos);
			iterator erase(iterator start, iterator end);

			/* Access methods */
			Type &front();
			const Type &front() const;
			Type &back();
			const Type &back() const;

			/* Misc */
			void dump(bool verbose) const; // Debugging only

			/** \brief Creates a regular R/W iterator pointing at the list start */
			iterator begin() { return iterator(this, this->head); }

			/** \brief Creates a regular R/W iterator pointing one node after the list end */
			iterator end() { return iterator(this, NULL); }

			/** \brief Creates a const_iterator pointing at the list start */
			const_iterator begin() const { return const_iterator(this, this->head); }

			/** \brief Creates a const_iterator pointing one node after the list end */
			const_iterator end() const { return const_iterator(this, NULL); }

			/** \brief Creates a R/W reverse_iterator pointing at the last node */
			reverse_iterator rbegin() { return reverse_iterator(this, this->tail); }

			/** \brief Creates a R/W reverse_iterator pointing one node before the list start */
			reverse_iterator rend() { return reverse_iterator(this, NULL); }

			/** \brief Creates a const_reverse_iterator pointing at the last node */
			const_reverse_iterator rbegin() const { return const_reverse_iterator(this, this->tail); }

			/** \brief Creates a const_reverse_iterator pointing one node before the list start */
			const_reverse_iterator rend() const { return const_reverse_iterator(this, NULL); }

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
		if (DEBUG) { // XXX: Remove this whole block sooner or later, when all erase() and insert() operations work
			size_t len = 0;
			for (node *current = this->head; current != NULL; current = current->next)
				len++;
			assert(len == this->_size);
		}

		return this->_size;
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

	/** \brief Deletes the element pointed to by \a position.
	 *  \return An iterator pointing to the new location of the element that followed the one erased, or end() if the tail was deleted. // XXX
	 */
	template <typename Type> typename LinkedList<Type>::iterator LinkedList<Type>::erase(iterator position) {
		if (DEBUG >= 2) std::cerr << "Before erase(iterator): " << std::endl;
		if (DEBUG >= 2) this->dump(true);

		node *to_delete = position.p;
		node *next_node = NULL;
		if (to_delete == NULL)
			return end(); // XXX, what should we return here?

		if (to_delete->prev != NULL) { // If this isn't the head node, fix its next pointer
			to_delete->prev->next = to_delete->next; // The node before the one we delete should point to the one after
		}
		else
			this->head = this->head->next; // The head node was deleted; replace it (possibly with NULL)

		if (to_delete->next != NULL) { // If  this isn't the tail node, fix its prev painter
			to_delete->next->prev = to_delete->prev; // The node after the one we delete should point to the one before
			next_node = to_delete->next;
		}
		else {
			this->tail = this->tail->prev; // The tail node was deleted; replace it (possibly with NULL)
			assert (next_node == NULL); // XXX: If this fails, set it here, too
		}
		
		delete to_delete;

		if (this->_size != 0)
			this->_size--;

		if (DEBUG >= 2) std::cerr << "After erase(iterator): " << std::endl;
		if (DEBUG >= 2) this->dump(true);

		// XXX: Is this correct? iterator(this, next_node) == end() if next_node == NULL, so it should work
		return iterator(this, next_node);
	}

	/** \brief Deletes all the elements between iterators \a start and \a end.
	 *  \return An iterator pointing to the new location of the element that followd the last elemen erased, or end() if the tail was deleted. // XXX
	 */
	template <typename Type> typename LinkedList<Type>::iterator LinkedList<Type>::erase(iterator start, iterator end) {
		while (start != end)
			start = this->erase(start);
		return end;
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
		if (verbose == false) {
			std::cerr << "List " << this << " (size " << this->size() << "): ";
			for (const_iterator ci = this->begin(); ci != this->end(); ++ci) {
				std::cerr << *ci << " ";
			}
		}
		else {
			std::cerr << std::endl << "Verbose dump of list " << this << " (size " << this->size() << "):" << std::endl;
			for (node *current = this->head; current != NULL; current = current->next) {
				std::cerr << current->prev << " <- " << current << " -> " << current->next << ": " << current->data << std::endl;
			}
		}
			std::cerr << std::endl;
	}

} // end namespace
#endif

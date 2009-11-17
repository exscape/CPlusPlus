#ifndef _LINKEDLIST_HPP
#define _LINKEDLIST_HPP

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

		private:
			struct node *head;
			struct node *tail;
	};

	template <typename Type> LinkedList<Type>::LinkedList() : head(NULL), tail(NULL) {
		if (DEBUG) std::cerr << "Hello, LinkedList " << this << std::endl;
	}

	template <typename Type> LinkedList<Type>::~LinkedList() {
		if (DEBUG) std::cerr << "Goodbye, LinkedList" << this << std::endl;
		this->clear();
	}

	template <typename Type> void LinkedList<Type>::init() {
		// XXX: Is this function required?
		if (DEBUG) std::cerr << "In LinkedList::init() for list" << this << std::endl;
	}

	template <typename Type> void LinkedList<Type>::clear() {
		if (DEBUG) std::cerr << "In LinkedList::clear() for list" << this << std::endl;
		/* Free memory, reset all pointers */ 
	}

} // end namespace
#endif

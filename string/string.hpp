#ifndef _STRING_HPP
#define _STRING_HPP

#include <iostream> /* stream support for operators << and >>, plus debugging */
#include <iterator>

#ifndef DEBUG
#define DEBUG 0
#endif

namespace exscape {
	class string {
		typedef ptrdiff_t difference_type;
		public:
			friend class iterator_base;
			friend class iterator;
			friend class reverse_iterator;
		protected:
			/* 
			 * A class that is the base class for both iterator and reverse_iterator, implementing common methods.
			 * Commented out methods are implemented in the subclasses.
			 */
			class iterator_base : public std::iterator<std::random_access_iterator_tag, char, difference_type> {
				public:
					friend class string;
					//friend iterator operator+(const int, iterator);
					//friend iterator operator-(const int, iterator);
					/* Constructors and operator= */
					iterator_base(void);
					iterator_base(const iterator_base &rhs);
					//iterator_base& operator=(const iterator_base &rhs);
					iterator_base(char *in_ptr, bool);

					/* Destructor */
					~iterator_base();

					/* Tests if these two iterators point to the same position */
					bool operator==(const iterator_base &rhs) const;

					/* Tests if these two iterator_bases DON'T point to the same position */
					bool operator!=(const iterator_base &rhs) const;
					bool operator<(const iterator_base &rhs) const;
					bool operator>(const iterator_base &rhs) const;

					/* A little of both... */
					bool operator<=(const iterator_base &rhs) const;
					bool operator>=(const iterator_base &rhs) const;

					/* Dereference operators */
					char &operator*(void);
					char *operator->(void);
					char &operator[](const int offset);

					///* Move the iterator forward one step */
					//iterator &operator++();
					//iterator operator++(int);

					///* Move the iterator back one step */
					//iterator &operator--();
					//iterator operator--(int);

					///* Arithmetic operators */
					//iterator &operator+=(const difference_type offset);
					//iterator &operator-=(const difference_type offset);
					//iterator operator+(const difference_type offset);
					//iterator operator-(const difference_type offset);
					//difference_type operator-(iterator &rhs);

				protected:
					char *base; // The base of the string
					char *p; // Points to the current character
					size_t length; // The length, i.e. we can't go past base+length
			}; // end string::iterator_base

		public:
			/* 
			 * A regular random access iterator
			 */
			class iterator : public iterator_base {
				public:
					friend class string;
					friend iterator operator+(const int, iterator);
					friend iterator operator-(const int, iterator);

					/* Constructors and operator= */
					iterator(void);
					iterator(const iterator &rhs);
					iterator& operator=(const iterator &rhs);
					iterator(char *in_ptr);

					/* Destructor */
					~iterator();

					/* Move the iterator forward one step */
					iterator &operator++();
					iterator operator++(int);

					/* Move the iterator back one step */
					iterator &operator--();
					iterator operator--(int);

					/* Arithmetic operators */
					iterator &operator+=(const difference_type offset);
					iterator &operator-=(const difference_type offset);
					iterator operator+(const difference_type offset);
					iterator operator-(const difference_type offset);
					difference_type operator-(iterator &rhs);
			}; // end string::iterator

			/* 
			 * A regular reverse random access iterator
			 */
			class reverse_iterator : public iterator_base {
				public:
					friend class string;
					friend reverse_iterator operator+(const int, reverse_iterator);
					friend reverse_iterator operator-(const int, reverse_iterator);

					/* Constructors and operator= */
					reverse_iterator(void);
					reverse_iterator(const reverse_iterator &rhs);
					reverse_iterator& operator=(const reverse_iterator &rhs);
					reverse_iterator(char *in_ptr);

					/* Destructor */
					~reverse_iterator();

					reverse_iterator &operator++();
					reverse_iterator operator++(int);

					reverse_iterator &operator--();
					reverse_iterator operator--(int);

					/* Arithmetic operators */
					reverse_iterator &operator+=(const difference_type offset);
					reverse_iterator &operator-=(const difference_type offset);
					reverse_iterator operator+(const difference_type offset);
					reverse_iterator operator-(const difference_type offset);
					difference_type operator-(reverse_iterator &rhs);
			}; // end string::reverse_iterator

		protected:
		/* Protected methods */
			void init();
			void alloc(size_t) throw();
			void dealloc(void);
			// void compress(void) throw();
			void assign(const char *);
			void append(const char *);

		public:
		/* Public methods */
			string();
			string(const string &);
			string(const char *);
			~string();
			const char *c_str(void) const;
			size_t length(void) const;
			size_t capacity(void) const;
			bool empty(void) const;
			bool equals(const char *str) const;
			size_t find (const char *) const;
			size_t find(const string &) const;
			void clear(void);
			void resize(size_t target_size);
			string reverse(void) const;
			string substr(ssize_t, ssize_t) const throw();
			string & operator+=(const char *);
			string & operator+=(const string &);
			string operator+(const char *) const;
			string operator+(const string &) const;
			friend string operator+(const char *, const string &);
			string & operator=(const char *);
			string & operator=(const string &);
			char &operator[](size_t) const;
			bool operator==(const char *) const;
			bool operator!=(const char *) const;
			friend bool operator==(const char *, string &);
			friend bool operator!=(const char *, string &);
			bool operator==(const string &) const;
			bool operator!=(const string &) const;
			friend std::ostream &operator<<(std::ostream &, string);
			friend std::istream &operator>>(std::istream &, string &);
			void dump(void) const;
			string::iterator begin(void) const;
			string::iterator end(void) const;
			string::reverse_iterator rbegin(void) const;
			string::reverse_iterator rend(void) const;

		protected:
		/* Protected member variables */
			char *buf;
			size_t _length; // string length
			size_t _size; // bytes allocated
	}; // end string

#endif
}

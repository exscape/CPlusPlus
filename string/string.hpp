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
			friend class iterator;
			friend class reverse_iterator;

			class iterator : public std::iterator<std::random_access_iterator_tag, char, difference_type> {
				public:
					friend class string;
					/* Constructors and operator= */
					iterator(char *in_ptr = NULL) : base(in_ptr), p(in_ptr) {}
					iterator(const iterator &rhs) { *this = rhs; }

					/* Destructor */
					~iterator() {}

					/* Tests if these two iterators point to the same position */
					bool operator==(const iterator &rhs) const { return (p == rhs.p); }

					/* Tests if these two iterators DON'T point to the same position */
					bool operator!=(const iterator &rhs) const { return p != rhs.p; }
					bool operator<(const iterator &rhs)  const { return p < rhs.p; }
					bool operator>(const iterator &rhs)  const { return p > rhs.p; }

					/* A little of both... */
					bool operator<=(const iterator &rhs) const { return p <= rhs.p; }
					bool operator>=(const iterator &rhs) const { return p >= rhs.p; }

					/* Dereference operators */
					char &operator*(void)  { return *p; }
					char *operator->(void) { return p; }
					char &operator[](const int offset) { return *(p + offset); }

					iterator& operator=(const iterator &rhs); // XXX: NOT INLINED!

					/* Single-step movement operators */
					iterator &operator++()   { p++; return *this; }
					iterator &operator--()   { p--; return *this; }
					iterator operator++(int) { ++(*this); return iterator(this->p - 1); }
					iterator operator--(int) { --(*this); return iterator(this->p + 1); }

					/* Arithmetic operators */
					iterator &operator+=(const difference_type offset) { p += offset; return *this; }
					iterator &operator-=(const difference_type offset) { p -= offset; return *this; }
					iterator operator+(const difference_type offset)   { iterator out (*this); return (out += offset); }
					iterator operator-(const difference_type offset)   { iterator out (*this); return (out -= offset); }
					friend iterator operator+(const int, iterator);    // XXX: Not inlined
					friend iterator operator-(const int, iterator);    // XXX: Not inlined
					difference_type operator-(iterator &rhs)           { return p - rhs.p; }

				protected:
					char *base; // The base of the string
					char *p; // Points to the current character
			}; // end string::iterator

			/* 
			 * A regular reverse random access iterator
			 */
			class reverse_iterator : public iterator {
				public:
					friend class string;
					friend reverse_iterator operator+(const int, reverse_iterator);
					friend reverse_iterator operator-(const int, reverse_iterator);

					/* Constructors */
					reverse_iterator(void);
					reverse_iterator(const reverse_iterator &rhs);
					reverse_iterator(char *in_ptr);

					/* Destructor */
					~reverse_iterator();

					/* Single-step movement operators */
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
			string(const string &);
			string(const char * = NULL);
			~string();
			const char *c_str(void) const;
			size_t length(void) const;
			size_t capacity(void) const;
			bool empty(void) const;
			bool equals(const char *str) const;
			bool is_palindrome_strict(void) const;
			bool is_palindrome(void) const;
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

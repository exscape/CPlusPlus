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

					/* Single-step movement operators */
					iterator &operator++()   { p++; return *this; }
					iterator &operator--()   { p--; return *this; }
					iterator operator++(int) { iterator out(*this); ++(*this); return out; }
					iterator operator--(int) { iterator out(*this); --(*this); return out; }

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

					/* Constructors */
					reverse_iterator(void) : iterator() {}
					reverse_iterator(const reverse_iterator &rhs) { *this = rhs; }
					reverse_iterator(char *in_ptr) : iterator(in_ptr) {}

					/* Destructor */
					~reverse_iterator() {}

					/* Single-step movement operators */
					reverse_iterator &operator++()   { p--; return *this; }
					reverse_iterator &operator--()   { p++; return *this; }
					reverse_iterator operator++(int) { reverse_iterator out; ++(*this); return out; }
					reverse_iterator operator--(int) { reverse_iterator out; --(*this); return out; }

					/* Arithmetic operators */
					reverse_iterator &operator+=(const difference_type offset) { p -= offset; return *this; }
					reverse_iterator &operator-=(const difference_type offset) { p += offset; return *this; }
					reverse_iterator operator+(const difference_type offset)   { reverse_iterator out(*this); return (out += offset); }
					reverse_iterator operator-(const difference_type offset)   { reverse_iterator out(*this); return (out -= offset); }
					friend reverse_iterator operator+(const int, reverse_iterator); // XXX: Not inlined
					friend reverse_iterator operator-(const int, reverse_iterator); // XXX: Not inlined
					difference_type operator-(reverse_iterator &rhs)           { return p - rhs.p; }

			}; // end string::reverse_iterator

			class const_iterator : public std::iterator<std::random_access_iterator_tag, char, difference_type> {
				public:
					friend class string;
					/* Constructors and operator= */
					const_iterator(char *in_ptr = NULL) : base(in_ptr), p(in_ptr) {}
					const_iterator(const const_iterator &rhs) { *this = rhs; }

					/* Destructor */
					~const_iterator() {}

					/* Tests if these two const_iterators point to the same position */
					bool operator==(const const_iterator &rhs) const { return (p == rhs.p); }

					/* Tests if these two const_iterators DON'T point to the same position */
					bool operator!=(const const_iterator &rhs) const { return p != rhs.p; }
					bool operator<(const const_iterator &rhs)  const { return p < rhs.p; }
					bool operator>(const const_iterator &rhs)  const { return p > rhs.p; }

					/* A little of both... */
					bool operator<=(const const_iterator &rhs) const { return p <= rhs.p; }
					bool operator>=(const const_iterator &rhs) const { return p >= rhs.p; }

					/* Dereference operators */
					const char &operator*(void) const { return *p; }
					const char *operator->(void) const { return p; }
					const char &operator[](const int offset) const { return *(p + offset); }

					/* Single-step movement operators */
					const_iterator &operator++()   { p++; return *this; }
					const_iterator &operator--()   { p--; return *this; }
					const_iterator operator++(int) { const_iterator out(*this); ++(*this); return out; }
					const_iterator operator--(int) { const_iterator out(*this); --(*this); return out; }

					/* Arithmetic operators */
					const_iterator &operator+=(const difference_type offset) { p += offset; return *this; }
					const_iterator &operator-=(const difference_type offset) { p -= offset; return *this; }
					const_iterator operator+(const difference_type offset)   { const_iterator out (*this); return (out += offset); }
					const_iterator operator-(const difference_type offset)   { const_iterator out (*this); return (out -= offset); }
					friend const_iterator operator+(const int, const_iterator);    // XXX: Not inlined
					friend const_iterator operator-(const int, const_iterator);    // XXX: Not inlined
					difference_type operator-(const_iterator &rhs)           { return p - rhs.p; }

				protected:
					char *base; // The base of the string
					char *p; // Points to the current character
			}; // end string::const_iterator

			/* 
			 * A regular reverse random access iterator
			 */
			class const_reverse_iterator : public const_iterator {
				public:
					friend class string;

					/* Constructors */
					const_reverse_iterator(void) : const_iterator() {}
					const_reverse_iterator(const const_reverse_iterator &rhs) { *this = rhs; }
					const_reverse_iterator(char *in_ptr) : const_iterator(in_ptr) {}

					/* Destructor */
					~const_reverse_iterator() {}

					/* Single-step movement operators */
					const_reverse_iterator &operator++()   { p--; return *this; }
					const_reverse_iterator &operator--()   { p++; return *this; }
					const_reverse_iterator operator++(int) { const_reverse_iterator out; ++(*this); return out; }
					const_reverse_iterator operator--(int) { const_reverse_iterator out; --(*this); return out; }

					/* Arithmetic operators */
					const_reverse_iterator &operator+=(const difference_type offset) { p -= offset; return *this; }
					const_reverse_iterator &operator-=(const difference_type offset) { p += offset; return *this; }
					const_reverse_iterator operator+(const difference_type offset)   { const_reverse_iterator out(*this); return (out += offset); }
					const_reverse_iterator operator-(const difference_type offset)   { const_reverse_iterator out(*this); return (out -= offset); }
					friend const_reverse_iterator operator+(const int, const_reverse_iterator); // XXX: Not inlined
					friend const_reverse_iterator operator-(const int, const_reverse_iterator); // XXX: Not inlined
					difference_type operator-(const_reverse_iterator &rhs)           { return p - rhs.p; }

			}; // end string::const_reverse_iterator


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
			string::iterator begin(void);
			string::iterator end(void);
			string::reverse_iterator rbegin(void);
			string::reverse_iterator rend(void);
			string::const_iterator begin(void) const;
			string::const_iterator end(void) const;
			string::const_reverse_iterator rbegin(void) const;
			string::const_reverse_iterator rend(void) const;

		protected:
		/* Protected member variables */
			char *buf;
			size_t _length; // string length
			size_t _size; // bytes allocated
	}; // end string

#endif
}

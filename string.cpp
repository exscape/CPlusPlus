#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <fstream>
#include <algorithm>

#define DEBUG 1

// TODO: 
// * Fix operator>>? Only works for cin >>, and doesn't act like it's supposed to...
// * Iterators:
//  * http://www.oreillynet.com/pub/a/network/2005/11/21/what-is-iterator-in-c-plus-plus-part2.html?page=3
//
//  * Don't forget reverse iterators later.

namespace exscape {
	using std::cerr;
	class string {
		friend class iterator;
		protected:
		/* Protected member variables */
			char *buf;
			size_t _length; // string length
			size_t _size; // bytes allocated

		protected:
		/* Protected methods */
			void init();
			void alloc(size_t) throw();
			void dealloc(void);
//			void compress(void) throw();
			void assign(const char *);
			void append(const char *);

		public:
			class iterator : public std::iterator<std::random_access_iterator_tag, char> {
				public:
				friend iterator operator+(const int, iterator);
				friend iterator operator-(const int, iterator);
					/* Default constructor */
					iterator(void) {
						std::cerr << "In DEFAULT constructor for iterator... what do we do here?" << std::endl;
						this->base = NULL;
						this->p = NULL;
						this->length = 0;
						exit(1); // XXX
					}

					/* Destructor */
					~iterator() { 
						if (DEBUG) std::cerr << "Goodbye, iterator " << this << ", pointing at " << &p << std::endl; 
					}

					/* Copy constructor */
					iterator(const iterator &rhs) {
						std::cerr << "In iterator(iterator &)" << std::endl;
						*this = rhs;
					}

					iterator& operator=(const iterator &rhs) {
						if (DEBUG) std::cerr << "In iterator::operator=" << std::endl;
						if (this != &rhs) {
							this->p = rhs.p;
							this->length = rhs.length;
							this->base = rhs.base;
						}
						if (DEBUG) std::cerr << "Hello, iterator (in operator=) " << this << ", pointing at " << &p << std::endl;

						return *this;
					}

					/* Most-used constructor; used by string to pass a pointer to the string base */
					iterator(char *in_ptr, size_t in_len = 0) { // XXX: 0 is used for end(); good idea?
						std::cerr << "In iterator(char *, size_t)" << std::endl;
						this->base = in_ptr;
						this->p = in_ptr;
						this->length = in_len;
						if (DEBUG) std::cerr << "Hello, iterator (in iterator (char *, size_t)) " << this << ", pointing at " << &p << std::endl;
					}

					/* Tests if these two iterators point to the same posision */
					bool operator==(const iterator &rhs) const {
						return (p == rhs.p);
					}

					/* Tests if these two iterators DON'T point to the same posision */
					bool operator!=(const iterator &rhs) const {
						return (p != rhs.p);
					}

					bool operator<(const iterator &rhs) const {
						return (p < rhs.p); // XXX: Backwards or not?
					}

					bool operator>(const iterator &rhs) const {
						return (p > rhs.p); // XXX: Backwards or not?
					}

					bool operator<=(const iterator &rhs) const {
						return (p < rhs.p || p == rhs.p); // XXX: Backwards or not?
					}

					bool operator>=(const iterator &rhs) const {
						return (p > rhs.p || p == rhs.p); // XXX: Backwards or not?
					}

					/* Dereference operator, return a reference to the currently pointed-to character */
					char &operator*(void) {
						if (this->p >= this->base + this->length || // Pointer is beyond the string boundaries
								this->p < this->base) // Pointer points to something before the string begins
							throw std::out_of_range("Tried to dereference iterator that is out of string bounds!");

						return *p;
					}

					char *operator->(void) {
						if (this->p >= this->base + this->length || // Pointer is beyond the string boundaries
								this->p < this->base) // Pointer points to something before the string begins
							throw std::out_of_range("Tried to dereference iterator that is out of string bounds!");

						return p;
					}

					/* Move the iterator forward one step */
					iterator &operator++() {
						p++;
						return *this;
					}

					/* Move the iterator forward one step */
					iterator operator++(int) {
						++(*this);
						return iterator(this->p - 1, this->length);
					}

					/* Move the iterator back one step */
					iterator &operator--() {
						p--;
						return *this;
					}

					/* Move the iterator back one step */
					iterator operator--(int) {
						p--;
						return iterator(this->p + 1, this->length);
					}

					iterator &operator+=(const int offset) {
						p += offset;
						return *this;
					}

					iterator &operator-=(const int offset) {
						p -= offset;
						return *this;
					}

					iterator operator+(const int offset) {
						iterator out (*this);
						out += offset;
						return out;
					}

					iterator operator-(const int offset) { 
						iterator out = (*this);
						out -= offset;
						return out;
					}

					long operator-(iterator &rhs) {
						return p - rhs.p;
					}

					char &operator[](const int offset) {
						if (this->p + offset >= this->base + this->length || // Pointer is beyond the string boundaries
								this->p + offset < this->base) // Pointer points to something before the string begins
							throw std::out_of_range("Tried to dereference iterator that is out of string bounds!");

						return *(p + offset);
					}

				private:
					char *p; // Points to the current character
					char *base; // The base of the string
					size_t length; // The length, i.e. we can't go past base+length
			}; // end string::iterator

		friend iterator operator+(const int n, iterator out) {
			out += n;
			return out;
		}

		friend iterator operator-(const int n, iterator out) {
			out -= n;
			return out;
		}

		/* Public methods */
			string() { init(); }
			string(const string &);
			string(const char *);
			~string();
			const char *c_str(void) const;
			size_t length(void) const;
			bool empty(void) const;
			bool equals(const char *str) const;
			size_t find (const char *) const;
			size_t find(const string &) const;
			void clear(void);
			string reverse(void) const;
			string substr(ssize_t, ssize_t) const throw();
			string & operator+=(const char *);
			string & operator+=(const string &);
			string operator+(const char *);
			string operator+(const string &);
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
			void dump(void) const; // XXX: Debugging
			string::iterator begin(void) const;
			string::iterator end(void) const;

	}; // end string

	string::iterator string::begin(void) const {
		return iterator(this->buf, this->_length);
	}

	string::iterator string::end(void) const {
		return iterator(this->buf + this->_length, 0); // buf[_length] == '\0', so one past the end
	}

	/* Initializes a string to an empty state */
	void string::init(void) {
		if (DEBUG) std::cerr << "In init() for string " << this << std::endl;
		this->buf = NULL;
		this->_length = 0;
		this->_size = 0;
	}

	/* Copy constructor from const char * */
	string::string(const char *in) {
		if (DEBUG) std::cerr << "In const char* copy constructor for string " << this << std::endl;
		this->init();
		this->append(in);
	}

	/* Copy constructor from another string instance */
	string::string(const string &in) {
		this->init();
		this->append(in.c_str());
	} 

	/* Destructor */
	string::~string() {
		if (DEBUG) std::cerr << "In destructor for string " << this << std::endl;
		this->dealloc();
	}

	/* Allocates/reallocates memory for a string */
	void string::alloc(size_t target_size) throw() {
		if (DEBUG) std::cerr << " In alloc() for string " << this << ", current size=" << this->_size << ", target_size=" << target_size << std::endl;

		if (this->_size >= target_size) {
			if (DEBUG) std::cerr << "  _size >= target_size, not reallocating string " << this << std::endl;
			return;
		}

		if (this->buf == NULL) { // Allocate a new string
			this->buf = (char *)calloc(1, target_size);
			if (this->buf != NULL) { // Allocation succeeded
				this->_size = target_size;
				this->_length = 0;
			}
			else { // Allocation failed
				this->_size = 0;
				this->_length = 0;
				throw std::runtime_error("calloc() returned NULL");
			}
		}
		else { // Reallocate to a larger memory area
			char *new_buf = (char *)realloc(this->buf, target_size);
			if (new_buf != NULL) { // Allocation succeeded
				// Set all newly allocated memory to 0, while leaving the old string be
				memset(new_buf + this->_size, 0, target_size - this->_size);
				this->buf = new_buf;
				this->_size = target_size;
			}
			else { // Allocation failed
				free(this->buf);
				this->buf = NULL;
				this->_size = 0;
				this->_length = 0;
				throw std::runtime_error("realloc() returned NULL");
			}
		}
	}

	/* "Compress" the string, i.e. realloc to use as little memory as required, length+1 bytes */
/*
	void string::compress(void) throw() {
		size_t target_size = this->_length+1;
		if (DEBUG) std::cerr << "In compress() for string " << this << ", current size=" << this->_size << ", target=" << this->_length+1 << std::endl;

		if (this->buf == NULL || this->_length == 0 || this->_size == this->_length + 1) {
			if (DEBUG) std::cerr << " no need to compress (buf==NULL, _length=0 or string already compressed), returning" << std::endl;
			return;
		}

		char *new_buf = (char *)realloc(this->buf, target_size);
		if (new_buf != NULL) {
			this->buf = new_buf;
			this->_size = target_size;
		}
		else {
			free(this->buf);
			this->buf = NULL;
			this->_size = 0;
			this->_length = 0;
			throw std::runtime_error("realloc() returned NULL in compress()");
		}
	}
*/

	/* Deallocates the memory associated with a string */
	void string::dealloc(void) {
		if (DEBUG) std::cerr << " In dealloc() for string " << this << std::endl;
		if (this->buf != NULL) {
			if (DEBUG) std::cerr << "  Calling free(" << &(this->buf) << ")" << std::endl;
			free(this->buf);
		}
		else
			if (DEBUG) std::cerr <<  "  Nothing to free, string was NULL" << std::endl;
		this->_length = 0;
		this->_size = 0;
	}

	/* Returns the string length, equal to strlen(this->buf) */
	size_t string::length(void) const {
		return this->_length;
	}

	/* Returns whether the string is empty or not */
	bool string::empty(void) const {
		return (this->_length == 0);
	}

	/* Returns a const char * pointer to the data store, just like std::string */
	const char *string::c_str() const {
		return this->buf;
	}

	/* Set this string to str, by starting over and "appending" to it */
	void string::assign(const char *str) {
		this->clear();
		this->append(str);
	}

	/* Internal function that appends a given C-style string to this exscape::string */
	void string::append(const char *str) {
		if (DEBUG) std::cerr << "In string::append() for destination string " << this << std::endl;
		if (str == NULL || strlen(str) < 0)
			return;

		size_t new_length = this->_length + strlen(str);
		this->alloc(new_length + 1);
		strcat(this->buf, str);
		this->_length = new_length;
	}

	/* Compares two strings; if their lengths don't match, compare byte for byte */
	bool string::equals(const char *str) const {
		if (DEBUG) std::cerr << " in equals() for " << this << " and const char *" << &str << std::endl;
		if (this->buf == NULL && str == NULL)
			return true;
		else if (this->buf == NULL || str == NULL)
			return false;
		if (this->_length != strlen(str))
			return false;

		return (strcmp(this->buf, str) == 0);
	}

	size_t string::find (const char *str) const {
		// The return value of -1 with an unsigned type in intentional; the same
		// method is used by std::string.
		if (str == NULL)
			return -1;

		size_t len = strlen(str);
		if (len == 0 || len > this->_length)
			return -1;

		char *p = strstr(this->buf, str);
		if (p == NULL)
			return -1;
		else
			return (p - this->buf);
	}

	size_t string::find(const string &str) const {
		return this->find(str.c_str());
	}

	void string::clear(void) {
		if (DEBUG) std::cerr << "In clear for string " << this << std::endl;
		this->dealloc();
		this->init();
	}

	/* Concatenate this string with a C-style string */
	string & string::operator+=(const char *str) {
		if (DEBUG) std::cerr << "In operator+=(const char *) for string " << this << std::endl;
		this->append(str);
		return *this;
	}

	/* Concatenate this string with another string instance */
	string & string::operator+=(const string &str) {
		if (DEBUG) std::cerr << "In operator+=(const string &) for string " << this << std::endl;
		this->append(str.c_str());
		return *this;
	}

	/* Return a new string consisting of this + a C-style string */
	string string::operator+(const char *str) {
		if (DEBUG) std::cerr << "In operator+(const char *) for string " << this << std::endl;
		string result = *this;
		result += str;
		return result;
	}

	/* Return a new string consisting of this + another string instance */
	string string::operator+(const string &str) {
		if (DEBUG) std::cerr << "In operator+(const string &) for string " << this << std::endl;
		string result = *this;
		result += str.c_str();
		return result;
	}

	/* Friend function, to handle cases such as "abc" + string */
	string operator+(const char *lhs, const string &rhs) {
		if (DEBUG) std::cerr << "In operator+(const char *, const string &)" << std::endl;
		string result (lhs);
		result += rhs;
		return result;
	}
	
	/* Set this string to other string instance str */
	string & string::operator=(const string &str) {
		if (this == &str)
			return *this;

		this->assign(str.c_str());
		return *this;
	}

	/* Set this string to C-string str */
	string & string::operator=(const char *str) {
		this->assign(str);
		return *this;
	}

	/* Return a single character, just like you'd expect from string indexing */
	char &string::operator[](size_t index) const {
		if (index >= this->_length)
			throw std::out_of_range("Index is out of bounds");

		return this->buf[index];
	}

	bool string::operator==(const string &rhs) const {
		if (DEBUG) std::cerr << "In operator== for strings " << this << " (" << this->c_str()  << ") and " << &rhs << " (" << rhs.c_str() << ")"<< std::endl;

		return this->equals(rhs.c_str());
	}

	bool string::operator==(const char *str) const { 
		if (DEBUG) std::cerr << "In operator== (const char *)" << std::endl;
		return this->equals(str);
	}

	bool operator==(const char *lhs, string &rhs) {
		return (rhs == lhs);
	}
	
	bool operator!=(const char *lhs, string &rhs) {
		return !(rhs == lhs);
	}

	/* The inverse of operator== */
	bool string::operator!=(const string &rhs) const {
		if (DEBUG) std::cerr << "In operator!= for strings " << this << " and " << &rhs << std::endl;
		return !(*this == rhs);
	}

	bool string::operator!=(const char *str) const { 
		if (DEBUG) std::cerr << "In operator!= (const char *)" << std::endl;
		return !(this->equals(str));
	}

	/* Allow the class to be used with output streams, i.e. cout << str */
	std::ostream &operator<<(std::ostream &stream, string str) {
		stream << str.c_str();
		return stream;
	}
	
	/* Allows the class to be used with input streams, i.e. cin >> str */
	std::istream &operator>>(std::istream &stream, string &str) {
		// XXX: This does NOT work with *fstream. cin >> appears to be fine, but that's about it...
		// Very ugly code, too.
		#define TEMP_SIZE 128
		char tmp[TEMP_SIZE] = {0};
		char *p;
		char c;

		str.clear();

		bool stop = false;
		while (stop == false) {
			memset(tmp, 0, TEMP_SIZE);
			p = tmp;
			int i = 0;
			while (i < TEMP_SIZE - 1) {
				stream.get(c);
				if (c != '\n') {
					*p++ = c;
					i++;
				}
				else {
					stop = true;
					break;
				}
				if (stream.eof() || stream.fail()) {
					stop = true;
					break;
				}
			}

			str.append(tmp);
		}

//		if (DEBUG) std::cerr << "STRING DUMP after operator>> is finished: " << std::endl;
//		str.dump();

		return stream;
	}

	/* Returns a reversed copy of this string */
	string string::reverse(void) const {
		string rev;
		rev.alloc(this->_length + 1);

		for (size_t i=0; i<this->_length; i++) {
			rev.buf[this->_length-i-1] = this->buf[i];
		}

		rev._length = this->_length;

		return rev;
	}

	/* Returns substring of this string instance.
	 * start: The index where to start, where 0 is the first character. If index is negative, start counting from the end, i.e. -1 is the last character.
	 * length: The number of characters to extract, or 0 for the remainder of the string. If negative, stop copying at -length characters from the end.
	 */
	string string::substr(ssize_t start, ssize_t length) const throw() {
		if (start < 0) {
			if ((size_t)(-start) > this->_length) { // For a n-char string, -n <= start <= n must be true. The second part is checked below.
				throw std::out_of_range("Negated negative start is greater than string length");
			}
			start = this->_length - (-start);
		}

		if (length == 0) {
			length = this->_length - start;
		}
		else if (length < 0) {
			length = this->_length - (-length) - start;
		}

		if (length < 0) {
			throw std::out_of_range("start/length combo for string::substr() results in a negative length");
		}
		if (length == 0)
			return exscape::string("");

		// XXX! Is this really enough?
		if ((size_t)(start + length) > this->_length)
			throw std::out_of_range("start+length in string::substr() is past the boundaries of the string");

		string out;
		out.alloc(length + 1);
		char *p = out.buf;
		for (size_t i = start; i < (size_t)(start+length); i++) {
			*p++ = this->buf[i];
		}

		return out;

	}

	void string::dump(void) const {
		if (this->buf == NULL) {
			if (DEBUG) std::cerr << "String (null) length=" << this->_length << ", size=" << this->_size << std::endl;
		}
		else {
			if (DEBUG) std::cerr << "String \"" << this->buf << "\", length=" << this->_length << ", size=" << this->_size << std::endl;
		}
	}
}

int main() {
/*
	exscape::string s = "FABECDA";
	exscape::string::iterator i = s.begin();
	for (i = s.begin(); i != s.end(); ++i)
		std::cout << *i << std::endl;

	std::sort(s.begin(), s.end());
	std::cout << "Sorted: " << s << std::endl;

	std::cout << "Count of A: " << std::count(s.begin(), s.end(), 'A') << std::endl;
	std::cout << "Count of B: " << std::count(s.begin(), s.end(), 'B') << std::endl;
	std::cout << "Count of X: " << std::count(s.begin(), s.end(), 'X') << std::endl;
*/

	// Permutation testing
	exscape::string perm = "012";
	do {
		std::cout << perm << std::endl;
	}
	while (std::next_permutation(perm.begin(), perm.end()-1));
	return 0;
}

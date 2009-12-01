#include <iostream> /* stream support for operators << and >>, plus debugging */
#include <cstring> /* strcat(), etc */
#include <cstdlib> /* malloc(), realloc(), free() */
#include <stdexcept> /* std::out_of_range */
#include "string.hpp"

// TODO: 
// * Fix operator>>? Only works for cin >>, and doesn't act like it's supposed to...
//
//  * Implement comparison operators, i.e. <, >, <=, >=
//    ... using a protected compare() that uses strcmp() internally
//    ... XXX: worth the trouble? str < str, str < char*, char* < str etc. 3 cases * 4 operators = 12 overloads...?
//
//  * const iterators; also, iterators can currently modify const strings.

namespace exscape {
	using std::cerr;

	/*
	 *
	 * Start of string implementation
	 *
	 */

	/* Initializes a string to an empty state */
	void string::init(void) {
		if (DEBUG) std::cerr << "In init() for string " << this << std::endl;
		this->buf = NULL;
		this->_length = 0;
		this->_size = 0;
	}

	/* Default constructor + Copy constructor from const char * */
	string::string(const char *in /* = NULL in .hpp */) : buf(NULL), _length(0), _size(0) {
		if (DEBUG) std::cerr << "In default / const char* copy constructor for string " << this << std::endl;
		*this = in;
	}

	/* Copy constructor from another string instance */
	string::string(const string &in) : buf(NULL), _length(0), _size(0) {
		if (DEBUG) std::cerr << "In string & copy constructor for string " << this << std::endl;
		*this = in;
	} 

	/* Destructor */
	string::~string() {
		if (DEBUG) std::cerr << "In destructor for string " << this << std::endl;
		this->dealloc();
	}

	/* Public, friendlier interface to alloc() */
	void string::resize(size_t target_size) {
		target_size += 1; // NUL
		if (DEBUG) std::cerr << "In resize() for string " << this << ", current size=" << this->_size << ", target_size=" << target_size << std::endl;
		if (this->_size >= target_size)
			return;
		this->alloc(target_size);
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
		this->buf = NULL;
		this->_length = 0;
		this->_size = 0;
	}

	/* Returns the string length, equal to strlen(this->buf) */
	size_t string::length(void) const {
		return this->_length;
	}
	
	size_t string::capacity(void) const {
		return this->_size - 1; // capacity() returns the amount of characters the strings can hold
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
		if (this->buf != NULL)
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
		if (DEBUG) std::cerr << " appended \"" << str << "\" to string " << this << std::endl;
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
	string string::operator+(const char *str) const {
		if (DEBUG) std::cerr << "In operator+(const char *) for string " << this << std::endl;
		string result = *this;
		result += str;
		return result;
	}

	/* Return a new string consisting of this + another string instance */
	string string::operator+(const string &str) const {
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

	/* Friend operator */
	bool operator==(const char *lhs, string &rhs) {
		return (rhs == lhs);
	}

	/* Friend operator */
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
		if (DEBUG) std::cerr << "In reverse() for string " << this << "(length=" << this->_length << ")" << std::endl;
	
		string rev;
		rev.resize(this->_length);

		iterator rev_it = rev.begin();
		reverse_iterator this_rend = this->rend(); // To use as a "cache"

		for (reverse_iterator ri = this->rbegin(); ri != this_rend; ++ri, ++rev_it) {
			*rev_it = *ri;
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
		std::cerr << "String \"" << (this->buf != NULL ? this->buf : "(null)") << "\", length=" << this->_length << ", size=" << this->_size << std::endl;
	}

	string::iterator string::begin(void) const {
		iterator s = iterator(this->buf);
		if (DEBUG) std::cerr << " In string::begin(), returning iterator " << &s << "; this->buf=" << &buf << ", this->_length = " << this->_length << ", so pointing to " << &(this->buf) << std::endl;
		return s;
	}

	bool string::is_palindrome_strict(void) const {
		iterator start = this->begin();
		iterator string_end = this->end();
		reverse_iterator end = this->rbegin();
		// Simple: loop from both ends, comparing characters until:
		// 1) We hit the end (not likely to happen!)
		// 2) The "end" pointer is now before or at the same position as the start pointer,
		//    at which point we've checked all we need to guarantee a correct result.
		for (; start != string_end; ++start, ++end) {
			if (*start != *end)
				return false;
			if (end <= start)
				return true;
		}

		return true;
	}

	bool string::is_palindrome(void) const {
		iterator start = this->begin();
		iterator string_end = this->end();
		reverse_iterator end = this->rbegin();
		// This one is a bit more complicated than the above one, but not by much.
		// We need to skip non-alphabetic characters, and only compare lowercase versions.
		// As such, we can't use the a for loop's third slot, due to the continue statements.
		while (start != string_end) {
			if (!::isalpha(*start)) {
				++start;
				continue;
			}
			if (!::isalpha(*end)) {
				++end;
				continue;
			}
			if (::tolower(*start) != ::tolower(*end))
				return false;
			if (end <= start)
				return true;

			++start, ++end;
		}

		return true;
	}


	string::iterator string::end(void) const {
		iterator e = iterator((char *)((char *)this->buf + (ptrdiff_t)this->_length)); // buf[_length] == '\0', so one past the end
		char *tmp = (this->buf + this->_length);
		if (DEBUG) std::cerr << " In string::end(), returning iterator " << &e << "; this->buf=" << &buf << ", this->_length = " << this->_length << ", so pointing to " << &tmp << std::endl;

		return e;
	}

	string::reverse_iterator string::rbegin(void) const {
		reverse_iterator s;
		if (this->_length > 0)
			s = reverse_iterator(this->buf + (this->_length - 1));
		else
			s = reverse_iterator(this->buf);

		if (DEBUG) std::cerr << " In string::rbegin(), returning reverse_iterator " << &s << "; this->buf=" << &buf << ", this->_length = " << this->_length << std::endl;
		return s;
	}

	string::reverse_iterator string::rend(void) const {
		reverse_iterator e = reverse_iterator(this->buf - 1);
		if (DEBUG) std::cerr << " In string::rend(), returning reverse_iterator " << &e << "; this->buf=" << &buf << ", this->_length = " << this->_length << ", so pointing to " << (&(this->buf)) - 1 << std::endl;

		return e;
	}

	/*
	 *
	 * End of string implementation
	 *
	 */

	string::iterator::iterator& string::iterator::operator=(const string::iterator &rhs) {
		if (this != &rhs) {
			this->p = rhs.p;
			this->base = rhs.base;
		}

		return *this;
	}

	/* Move the iterator forward one step */
	string::iterator::iterator &string::iterator::operator++() {
		p++;
		return *this;
	}

	/* Move the iterator forward one step */
	string::iterator::iterator string::iterator::operator++(int) {
		++(*this);
		return iterator(this->p - 1);
	}

	/* Move the iterator back one step */
	string::iterator &string::iterator::operator--() {
		p--;
		return *this;
	}

	/* Move the iterator back one step */
	string::iterator string::iterator::operator--(int) {
		--(*this);
		return iterator(this->p + 1);
	}

	/* Arithmetic operators */
	string::iterator &string::iterator::operator+=(const string::difference_type offset) {
		p += offset;
		return *this;
	}

	string::iterator &string::iterator::operator-=(const string::difference_type offset) {
		p -= offset;
		return *this;
	}

	string::iterator string::iterator::operator+(const string::difference_type offset) {
		iterator out (*this);
		return out += offset;
	}

	string::iterator string::iterator::operator-(const string::difference_type offset) { 
		iterator out = (*this);
		return out -= offset;
	}

	string::difference_type string::iterator::operator-(string::iterator &rhs) {
		return p - rhs.p;
	}

	string::iterator operator+(const int n, string::iterator out) {
		return out += n;
	}

	string::iterator operator-(const int n, string::iterator out) {
		return out -= n;
	}

	/*
	 *
	 * End of string::iterator implementation
	 *
	 */

	/*
	 *
	 * Start of string::reverse_iterator implementation
	 *
	 */

	/* Default constructor */
	string::reverse_iterator::reverse_iterator(void) : iterator() {
	}

	/* Destructor */
	string::reverse_iterator::~reverse_iterator() { 
	}

	/* Copy constructor */
	string::reverse_iterator::reverse_iterator(const string::reverse_iterator &rhs) {
		*this = rhs;
	}

	/* Most-used constructor; used by string to pass a pointer to the string base */
	string::reverse_iterator::reverse_iterator(char *in_ptr) : iterator(in_ptr) {
	}

	string::reverse_iterator::reverse_iterator &string::reverse_iterator::operator++() {
		p--;
		return *this;
	}

	string::reverse_iterator::reverse_iterator string::reverse_iterator::operator++(int) {
		++(*this);
		return reverse_iterator(this->p + 1);
	}

	string::reverse_iterator &string::reverse_iterator::operator--() {
		p++;
		return *this;
	}

	string::reverse_iterator string::reverse_iterator::operator--(int) {
		--(*this);
		return reverse_iterator(this->p - 1);
	}

	/* Arithmetic operators */
	string::reverse_iterator &string::reverse_iterator::operator+=(const string::difference_type offset) {
		p -= offset;
		return *this;
	}

	string::reverse_iterator &string::reverse_iterator::operator-=(const string::difference_type offset) {
		p += offset;
		return *this;
	}

	string::reverse_iterator string::reverse_iterator::operator+(const string::difference_type offset) {
		reverse_iterator out (*this);
		out -= offset;
		return out;
	}

	string::reverse_iterator string::reverse_iterator::operator-(const string::difference_type offset) { 
		reverse_iterator out = (*this);
		out += offset;
		return out;
	}

	string::difference_type string::reverse_iterator::operator-(string::reverse_iterator &rhs) {
		return p - rhs.p;
	}

	string::reverse_iterator operator+(const int n, string::reverse_iterator out) {
		out -= n;
		return out;
	}

	string::reverse_iterator operator-(const int n, string::reverse_iterator out) {
		out += n;
		return out;
	}

	/*
	 *
	 * End of string::reverse_iterator implementation
	 *
	 */

} // end namespace

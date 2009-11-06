#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdexcept>

namespace exscape {
	class string {
		protected:
		public:
			char *buf;
			size_t _length; // string length
			size_t _size; // bytes allocated

			void init();
			void alloc(size_t) throw();
			void dealloc(void);
			void assign(const char *);
			void append(const char *);

		public:
			string() { init(); }
			string(const string &);
			string(const char *);
			~string();
			const char *c_str(void) const;
			size_t length(void) const;
			bool empty(void) const;
			bool equals(const char *str) const;
			string & operator+=(const char *);
			string & operator+=(const string &);
			string operator+(const char *);
			string operator+(const string &);
			friend string operator+(const char *, const string &);
			string & operator=(const char *);
			string & operator=(const string &);
			char operator[](size_t) const;
			bool operator==(const char *) const;
			bool operator!=(const char *) const;
			friend bool operator==(const char *, string &);
			friend bool operator!=(const char *, string &);
			bool operator==(const string &) const;
			bool operator!=(const string &) const;
			friend std::ostream &operator<<(std::ostream &, string);
			friend std::istream &operator>>(std::istream &, string &);
			void dump(void) const; // XXX: Debugging
	};

	/* Initialiazes a string to an empty state */
	void string::init(void) {
		std::cerr << "In init() for string " << this << std::endl;
		this->buf = NULL;
		this->_length = 0;
		this->_size = 0;
	}

	/* Copy constructor from const char * */
	string::string(const char *in) {
		std::cerr << "In const char* copy constructor for string " << this << std::endl;
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
		std::cerr << "In destructor for string " << this << std::endl;
		this->dealloc();
	}

	/* Allocates/reallocates memory for a string */
	void string::alloc(size_t target_size) throw() {
		std::cerr << " In alloc() for string " << this << ", current size=" << this->_size << ", target_size=" << target_size << std::endl;

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

	/* Deallocates the memory associated with a string */
	void string::dealloc(void) {
		std::cerr << " In dealloc() for string " << this << std::endl;
		if (this->buf != NULL) {
			std::cerr << "  Calling free(" << &(this->buf) << ")" << std::endl;
			free(this->buf);
		}
		else
			std::cerr <<  "  Nothing to free, string was NULL" << std::endl;
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
		this->dealloc();
		this->init();
		this->append(str);
	}

	/* Internal function that appends a given C-style string to this exscape::string */
	void string::append(const char *str) {
		std::cerr << "In string::append() for destination string " << this << std::endl;
		if (str == NULL)
			return;

		size_t new_length = this->_length + strlen(str);
		this->alloc(new_length + 1);
		strcat(this->buf, str);
		this->_length = new_length;
	}

	/* Compares two strings; if their lengths don't match, compare byte for byte */
	bool string::equals(const char *str) const {
		std::cerr << " in equals() for " << this << " and const char *" << &str << std::endl;
		if (this->buf == NULL && str == NULL)
			return true;
		else if (this->buf == NULL || str == NULL)
			return false;
		if (this->_length != strlen(str))
			return false;

		return (strcmp(this->buf, str) == 0);
	}

	/* Concatenate this string with a C-style string */
	string & string::operator+=(const char *str) {
		std::cerr << "In operator+=(const char *) for string " << this << std::endl;
		this->append(str);
		return *this;
	}

	/* Concatenate this string with another string instance */
	string & string::operator+=(const string &str) {
		std::cerr << "In operator+=(const string &) for string " << this << std::endl;
		this->append(str.c_str());
		return *this;
	}

	/* Return a new string consisting of this + a C-style string */
	string string::operator+(const char *str) {
		std::cerr << "In operator+(const char *) for string " << this << std::endl;
		string result = *this;
		result += str;
		return result;
	}

	/* Return a new string consisting of this + another string instance */
	string string::operator+(const string &str) {
		std::cerr << "In operator+(const string &) for string " << this << std::endl;
		string result = *this;
		result += str.c_str();
		return result;
	}

	/* Friend function, to handle cases such as "abc" + string */
	string operator+(const char *lhs, const string &rhs) {
		std::cerr << "In operator+(const char *, const string &)" << std::endl;
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
	char string::operator[](size_t index) const {
		if (index >= this->_length)
			throw std::out_of_range("Index is out of bounds");

		return this->buf[index];
	}

	bool string::operator==(const string &rhs) const {
		std::cerr << "In operator== for strings " << this << " (" << this->c_str()  << ") and " << &rhs << " (" << rhs.c_str() << ")"<< std::endl;

		return this->equals(rhs.c_str());
	}

	bool string::operator==(const char *str) const { 
		std::cerr << "In operator== (const char *)" << std::endl;
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
		std::cerr << "In operator!= for strings " << this << " and " << &rhs << std::endl;
		return !(*this == rhs);
	}

	bool string::operator!=(const char *str) const { 
		std::cerr << "In operator!= (const char *)" << std::endl;
		return !(this->equals(str));
	}

	/* Allow the class to be used with output streams, i.e. cout << str */
	std::ostream &operator<<(std::ostream &stream, string str) {
		stream << str.c_str();
		return stream;
	}
	
	/* Allows the class to be used with input stream, i.e. cin >> str */
	std::istream &operator>>(std::istream &stream, string &str) {
		// XXX: A way that didn't reallocate the string for every SINGLE BYTE
		// would be preferable...
		char tmp[2] = {0};
		char c;
		while (stream.get(c) && c != '\n') {
			tmp[0] = c;
			str.append(tmp);
		}

		return stream;
	}

	/* XXX: Debug function */
	void string::dump(void) const {
		if (this->c_str() == NULL)
			std::cerr << "String (null) length=" << this->_length << ", size=" << this->_size << std::endl;
		else
			std::cerr << "String \"" << this->c_str() << "\", length=" << this->_length << ", size=" << this->_size << std::endl;
	}
}

int main() {

	return 0;
}

/*
char *reverse(const char *str) {
	int len = strlen(str);
	char *rev = malloc(len+1); // +1 for NUL
	if (rev == NULL)
		return NULL;
	memset(rev, 0, len+1);

	for (uint32_t i=0; i<len; i++) {
		rev[len-i-1] = str[i];
	}

	return rev;
}

//
// * str: the string to work on
// * start: the starting offset (0 for the first position, 1 for the second etc.; negative offsets count from the end of the string, -1 being the last)
// * length: the length to extract. 0 extracts the remainder of the string; negative lengths stop at n characters from the end.
// *
char *substr(const char *str, int start, int length) {
	if (str == NULL)
		return NULL;
	const uint32_t str_length = strlen(str);

	// Calculate the starting position for negative start values
	if (start < 0) {
		if (-start > str_length) { // for a 5-char string, -5 <= start <= 5 must be true; the second part is checked below
			return NULL;
		}
		start = str_length - (-start); // describes itself. we start at str_length minus the negated start value.
									   //  start = str_length + start should do the same, but is less clear. 
	}

	if (length == 0) {
		length = str_length - start; // simple enough, the length is from the staring point to the end
	}
	else if (length < 0) {
		length = str_length - (-length) - start; // a bit more complicated; we need to subtract (the negated) length here, too
	}

	// If length is less than 0 even after the changes, call it quits.
	if (length < 0) {
		return NULL;
	}

	// Make sure we stay within the bounds of "str"
	if (start+length > str_length || 
		str <= ( (char *) ( (unsigned long)start + (unsigned long)length ) )) { // XXX: OBOE?
		return NULL;
	}

	char *out = malloc(length + 1);
	if (out == NULL)
		return NULL;
	memset(out, 0, length + 1);

	char *p = out;
	for (uint32_t i = start; i < start+length; i++) {
		*p++ = str[i];
	}

	return out;
	}
*/

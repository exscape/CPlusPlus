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
			void append(const char *);
			void set(const char *);

		public:
			string() { init(); }
			string(string &);
			string(const char *);
			~string();
			void dealloc(void);
			void resize(size_t) throw();
			const char *c_str(void) const;
			size_t length(void) const;
			bool empty(void) const;
			string & operator+=(const char *);
			string & operator+=(const string &);
			string operator+(const char *);
			string operator+(const string &);
			friend string operator+(const char *, const string &);
			string & operator=(const char *);
			string & operator=(const string &);
			void dump(void) const; // XXX: Debugging
			// XXX:
			// operator== and operator!=
			// operator[]
			// operator<<
	};

	/* Initialiazes a string to an empty state */
	void string::init(void) {
		std::cerr << "In init() for string " << this << std::endl;
		this->buf = NULL;
		this->_length = 0;
		this->_size = 0;
	}

	/* Deallocates the memory associated with a string */
	void string::dealloc(void) {
		std::cerr << "in string::dealloc() for string " << this << std::endl;
		if (this->buf != NULL) {
			std::cerr << "  calling dealloc(" << &(this->buf) << ")" << std::endl;
			free(this->buf);
		}
		this->_length = 0;
		this->_size = 0;
	}

	/* Resizes the buffer using realloc */
	void string::resize(size_t target) throw() {
		std::cerr << "In resize() for string " << this << ", current size=" << this->_size << ", target size=" << target << std::endl;
		char *new_buf = (char *)realloc(this->buf, target);
		if (new_buf) {
			this->buf = new_buf;
			this->_size = target;
		}
		else {
			free(this->buf);
			this->_size = 0;
			this->_length = 0;
			throw std::runtime_error("realloc() returned NULL");
		}
	}

	/* Copy constructor from const char * */
	string::string(const char *in) {
		this->buf = strdup(in);
		this->_length = strlen(this->buf);
		this->_size = this->_length + 1; // NUL
	}

	/* Copy constructor from another string instance */
	string::string(string &in) {
		this->buf = strdup(in.c_str());
		this->_length = strlen(this->buf);
		this->_size = this->_length + 1; // NUL
	} 

	/* Destructor */
	string::~string() {
		std::cerr << "In destructor for string " << this << std::endl;
		this->dealloc();
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

	/* Internal function that appends a given C-style string to this exscape::string */
	void string::append(const char *str) {
		std::cerr << "In string::append() for destination string " << this << std::endl;
		if (str == NULL)
			return;

		size_t new_size = this->_length + strlen(str);
		this->resize(new_size + 1);
		strcat(this->buf, str);
		this->_length = new_size;
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
	
	/* Set this string to str, by starting over and "appending" it */
	void string::set(const char *str) {
		this->dealloc();
		this->init();
		this->append(str);
	}

	/* Set this string to other string instance sstr */
	string & string::operator=(const string &str) {
		if (this == &str)
			return *this;

		this->set(str.c_str());
		return *this;
	}

	/* Set this string to C-string str */
	string & string::operator=(const char *str) {
		this->set(str);
		return *this;
	}

	/* XXX: Debug function */
	void string::dump(void) const {
		std::cerr << "String \"" << this->c_str() << "\", length=" << this->_length << ", size=" << this->_size << std::endl;
	}

}

int main() {
	exscape::string s, s2;
	s = "abc";
	s2 = "def" + s;

	s.dump();
	s2.dump();
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

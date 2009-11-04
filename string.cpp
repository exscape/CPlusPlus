#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdexcept>

namespace exscape {
	class string {
//		protected:
		// XXX: TESTING ONLY
		public:
			char *buf;
			size_t _length; // string length
			size_t _size; // bytes allocated

			void init();
			void append(const char *);

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
			// XXX:
			// operator+, using the above
			// operator=
			// operator== and operator!=
			// operator[]
	};

	void string::init(void) {
		std::cerr << "In init() for string " << this << std::endl;
		this->buf = NULL;
		this->_length = 0;
		this->_size = 0;
	}

	void string::dealloc(void) {
		std::cerr << "In dealloc() for string " << this << std::endl;
		if (this->buf != NULL)
			free(this->buf);
		this->_length = 0;
		this->_size = 0;
	}

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

	string::string(const char *in) {
		this->buf = strdup(in);
		this->_length = strlen(this->buf);
		this->_size = this->_length + 1; // NUL
	}

	string::string(string &in) {
		this->buf = strdup(in.c_str());
		this->_length = strlen(this->buf);
		this->_size = this->_length + 1; // NUL
	} 

	string::~string() {
		std::cerr << "In destructor for string " << this << std::endl;
		this->dealloc();
	}

	size_t string::length(void) const {
		return this->_length;
	}

	bool string::empty(void) const {
		return (this->_length == 0);
	}

	const char *string::c_str() const {
		return this->buf;
	}

	void string::append(const char *str) {
		std::cerr << "In string::append() for destination string " << this << std::endl;
		if (str == NULL)
			return;

		size_t new_size = this->_length + strlen(str);
		this->resize(new_size + 1);
		strcat(this->buf, str);
		this->_length = new_size;
	}

	string & string::operator+=(const char *str) {
		std::cerr << "In operator+=(const char *) for string " << this << std::endl;
		this->append(str);
		return *this;
	}

	string & string::operator+=(const string &str) {
		std::cerr << "In operator+=(const string &) for string " << this << std::endl;
		this->append(str.c_str());
		return *this;
	}
}

int main() {
	exscape::string str ("Hello, world!");
	std::cout << str.c_str() << std::endl; // XXX: overload <<
	std::cout << "String: \"" << str.c_str() << "\", string length: "<< str._length << ", size: " << str._size << std::endl;

	exscape::string str2 (str);
	std::cout << "String: \"" << str2.c_str() << "\", string length: "<< str2._length << ", size: " << str2._size << std::endl;

	str2 += " How are you doing?";
	std::cout << "String: \"" << str2.c_str() << "\", string length: "<< str2._length << ", size: " << str2._size << std::endl;

	exscape::string str3;
	str3 += str += str2;
	std::cout << "String: \"" << str3.c_str() << "\", string length: "<< str3._length << ", size: " << str3._size << std::endl;

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

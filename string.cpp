#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdexcept>

namespace exscape {
	class string {
		protected:
			char *buf;
			size_t _length; // string length
			size_t _size; // bytes allocated

			void init();
			void resize(size_t) throw();

		public:
			string() { init(); }
			string(const char *);
//			string(string &);
			~string();
			void dealloc(void);
			const char *c_str(void) const;
			size_t length(void) const;
			bool empty(void) const;
	};

	void string::init(void) {
		this->buf = NULL;
		this->_length = 0;
		this->_size = 0;
	}

	void string::dealloc(void) {
		if (this->buf != NULL)
			free(this->buf);
		this->_length = 0;
		this->_size = 0;
	}

	void string::resize(size_t target) throw() {
		char *new_buf = (char *)realloc(this->buf, target);
		if (new_buf)
			this->buf = new_buf;
		else {
			free(this->buf);
			throw std::runtime_error("realloc() returned NULL");
		}
	}

	string::string(const char *in) {
		this->buf = strdup(in);
		this->_length = strlen(this->buf);
		this->_size = this->_length + 1; // NUL
	}

	string::~string() {
		this->dealloc();
	}

	const char *string::c_str() const {
		return this->buf;
	}

/*	string::string(string &in) {
		this->buf = strdup(in.c_str());
		this->_length = strlen(this->buf);
	} */
}

int main() {
	exscape::string str = "Hello, world!";
	std::cout << str.c_str() << std::endl; // XXX: overload <<

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

#include <stdexcept>

class StackUnderflowException : public std::runtime_error {
	public:
	StackUnderflowException() : std::runtime_error("StackUnderflowException") {}
};

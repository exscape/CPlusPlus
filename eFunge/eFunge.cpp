#include <iostream>
#include <fstream>
#include <stack>
#include <deque>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <stdint.h>
#include <assert.h>
#include "../stack.cpp"

/*
 * PLEASE NOTE:
 * The vast majority of this code was written several years ago (at LEAST 3.5 years ago),
 * and has only been modified to use my stack implementation instead of the STL one,
 * to see how it works in practice.
 *
 * I had to port it from Windows-only to POSIX, so there are some other modifications. 
 * Still, most of the bad code is old. ;)
 */

template <class out_type, class in_type>
out_type Convert (in_type in)
{
	std::stringstream ss;
	ss << in;
	out_type out;
	ss >> out;
	return out;
}

inline void WarnUnderflow()
{
	std::cout << "Warning! Stack underflow occured, popped 0 instead of the value you probably wanted." << std::endl;
}

short rnd()
{
//    return int((rand()<<2)/(RAND_MAX + 1.0));
	short i = rand() % 4;
	assert(i >= 0 && i <= 3);
	return i;
}

//static std::stack <int64_t, std::deque<int64_t> > stack;
static exscape::stack<int64_t> stack;
static enum { RIGHT, LEFT, UP, DOWN } dir;
int64_t space[50][80];

//
// Moves the IP (Instruction Pointer) to the next cell
//
void next(unsigned short &x, unsigned short &y, int dir)
{
	switch (dir)
	{
	case RIGHT:
			x = (x==79? 0 : x+1);
		break;
	case LEFT:
			x = (x==0? 79 : x-1);
		break;

	case UP:
			y = (y==0? 49 : y-1);
		break;

	case DOWN:
			y = (y==49 ? 0 : y+1);
		break;
	}
}

int64_t peek(unsigned short x, unsigned short y, int dir)
{
	switch (dir)
	{
	case RIGHT:
			x = (x==79? 0 : x+1);
		break;
	case LEFT:
			x = (x==0? 79 : x-1);
		break;

	case UP:
			y = (y==0? 49 : y-1);
		break;

	case DOWN:
			y = (y==49 ? 0 : y+1);
		break;
	}
	return space[y][x];
}

int main(int argc, char *argv[])
{
	unsigned int writedelay = 0;
	// 
	// Print usage if filename isn't given as an argument
	//
	if (argc == 1)
	{
		std::cout << "eFunge 0.97, exscape Befunge Interpreter" << std::endl;
		std::cout << "http://exscape.org" << std::endl;
		std::cout << "jarjar@exscape.org" << std::endl;
		std::cout << std::endl << "Usage: " << argv[0] << " <-delay ms> [filename.bf]" << std::endl;
		std::cout << "-delay simulates typing by not writing everything at once, instead it pauses X milliseconds per letter." << std::endl;
		exit(1);
	}

	if (argc == 2)
		writedelay = 0;
	else if (argc == 4)
		writedelay = Convert<unsigned int>(argv[2]);
	else
	{
		std::cout << "Unknown error in arguments!" << std::endl;
		exit(1);
	}

	//
	// Open the file
	//
	std::fstream f;
	f.open(argv[(argc==2?1:3)]);
	if (!f.is_open())
	{
		std::cerr << "Error: Couldn't open file \"" << argv[(argc==2?1:3)] << "\"! Exiting..." << std::endl;
		exit(1);
	}

	// 
	// Initialize the Funge space (80x50)
	//
	for (int a=0; a<50; a++)
		for (int b=0; b<80; b++)
			space[a][b] = 32; /* int64_t(' ') */

	//
	// Read the file
	//
	char c = 0;
	unsigned short y=0, x=0;
	while (true)
	{
		if (!f.eof())
		{
			c = f.get();

			if (c != 0xa && c != 0xd)
				space[y][x] = c;
			else
			{
				if (c == 0xd)
					f.get();
				y++, x = 0;
				continue;
			}
			x++;
		}
		else
			break;
	}

	f.close();

	/*
	for (int a=0; a<50; a++)
		for (int b=0; b<80; b++)
			std::cout << char(space[a][b]);
	*/

	srand((unsigned)time(0));
	
	//
	// Create basic variables that will be used a *lot*...
	//
	dir = RIGHT;
	x = y = 0;
	bool stringmode = false;
	
	//
	// Main loop
	//
	while (true)
	{
		if (space[y][x] == 32 && !stringmode)
		{
			while (peek(x, y, dir) == 32)
				next(x, y, dir);
			
			next(x, y, dir);			
		}

		//
		// Check for invalid characters
		//
		if ((space[y][x] >= 127 || space[y][x] < 32) && !stringmode)
		{
			next(x, y, dir);
			continue;
		}

		c = (char)space[y][x];

		//
		// Handle stringmode
		//
		if (c == '\"')
		{
			stringmode = (stringmode ? 0 : 1);
			next (x, y, dir);
			continue;
		}

		//
		// Push ASCII values if in stringmode
		//
		if (stringmode == true && c != '\"')
		{
			stack.push(c);
			next(x, y, dir);
			continue;
		}

		//
		// Handle direction arrows
		//
		if (c == '<')
		{
			dir = LEFT;
			next(x,y,dir);
			continue;
		}
		else if (c == '>')
		{
			dir = RIGHT;
			next(x,y,dir);
			continue;
		}
		else if (c == '^')
		{
			dir = UP;
			next(x,y,dir);
			continue;
		}
		else if (c == 'v')
		{
			dir = DOWN;
			next(x,y,dir);
			continue;
		}
		else if (c == '?')
		{
			int d = rnd();

			switch (d)
			{

			case 0:
				dir = RIGHT;
				break;

			case 1:
				dir = LEFT;
				break;

			case 2:
				dir = UP;
				break;

			case 3:
				dir = DOWN;
				break;

			default:
				std::cout << "WARNING!!! Random value was " << d << " (range is 0-3!)" << std::endl;
				exit(0);
				break;
			}
			
			next(x, y, dir);
			continue;
		}

		//
		// Handle @
		//
		if (c == '@')
		{
			std::cout << std::endl << std::endl << "Program ended at [" << x << ", " << y << "]." << std::endl;
			exit(0);
		}

		//
		// 0-9: push the number
		//
		if (c>='0' && c<='9')
		{
			stack.push(c-48); // '0'-48 = 0, '1'-48 = 1 etc... ASCII -> number
			next(x, y, dir);
			continue;
		}

		//
		// .: Pop a number and print it
		//
		if (c == '.')
		{
			if (!stack.empty())
			{
				std::cout << stack.top();
				stack.pop();
			}
			else
			{
				std::cout << 0;
				WarnUnderflow();
			}

			if (writedelay)
				usleep(writedelay * 1000);

			next(x, y, dir);
			continue;
		}

		//
		// ,: Pop a character and print it
		//
		else if (c == ',')
		{
			if (!stack.empty())
			{
				std::cout << char(stack.top());
				stack.pop();
			}
						
			if (writedelay)
				usleep(writedelay * 1000);
			next(x, y, dir);
			continue;
		}

		//
		// Pop a, b and push a+b
		//
		if (c == '+')
		{
			int64_t a=0, b=0;
			if (!stack.empty())
			{
				a = stack.top();
				stack.pop();
				if (!stack.empty())
				{
					b = stack.top();
					stack.pop();
				}
				else
				{
					b = 0;
					WarnUnderflow();
				}
			}
			else
			{
				a = 0, b = 0;
				WarnUnderflow();
			}

			stack.push(a+b);
			next(x, y, dir);
			continue;
		}

		//
		// Pop a, b and push b-a
		//
		if (c == '-')
		{
			int64_t a=0, b=0;
			if (!stack.empty())
			{
				a = stack.top();
				stack.pop();
				if (!stack.empty())
				{
					b = stack.top();
					stack.pop();
				}
				else
				{
					b = 0;
					WarnUnderflow();
				}
			}
			else
			{
				a = 0, b = 0;
				WarnUnderflow();
			}

			stack.push(b-a);
			next(x, y, dir);
			continue;
		}

		//
		// Pop a, b and push a*b
		//
		if (c == '*')
		{
			int64_t a=0, b=0;
			if (!stack.empty())
			{
				a = stack.top();
				stack.pop();
				if (!stack.empty())
				{
					b = stack.top();
					stack.pop();
				}
				else
				{
					b = 0;
					WarnUnderflow();
				}
			}
			else
			{
				a = 0, b = 0;
				WarnUnderflow();
			}

			stack.push(a*b);
			next(x, y, dir);
			continue;
		}

		//
		// Pop a, b and push b/a
		//
		if (c == '/')
		{
			int64_t a=0, b=0;
			if (!stack.empty())
			{
				a = stack.top();
				stack.pop();
				if (!stack.empty())
				{
					b = stack.top();
					stack.pop();
				}
				else
				{
					b = 0;
					WarnUnderflow();
				}
			}
			else
			{
				a = 0, b = 0;
				WarnUnderflow();
			}

			if (a != 0)
				stack.push(b/a);
			else
			{
				std::cout << "WARNING: Division by zero! Exiting!" << std::endl;
				exit(0);
			}
			next(x, y, dir);
			continue;
		}

		//
		// Pop a, b and push b%a
		//
		if (c == '%')
		{
			int64_t a=0, b=0;
			if (!stack.empty())
			{
				a = stack.top();
				stack.pop();
				if (!stack.empty())
				{
					b = stack.top();
					stack.pop();
				}
				else
				{
					b = 0;
					WarnUnderflow();
				}
			}
			else
			{
				a = 0, b = 0;
				WarnUnderflow();
			}

			if (a != 0)
				stack.push(b%a);
			else
			{
				std::cout << "WARNING: Division by zero! Exiting!" << std::endl;
				exit(0);
			}
			next(x, y, dir);
			continue;
		}

		//
		// Pop a value, if it's 0; push 1. If not, push 0.
		//
		if (c == '!')
		{
			if (!stack.empty())
			{
				if (stack.top() == 0)
				{
					stack.pop();
					stack.push(1);
				}
				else
				{
					stack.pop();
					stack.push(0);
				}
			}
			else
			{
				stack.push(1);
				WarnUnderflow();
			}

			next(x, y, dir);
			continue;
		}

		//
		// Pop a, b. Push 1 if b>a, 0 otherwise.
		//
		if (c == '`')
		{
			int64_t a=0, b=0;
			if (!stack.empty())
			{
				a = stack.top();
				stack.pop();
				if (!stack.empty())
				{
					b = stack.top();
					stack.pop();
				}
				else
				{
					b = 0;
					WarnUnderflow();
				}
			}
			else
			{
				a = 0, b = 0;
				WarnUnderflow();
			}

			if (b>a)
				stack.push(1);
			else
				stack.push(0);

			next(x, y, dir);
			continue;
		}

		//
		// IF: Pop a value, move right if zero, left otherwise.
		//
		if (c == '_')
		{
			if (!stack.empty())
			{
				if (stack.top() == 0)
				{
					dir = RIGHT;
					next (x, y, dir);
					stack.pop();
				}
				else
				{
					dir = LEFT;
					next (x, y ,dir);
					stack.pop();
				}
			}
			else
			{
				dir = RIGHT;
				next (x, y, dir);
				WarnUnderflow();
			}
		}

		//
		// IF: Pop a value, move down if zero, up otherwise.
		//
			if (c == '|')
		{
			if (!stack.empty())
			{
				if (stack.top() == 0)
				{
					dir = DOWN;
					next (x, y, dir);
					stack.pop();
				}
				else
				{
					dir = UP;
					next (x, y ,dir);
					stack.pop();
				}
			}
			else
			{
				dir = DOWN;
				next (x, y, dir);
				WarnUnderflow();
			}
		}

		//
		// Pop a value, push it twice
		//
		if (c == ':')
		{
			if (!stack.empty())
			{
				stack.push(stack.top());
			}
			else
			{
				stack.push(0);
				stack.push(0);
				WarnUnderflow();
			}
			
			next(x, y, dir);
			continue;
		}

		//
		// Pop a and b, and push them in the reverse order
		//
		if (c == '\\')
		{
			int64_t a=0, b=0;
			if (!stack.empty())
			{
				a = stack.top();
				stack.pop();
				if (!stack.empty())
				{
					b = stack.top();
					stack.pop();
				}
				else
				{
					b = 0;
					WarnUnderflow();
				}
			}
			else
			{
				a = b = 0;
				WarnUnderflow();
			}

			stack.push(a);
			stack.push(b);

			next(x, y, dir);
			continue;
		}

		// 
		// Pop a value and discard it
		//
		if (c == '$')
		{
			if (!stack.empty())
				stack.pop();
			next(x, y, dir);
			continue;
		}

		// 
		// Skip the next cell
		//
		if (c == '#')
		{
			next (x, y, dir);
			next (x, y, dir);
			continue;
		}

		// 
		// Pop y and x, then push ASCII value of char at that position in the program
		//
		if (c == 'g')
		{
			int64_t a=0, b=0;
			if (!stack.empty())
			{
				a = stack.top();
				stack.pop();
				if (!stack.empty())
				{
					b = stack.top();
					stack.pop();
				}
				else
				{
					b = 0;
					WarnUnderflow();
				}
			}
			else
			{
				a = 0, b = 0;
				WarnUnderflow();
			}

			if (a>49)
			{
				std::cout << "WARNING: Out of bounds! Using Y=49!" << std::endl;
				a = 49;
			}
			if (b>79)
			{
				std::cout << "WARNING: Out of bounds! Using X=79!" << std::endl;
				b = 79;
			}

			stack.push(space[a][b]);			

			next(x, y, dir);
			continue;
		}

		// 
		// Pop y, x and v, then set position x,y to character v
		//
		if (c == 'p')
		{
			int64_t a=0, b=0, v=0;
			if (!stack.empty())
			{
				a = stack.top();
				stack.pop();
				if (!stack.empty())
				{
					b = stack.top();
					stack.pop();
					if (!stack.empty())
					{
						v = stack.top();
						stack.pop();
					}
					else
					{
						v = 0;
						WarnUnderflow();
					}
				}
				else
				{
					v = 0, b = 0;
					WarnUnderflow();
				}
			}
			else
			{
				a = 0, b = 0, v = 0;
				WarnUnderflow();
			}

			if (a>49)
			{
				std::cout << "WARNING: Out of bounds! Using Y=49!" << std::endl;
				a = 49;
			}
			if (b>79)
			{
				std::cout << "WARNING: Out of bounds! Using X=79!" << std::endl;
				b = 79;
			}

			space[a][b] = v;
			
			next(x, y, dir);
			continue;
		}

		if (c == '&')
		{
			int64_t a;
			std::cout << "Enter a number: ";
			std::cin >> a;

			stack.push(a);

			next(x, y, dir);
			continue;
		}

		if (c == '~')
		{
			char a;
			std::cout << "Char: ";
			while ((a = getchar()) == 0xa);
			stack.push(a); 
			
			next(x, y, dir);
			continue;
		}	
		
	}

	return 0;
}

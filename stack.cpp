#include <iostream>

/* Written: 2009-11-02, XXX */

namespace exscape {
	class stack {

		typedef struct _node {
			struct _node *next;
			int data;
		} node;

		private:
		node *head;

		public:
		stack();
		~stack();
		void push(int const &elem);
		int pop(void);
		int size(void);
	};

	stack::stack() {
		std::cout << "Hello, stack!" << std::endl;
	}

	stack::~stack() {
		std::cout << "Goodbye, stack." << std::endl;
	}

	int stack::size(void) {
		int len = 0;
		for (node *n = this->head; n != NULL; n = n->next)
			len++;

		return len;
	}

	void stack::push(int const &elem) {
		node *n = new node;
		n->data = elem;
		n->next = this->head;
		this->head = n;
		std::cout << "Push " << elem << std::endl;
	}

	int stack::pop(void) {
		if (stack::size() == 0)
			return -1; // XXX: Exception
		int data = this->head->data;
		node *new_head = this->head->next;
		delete this->head;
		this->head = new_head;

		return data;
	}
}

int main() {
	exscape::stack s;
	s.push(10);
	s.push(20);
	s.push(30);
	std::cout << "Pop: " << s.pop() << std::endl;
	std::cout << "Pop: " << s.pop() << std::endl;
	std::cout << "Pop: " << s.pop() << std::endl;
	std::cout << "Pop: " << s.pop() << std::endl; // One pop too much
	return 0;
}

/*
void create_add_node(node **head, const char *str, int where) {
	node *new = malloc(sizeof(node));
	set_node_data(&new, str);
	new->next = NULL;

	if (where == START) {
		new->next = *head;
		*head = new;
	}
	else if (where == END) {
		node *n;
		for (n = *head; n->next != NULL; n = n->next)
			;
		n->next = new;
	}
	else {
		fprintf(stderr, "Error: invalid \"where\" value specificed for create_add_node\n");
		exit(1);
	}
}
char *Pop(node **head) {
	if (Length(head) == 0)
		return NULL;
	
	node *new_head = (*head)->next;
	char *data = strdup((*head)->data);
	free(*head);
	*head = new_head;

	return data;
}

int main() {
	node *list = NULL;
	create_add_node(&list, "Alpha", START);
	printf("Length after adding 1 element: %zu\n", Length(&list));

	create_add_node(&list, "Beta", START);
	create_add_node(&list, "Gamma", END);
	create_add_node(&list, "Omega", START);
	create_add_node(&list, "Alpha", END);

	printf("Length with 5 elements: %zu\n", Length(&list));

	print_list(&list);

	printf("Count(Alpha): %d\n", Count(&list, "Alpha"));
	printf("Count(Omega): %d\n", Count(&list, "Omega"));
	printf("Count(Delta): %d\n", Count(&list, "Delta"));

	for (int i=0; i<3; i++) {
		char *s = Pop(&list);
		printf("Pop: %s\n", s);
		printf("New length: %zu\n", Length(&list));
		free(s);
	}

	free_list(&list);
	printf("Length after freeing: %zu\n", Length(&list));
	return 0;
}
*/

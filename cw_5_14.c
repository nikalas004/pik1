#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	char data[15];
	struct node * next;
};
typedef struct node t_Node;

void print_list(t_Node *list);
void add_to_list(char string[15], t_Node *list);
void remove_from_list(t_Node *list);
t_Node* find_in_list(char string[15], t_Node *list);

int main() {
	t_Node *list = NULL;
	list = (t_Node *) malloc(sizeof(t_Node));
	strcpy(list->data, "neshto");
	free(list);
	find_in_list("edno", list);
	print_list(list);
	return 0;
}

void print_list(t_Node *list) {
	t_Node *current = list;
	while(current->next != NULL) {
		printf("%s \n", current->data);
		current = current->next;
	}
	printf("%s \n", current->data);
}

void add_to_list(char string[15], t_Node *list) {
	t_Node *current = list;
	while(current->next != NULL) {
		current = current->next;
	}
	current->next = (t_Node *) malloc(sizeof(t_Node));
	strcpy(current->next->data, string);
	current->next->next = NULL;
}

void remove_from_list(t_Node *list) {
	t_Node *del = list;
	*list = *list->next;
	free(del);
}

t_Node* find_in_list(char string[15], t_Node *list) {
	t_Node *current = list;
	while(current->next != NULL) {
		if(!strcmp(current->data, string)) {
			return current;
		}
		current = current->next;
	}
}

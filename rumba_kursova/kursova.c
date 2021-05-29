#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getch.c"

typedef struct {
	int id;
	char name[50];
	float deposit;
	int months;
} Client_t;

struct node{
	Client_t data;
	struct node *next;
};

typedef struct node Node_t;

int menu(void);
void print_menu(char menu[5][100]);
void add_client(Node_t **head);
int enter_id(Node_t **head);
void client_with_deposits_over_date(Node_t **head);
void remove_client(Node_t **head);
void edit_client(Node_t **head);
void read_from_file(Node_t **head);
void memory_clear(Node_t **head);
void print_all(Node_t **head);

int main() {
	Node_t *head = NULL;
	char filename[7] = "db.bin";

	int user_input = 10;
	void (*func_ptr[5])(Node_t**) = {add_client, client_with_deposits_over_date, remove_client, edit_client, print_all};
	 
	read_from_file(&head);
	
	while(user_input != 5) {
		user_input = menu();
		if(user_input < 5) {
			func_ptr[user_input](&head);
		}
		if(user_input != 3) {
			getch();
		}
		if(user_input != 5) {
			printf("Press any key to continue...");
			getch();
		}
	}
	
	memory_clear(&head);
	
	system("clear");
	printf("End of program\n");
	
	return 0;
}

void read_from_file(Node_t **head) {
	FILE *fp = fopen("db.bin", "ab+");
	Node_t *node = malloc(sizeof(Node_t));
	while(fread(&(node->data.id), sizeof(int), 1, fp)) {
		fread(node->data.name, sizeof(char)*50, 1, fp);
		fread(&(node->data.deposit), sizeof(float), 1, fp);
		fread(&(node->data.months), sizeof(int), 1, fp);
		
		node->next = *head;
		*head = node;
		node = malloc(sizeof(Node_t));
	}
	fclose(fp);
}

void memory_clear(Node_t **head) {
	Node_t *current = *head;
	Node_t *fr;
	
	FILE *fp = fopen("db.bin", "wb");
	
	while(current != NULL) {
		fwrite(&(current->data.id), sizeof(int), 1, fp);
		fwrite(current->data.name, sizeof(char)*50, 1, fp);
		fwrite(&(current->data.deposit), sizeof(float), 1, fp);
		fwrite(&(current->data.months), sizeof(int), 1, fp);
		fr = current;
		current = current->next;
		free(fr);
	}
	
	fclose(fp);
}

int menu(void) {
	char menu_options[6][100] = {"1. Add client\n", "2. Client with deposits over date\n", "3. Delete clients\n", "4. Edit client's name\n", "5. Print all\n", "6. Exit\n"};
	int user_input;
	
	print_menu(menu_options);
	printf("Enter an option: ");
	do {
		scanf("%d", &user_input);
		if(user_input < 1 || user_input > 6) {
			printf("Please enter valid option(between 1 and 5): ");
		}
	}while(user_input < 1 || user_input > 6); 
	
	system("clear");
	return user_input-1;
}

void print_menu(char menu[6][100]) {
	system("clear");
	for(int i = 0; i < 6; i++) {
		printf("%s", menu[i]);
	}
}

void add_client(Node_t **head) {
	Node_t *new_client = malloc(sizeof(Node_t));
	new_client->data.id = enter_id(head);
	getch();
	printf("Enter client name: ");
	fgets(new_client->data.name, 50, stdin);
	printf("Enter clients's deposit amount: ");
	scanf("%f", &(new_client->data.deposit));
	printf("Enter months the deposit spent in the bank: ");
	scanf("%d", &(new_client->data.months));

	new_client->next = *head;
	*head = new_client; 
}



int enter_id(Node_t **head) {
	int id;
	int id_flag = 0;
	printf("Enter clients's id: ");
	do {
		id_flag = 0;
		scanf("%d", &id);
		Node_t *current = *head;
		while(current != NULL) {
			if(current->data.id == id) {
				printf("That id already exists. Please enter another: ");
				id_flag = 1;
			}
			current = current->next;
		}
	}while(id_flag);

	return id;	
}

void client_with_deposits_over_date(Node_t **head) {
	int months;
	int count = 0;
	printf("Enter number of months: ");
	scanf("%d", &months);
	
	Node_t *current = *head;
	while(current != NULL) {
		if(current->data.months > months) {
			count++;
		}
		current = current->next;
	}
	
	printf("The number of depostist which spent more than %d months in the bank is: %d\n", months, count);
}

void remove_client(Node_t **head) {
	int id;
	int flag = 0;
	printf("Enter clients's id: ");
	scanf("%d", &id);
	
	Node_t *current = *head;
	Node_t *rm;
	while(current->next != NULL) {
		if(current->next->data.id == id) {
			rm = current->next;
			current->next = current->next->next;
			free(rm);
			flag = 1;
			break;
		}
		current = current->next;
	}
	
	if(flag){
		printf("Client with id: %d removed.\n", id);
	} else {
		printf("Client with id: %d can't be found.\n", id);
	}
}

void edit_client(Node_t **head) {
	int id;
	int flag = 0;
	Node_t *current = *head;
	
	printf("Enter clients's id: ");
	scanf("%d", &id);
	getch();

	while(current != NULL) {
		if(current->data.id == id) {
			printf("Enter new client name: ");
			fgets(current->data.name, 50, stdin);
			flag = 1;
			break;
		}
		current = current->next;
	}
	
	if(flag){
		printf("Client with id: %d edited.\n", id);
	} else {
		printf("Client with id: %d can't be found.\n", id);
	}
}

void print_all(Node_t **head) {
	Node_t *current = *head;
	while(current != NULL) {
		printf("-------------------------------\n");
		printf("Id: %d\n", current->data.id);
		printf("Name: %s", current->data.name);
		printf("Deposit: %.2f\n", current->data.deposit);
		printf("Months: %d\n", current->data.months);
		printf("-------------------------------\n");
		current = current->next;
	}
}


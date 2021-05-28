#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getch.c"

typedef struct {
	long num;
	char name[20];
	int key;
	char deliver[80];
	char date[11];
	int quantity;	
} Delivery_t;

struct Node_t{
	Delivery_t data;
	struct Node_t *next;
};
typedef struct Node_t Node_t;  

int menu(void);
void print_menu(char menu_list[5][50], int user);
void add_delivery(Node_t **head);
long enter_delivery_number(Node_t **head);
int digits_check(long n);
int enter_delivery_key(void);
void enter_date(char *date);
void deliveries_by_moth(Node_t *head);
void int_to_char(int month, char *month_c);
void print_delivery(Delivery_t delivery);
void stcock_total_quantity(Node_t *head);
void all_deliver_info_for_stock(Node_t *head);
void year_to_string(int year, char *year_c);

int main(int argc, char *argv[]) {
	Node_t *head = NULL;
	FILE *fp = NULL;
	int user_input = 5; 
	char filename[30] = "delivery_data.bin";
	long buff = 0;
	if(argc > 1) {
		strcpy(filename, argv[1]);
	}
	
	if(!(fp = fopen(filename, "ab+"))) {
		perror("Error opening file!");
		exit(-1);
	}
	
	Node_t *new_node = malloc(sizeof(Node_t));
	while((buff += fread(&(new_node->data.num), sizeof(long), 1, fp+buff)) == sizeof(long)) {
		buff += fread(new_node->data.name, sizeof(char)*20, 1, fp+buff);
		buff += fread(&(new_node->data.key), sizeof(int), 1, fp);
		buff += fread(new_node->data.deliver, sizeof(char)*80, 1, fp+buff);
		buff += fread(new_node->data.date, sizeof(char)*11, 1, fp+buff);
		buff += fread(&(new_node->data.quantity), sizeof(int), 1, fp+buff);
		if(head == NULL) {
			new_node->next = NULL;
			head = new_node;
		} else {
			new_node->next = head;
			head = new_node;
			new_node = malloc(sizeof(Node_t));
		}
	}
	
	while(user_input != 4) {
		user_input = menu();
		system("clear");
		switch(user_input) {
			case 0:
				add_delivery(&head);
				break;
			case 1:
				deliveries_by_moth(head);
				break;
			case 2:
				stcock_total_quantity(head);
				break;
			case 3:
				all_deliver_info_for_stock(head);
				break;
		}
		printf("Press any key to continue...");
		getch();
		
	}
	
	system("clear");
	Node_t *current = head;
	printf("%ld\n", buff);
	while(current != NULL) {
		fwrite(&(current->data.num), sizeof(long), 1, fp+buff);
		buff += sizeof(long);
		printf("%ld\n", buff);
		buff += fwrite(current->data.name, sizeof(char)*20, 1, fp+buff);
		buff += sizeof(char)*20;
		//buff += fwrite(&(current->data.key), sizeof(int), 1, fp+buff);
		//buff += fwrite(current->data.deliver, sizeof(char)*80, 1, fp+buff);
		//buff += fwrite(current->data.date, sizeof(char)*11, 1, fp+buff);
		//buff += fwrite(&(current->data.quantity), sizeof(int), 1, fp+buff);
		current = current->next;
	}
	
	current = head;
	while(current != NULL) {
		Node_t *for_free = current->next;
		free(current);
		current = for_free;
	}
	fclose(fp);
	
	printf("End of program\n");
	
	return 0;
}

int menu(void) {
	char menu_options[5][50] = {"1.Add delivery\n", "2.Deliveries for month\n", "3.Total quantity of stock\n", "4.All deliver information for a stock\n", "5.Exit\n"};
	int user = 0;
	char user_input = 0;
	while(1) {
		print_menu(menu_options, user);
		user_input = getch();
		if(user_input == '\033') {
			getch();
			switch(getch()) {
				case 'A':
					user--;
					if(user < 0) {
						user = 4;
					}
					break;
				case 'B':
					user++;
					if(user == 5) {
						user = 0;
					}
					break;
			}
		} else if(user_input == '\n') {
			return user;
		}
	}
	
}

void print_menu(char menu_list[5][50], int user) {
	system("clear");
	for(int i = 0; i < 5; i++) {
		if(i == user) {
			printf("> ");
		}
		printf("%s", menu_list[i]);
	}
}

void add_delivery(Node_t **head) {
	Node_t *new_node = malloc(sizeof(Node_t));
	new_node->data.num = enter_delivery_number(head);
	printf("Enter delivery name: ");
	getch();
	fgets(new_node->data.name, 20, stdin);
	new_node->data.key = enter_delivery_key();
	printf("Enter deliver information: ");
	getch();
	fgets(new_node->data.deliver, 80, stdin);
	enter_date(new_node->data.date);
	printf("Enter delivered quantity: ");
	scanf("%d", &(new_node->data.quantity));
	getch();
	if(*head == NULL) {
		*head = new_node;
		return;
	}
	Node_t *current = *head;
	while(current->next != NULL) {
		current = current->next;
	}
	
	current->next = new_node;
}

long enter_delivery_number(Node_t **head) {
	int id_flag = 0;
	int dig_flag = 1;
	long del_num;
	Node_t *current = *head;
	printf("Enter delivery number(12 digitis): ");
	do {
		id_flag = 0;
		dig_flag = 1;
		scanf("%ld", &del_num);
		while(current != NULL) {
			if(current->data.num == del_num) {
				id_flag = 1;
				printf("This delivery number already exits!\n");
				break;
			}
			current = current->next;
		}
		if(digits_check(del_num) != 4) {
			printf("The delivery nuber has to contain 12 digits!\n");
		} else {
			dig_flag = 0;
		}
		if(id_flag || dig_flag) {
			printf("Please enter another delivery number:");
		}
	}while(id_flag || dig_flag);
	
	return del_num;
}

int digits_check(long n) {
	int digits;
	for(digits = 0; n != 0; n /= 10) {
		++digits;
	}
	
	return digits;
}

int enter_delivery_key(void) {
	int dig_flag = 1;
	int key;
	printf("Enter delivery key(8 digits):");
	do {
		dig_flag = 1;
		scanf("%d", &key);
		if(digits_check(key) != 8) {
			printf("The delivery nuber has to contain 8 digits!\nPlease enter valid delivery key: ");
		} else {
			dig_flag = 0;
		}
	}while(dig_flag);
	
	return key;
}

void enter_date(char *date) {
	int valid_data = 0;
	printf("Enter delivery date(DD-MM-YYYY): ");
	do{
		valid_data = 0;
		fgets(date, 11, stdin);
		for(int i = 0; i < 10; i++) {
			if(i == 2 || i == 5) {
				if((*(date+i) != '-') && valid_data == 0) {
					printf("Please enter vlaid delivery date(DD-MM-YYYY): ");
					valid_data = 1;
				}
			} else if((*(date+i) < '0' || *(date+i) > '9') && valid_data == 0) {
				printf("Please enter vlaid delivery date(DD-MM-YYYY): ");
				valid_data = 1;
			} 
		}
	}while(valid_data);
}

void deliveries_by_moth(Node_t *head) {
	int year;
	printf("Enter year: ");
	scanf("%d", &year);
	char year_c[5];
	year_to_string(year, year_c);
	int month;
	printf("Enter month: ");
	do {
		scanf("%d", &month);
		if(month < 1 || month > 12) {
			printf("Please enter valid month: ");
		}
	} while(month < 1 || month > 12);
	
	char month_c[10];
	int_to_char(month, month_c);
	month_c[2] = 0;
	Node_t *current = head;
	char buffer[10];
	while(current != NULL) {
		strncpy(buffer, current->data.date+3, 7);
		buffer[7] = 0;
		strcat(month_c, "-");
		strcat(month_c, year_c);
		if(!strcmp(month_c, buffer)) { 
			print_delivery(current->data);
		}
		current = current->next;
	}
	getch();
}

void year_to_string(int year, char *year_c) {
	for(int i = 3; year != 0; year /= 10, i--){
		switch(year % 10) {
			case 1:
				*(year_c+i) = '1';
				break;
			case 2:
				*(year_c+i) = '2';
				break;
			case 3:
				*(year_c+i) = '3';
				break;
			case 4:
				*(year_c+i) = '4';
				break;
			case 5:
				*(year_c+i) = '5';
				break;
			case 6:
				*(year_c+i) = '6';
				break;
			case 7:
				*(year_c+i) = '7';
				break;
			case 8:
				*(year_c+i) = '8';
				break;
			case 9:
				*(year_c+i) = '9';
				break;
			case 0:
				*(year_c+i) = '0';
				break;
		}
	}
	*(year_c+4) = 0;
}

void int_to_char(int month, char *month_c) {
	switch(month) {
		case 1:
			*month_c = '0';
			*(month_c+1) = '1';
			break;
		case 2:
			*month_c = '0';
			*(month_c+1) = '2';
			break;
		case 3:
			*month_c = '0';
			*(month_c+1) = '3';
			break;
		case 4:
			*month_c = '0';
			*(month_c+1) = '4';
			break;
		case 5:
			*month_c = '0';
			*(month_c+1) = '5';
			break;
		case 6:
			*month_c = '0';
			*(month_c+1) = '6';
			break;
		case 7:
			*month_c = '0';
			*(month_c+1) = '7';
			break;
		case 8:
			*month_c = '0';
			*(month_c+1) = '8';
			break;
		case 9:
			*month_c = '0';
			*(month_c+1) = '9';
			break;
		case 10:
			*month_c = '1';
			*(month_c+1) = '0';
			break;
		case 11:
			*month_c = '1';
			*(month_c+1) = '1';
			break;
		case 12:
			*month_c = '1';
			*(month_c+1) = '2';
			break;
	}
}

void print_delivery(Delivery_t delivery) {
	printf("----------------------------------\n");
	printf("Delivery number: %ld\n", delivery.num);
	printf("Delivery name: %s", delivery.name);
	printf("Deliver key: %d\n", delivery.key);
	printf("Deliver information: %s", delivery.deliver);
	printf("Delivery date: %s\n", delivery.date);
	printf("Delivery quantity: %d\n", delivery.quantity);
	printf("----------------------------------\n");
}

void stcock_total_quantity(Node_t *head) {
	char stock[20];
	int quantity = 0;
	printf("Enter name of stock: ");
	fgets(stock, 20, stdin);
	Node_t *current = head;
	while(current != NULL) {
		if(!strcmp(current->data.name, stock)) {
			quantity += current->data.quantity;
		}
		current = current->next;
	}
	
	printf("Quantity: %d\n", quantity);
}

void all_deliver_info_for_stock(Node_t *head) {
	char stock[20];
	printf("Enter name of stock: ");
	fgets(stock, 20, stdin);
	Node_t *current = head;
	while(current != NULL) {
		if(!strcmp(current->data.name, stock)) {
			printf("----------------------------------\n");
			printf("%s", current->data.deliver);
			printf("----------------------------------\n");
		}
		current = current->next;
	}
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getch.c"

typedef enum {
	HIDDEN = 1,
	READ_ONLY,
	SYSTEM_FILE,
	EXECUTABLE,
} File_flag_e;

typedef struct {
	char name[100];
	char path[500];
	int size;
	int creation_date[3];
	int last_modified_date[3];
	File_flag_e flag;
} File_t;

struct Node_t{
	File_t data;
	struct Node_t *next;
};
typedef struct Node_t Node_t;   

int menu(void);
void print_menu(char menu_list[4][20], int user);
void add_file(FILE *fp, Node_t *head);
void find_file(FILE *fp, Node_t *head);
void print_dir(FILE *fp, Node_t *head);
void print_flag(File_flag_e flag);
int folder_in_dir(char* dir, File_t file);

int main(int argc, char *argv[]) {
	int user_input = 10;
	Node_t *head = NULL;
	FILE *fp = NULL;
	char filename[100] = "files_db.bin";
	int files = 0;
	
	if(argc > 1) {
		strcpy(filename, argv[1]);	
	}
	if((fp = fopen(filename, "rb")) == NULL) {
		fp = fopen(filename, "ab+");
		fwrite(&files, sizeof(int), 1, fp);
	}
	
	/*while(user_input != 3) {
		user_input = menu();
	}*/
	
	fclose(fp);
	return 0;
}

int menu(void) {
	char menu_options[4][20] = {"1.Add file\n", "2.Find file\n", "3.Show Folder\n", "4.Exit\n"};
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
						user = 3;
					}
					break;
				case 'B':
					user++;
					if(user == 4) {
						user = 0;
					}
					break;
			}
		} else if(user_input == '\n') {
			return user;
		}
	}
	
}

void print_menu(char menu_list[4][20], int user) {
	system("clear");
	for(int i = 0; i < 4; i++) {
		if(i == user) {
			printf("> ");
		}
		printf("%s", menu_list[i]);
	}
}

void add_file(FILE *fp, Node_t *head) {
	Node_t *new = malloc(sizeof(Node_t));
	printf("Enter file's name:");
	scanf("%s", new->data.name);
	printf("Enter file's path:");
	scanf("%s", new->data.path);
	printf("Enter file's size:");
	scanf("%d", &(new->data.size));
	printf("Enter file's creation date:");
	scanf("%d %d %d", new->data.creation_date, new->data.creation_date+1, new->data.creation_date+2);
	printf("Enter file's last modified date:");
	scanf("%d %d %d", new->data.last_modified_date, new->data.last_modified_date+1, new->data.last_modified_date+2);
	int flag;
	printf("Enter file's flag(1-hidden, 2-read-only, 3-system file, 4-executable):"); 
	scanf("%d", &flag);
	new->data.flag = flag;
	new->next = NULL;
	if(head == NULL) {
		head = new;
	} else {
		Node_t *cur = head;
		while(cur->next != NULL) {
			cur = cur->next;
		}
		cur->next = new;
	}
}

void find_file(FILE *fp, Node_t *head) {
	char file[501];
	printf("Enter file's name");
	scanf("%s", file);
	
	Node_t *cur = head;
	Node_t *found = NULL;
	do{
		if(!strcmp(file, strcat(cur->data.path, strcat("/", cur->data.name)))) {
			found = cur;
			break;
		}
	}while(cur->next != NULL);
	
	if(found == NULL) {
		printf("File not found");
	} else {
		printf("Name: %s\n", found->data.name);
		printf("Path: %s\n", found->data.path);
		printf("Size: %d\n", found->data.size);
		printf("Creation date: %d.%d.%d\n", found->data.creation_date[0], found->data.creation_date[1], found->data.creation_date[2]);
		printf("Last modified date: %d.%d.%d\n", found->data.last_modified_date[0], found->data.last_modified_date[1], found->data.last_modified_date[2]);
		print_flag(found->data.flag);
	}
}

void print_flag(File_flag_e flag) {
	switch(flag) {
		case '1':
			printf("Flag: hidden\n");
			break;
		case '2':
			printf("Flag: read-only\n");
			break;
		case '3':
			printf("Flag: system file\n");
			break;
		case '4':
			printf("Flag: executable\n");
			break;
	}
}

void print_dir(FILE *fp, Node_t *head) {
	char dir[400];
	printf("Enter folders's name");
	scanf("%s", dir);
	
	int files = 0;
	int size = 0;
	
	Node_t *cur = head;
	do{
		if(!strcmp(cur->data.path, dir)) {
			files++;
			size += cur->data.size;
		} else {
			size += folder_in_dir(dir, cur->data);
		}
	}while(cur->next != NULL);
	
	printf("Files: %d", files);
	printf("Size: %fGB", (float)size/1024);
}

int folder_in_dir(char* dir, File_t file) {
	if(strstr(file.path, dir)) {
		return file.size;
	} else {
		return 0;
	}
}



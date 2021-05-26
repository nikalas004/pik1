#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getch.c"

typedef enum {
	HIDDEN,
	READ_ONLY,
	SYSTEM_FILE,
	EXECUTABLE,
} File_flag_e;

typedef struct {
	char *name;
	char *path;
	int size;
	int creation_date[3];
	int last_modified_date[3];
	File_flag_e flag;
} File_t;

struct Node_t{
	File_t *data;
	struct Node_t *next;
};
typedef struct Node_t Node_t;   

int menu(void);
void print_menu(char menu_list[4][20], int user);
void add_file(FILE *fp);
void enter_string(char *string);

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

void add_file(FILE *fp) {
	
}

void enter_string(char *string) {
	char user_input;
	int str_size = 1;
	while(user_input != '\n') {
		user_input = getch();
		if(user_input == 127) {
			if(str_size > 1) {
				str_size--;
				string = realloc(string, sizeof(char) * str_size);
				printf("\b \b");
			}
		} else {
			str_size++;
			string = realloc(string, sizeof(char) * str_size);
			*(string+str_size-2) = user_input;
			printf("%c", user_input);
		}
	}
	*(string+str_size-1) = 0;
	printf("%s", string);
}

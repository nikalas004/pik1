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
	char name[50];
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
void add_file(Node_t **head);
void show_file(Node_t **head);
void print_file(File_t file);
void show_dir(Node_t **head);
void read_data(Node_t **head, char filename[100]);
void save_data(Node_t **head, char filename[100]);
void garbage_collector(Node_t **head);
int compare_dirs(char **user_dir, char **file_dir);

int main(int argc, char *argv[]) {
	int user_input = 10;
	Node_t *head = NULL;
	char filename[100] = "files_db.bin";
	void (*func_p[3])(Node_t **head) = {add_file, show_file, show_dir};
	int files = 0;
	
	if(argc > 1) {
		strcpy(filename, argv[1]);	
	}
	
	read_data(&head, filename);
	
	while(user_input != 3) {
		user_input = menu();
		system("clear");
		if(user_input != 3) {
			func_p[user_input](&head);
			printf("Please press any key...");
			getch();
		}
	}
	
	save_data(&head, filename);
	garbage_collector(&head);
	
	return 0;
}

void read_data(Node_t **head, char filename[100]) {
	FILE *fp;
	int files_sum = 0;
	Node_t *new_node;
	
	fp = fopen(filename, "ab+");
	fread(&files_sum, sizeof(int), 1, fp);
	
	for(int i = 1; i <= files_sum; i++) {
		new_node = malloc(sizeof(Node_t));
		fread(new_node->data.name, sizeof(char)*50, 1, fp);
		fread(new_node->data.path, sizeof(char)*500, 1, fp);
		fread(&(new_node->data.size), sizeof(int), 1, fp);
		fread(new_node->data.creation_date, sizeof(int)*3, 1, fp);
		fread(new_node->data.last_modified_date, sizeof(int)*3, 1, fp);
		
		new_node->next = *head;
		*head = new_node;
	}
	
	fclose(fp);
}

void save_data(Node_t **head, char filename[100]) {
	FILE *fp;
	int files_count = 0;
	Node_t *current = *head;
	
	fp = fopen(filename, "wb");
	fseek(fp, sizeof(int), SEEK_SET);
	
	while(current != NULL) {
		fwrite(current->data.name, sizeof(char)*50, 1, fp);
		fwrite(current->data.path, sizeof(char)*500, 1, fp);
		fwrite(&(current->data.size), sizeof(int), 1, fp);
		fwrite(current->data.creation_date, sizeof(int)*3, 1, fp);
		fwrite(current->data.last_modified_date, sizeof(int)*3, 1, fp);
		files_count++;
		
		current = current->next;
	}
	
	fseek(fp, 0, SEEK_SET);
	fwrite(&files_count, sizeof(int), 1, fp);
	fclose(fp);
}

void garbage_collector(Node_t **head) {
	Node_t *current = *head;
	Node_t *fr;
	
	while(current != NULL) {
		fr = current;
		current = current->next;
		free(fr);
	}
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

void add_file(Node_t **head) {
	Node_t *new_node = malloc(sizeof(Node_t));
	char *new_line_pt;
	
	printf("Enter file's name: ");
	fgets(new_node->data.name, 50, stdin);
	new_line_pt = strchr(new_node->data.name, '\n');
	*new_line_pt = 0;
	
	printf("Enter file's path: ");
	fgets(new_node->data.path, 50, stdin);
	new_line_pt = strchr(new_node->data.path, '\n');
	*new_line_pt = 0;
	
	printf("Enter file's size: ");
	scanf("%d", &(new_node->data.size));
	
	printf("Enter file's creation date: ");
	scanf("%d %d %d", new_node->data.creation_date, new_node->data.creation_date+1, new_node->data.creation_date+2);
	
	printf("Enter file's last modified date: ");
	scanf("%d %d %d", new_node->data.last_modified_date, new_node->data.last_modified_date+1, new_node->data.last_modified_date+2);
	
	getc(stdin);
	
	new_node->next = *head;
	*head = new_node;
}

void show_file(Node_t **head) {
	char file_name[50];
	Node_t *current = *head;
	Node_t **found_files = malloc(1);
	int user_input, ff_size = 0;
	int found_flag = 0;
	char *new_line_pt;
	
	printf("Enter file's name: ");
	fgets(file_name, 50, stdin);
	new_line_pt = strchr(file_name, '\n');
	*new_line_pt = 0;
	
	while(current != NULL) {
		if(!strcmp(file_name, current->data.name)) {
			ff_size++;
			found_files = realloc(found_files, sizeof(Node_t*)*ff_size);
			found_files[(ff_size-1)] = current;
			found_flag = 1;
		}
		current = current->next;
	}
	
	if(found_flag) {
		if(ff_size > 1) {
			printf("There are more than one files with that name. Choose one: \n");
			for(int i = 0; i < ff_size; i++) {
				printf("%d. %s/%s\n", i+1, found_files[i]->data.path, found_files[i]->data.name);
			}
			scanf("%d", &user_input);
			getc(stdin);
			
			print_file(found_files[user_input-1]->data);
		} else {
			print_file(found_files[0]->data);
		}
	} else {
		printf("File with that name can't be found!\n");
	}
	
	free(found_files);
}

void print_file(File_t file) {
	printf("------------------------------\n");
	printf("Name: %s\n", file.name);
	printf("Path: %s\n", file.path);
	printf("Size: %dMB\n", file.size);
	printf("Creation date: %d/%d/%d\n", file.creation_date[0], file.creation_date[1], file.creation_date[2]);
	printf("Last modified date: %d/%d/%d\n", file.last_modified_date[0], file.last_modified_date[1], file.last_modified_date[2]);
	printf("------------------------------\n");	
}

void show_dir(Node_t **head) {
	char path[500];
	Node_t *current = *head;
	int files_in_folder = 0;
	long folder_size = 0;
	char *new_line_pt;
	
	printf("Enter dirctory: ");
	fgets(path, 500, stdin);
	new_line_pt = strchr(path, '\n');
	*new_line_pt = 0;
	
	while(current != NULL) {
		char *path_sp = strtok(current->data.path, "/");
		char *dir_sp = strtok(path, "/");
		if(compare_dirs(&dir_sp, &path_sp)) {
			files_in_folder++;
			folder_size += current->data.size;
		}
		current = current->next;
	}
	
	printf("Files in directory: %d\n", files_in_folder);
	printf("Directory size: %ld\n", folder_size);
}

int compare_dirs(char **user_dir, char **file_dir) {
	while(*user_dir != NULL) {
		if(strcmp(*user_dir, *file_dir)) {
			return 0;
		}
		*user_dir = strtok(NULL, "/");
		*file_dir = strtok(NULL, "/");
	}
	return 1;
}

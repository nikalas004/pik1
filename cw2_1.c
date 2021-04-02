#include <stdio.h>
#include <stdlib.h>

void read_bin_file(char *file_name, char *file_name2);
void readfile(char *file_name, char *file_name2);

int main(int argc, char *argv[]) {
	return 0;
}

void readfile(char *file_name, char *file_name2) {	
	FILE * file;
	FILE * f;
	int c;
	char new_line = '\n';
	
	if((file = fopen(file_name, "r")) == NULL) {
		perror("Error opening file");
	}
	if((f = fopen(file_name2, "w")) == NULL) {
		perror("Error opening file");
	}
	
	while((c = fgetc(file)) != EOF) {
		printf("%c", c);
		fwrite(&c, sizeof(char), 1, f);
		if(c != '\n') {
			fwrite(&new_line, sizeof(char), 1, f);
		}
	}

	fclose(file);
	fclose(f);
}

void read_bin_file(char *file_name, char *file_name2) {
	FILE * f;
	int num = 0;
	double num2 = 0.0;
	int len = 0;
	char string[50] = {0};
	char str_indicator = '|'; 
	if((f = fopen(file_name, "rb")) == NULL) {
		perror("Error opening file");
	}
	
	if(fread(&num, sizeof(int), 1, f) != 1) {
		perror("Error reading num");
	}
	if(fread(&num2, sizeof(double), 1, f) != 1) {
		perror("Error reading num2");
	}
	if(fread(&len, sizeof(int), 1, f) != 1) {
		perror("Error reading len");
	}
	if(fread(string, sizeof(char), len, f) != len) {
		perror("Error reading string");
	}
	
	fclose(f);
	if((f = fopen(file_name2, "wb")) == NULL) {
		perror("Error opening file");
	}
	
	if(fwrite(&num, sizeof(int), 1, f) != 1) {
		perror("Error writing num");
	}
	if(fwrite(&num2, sizeof(double), 1, f) != 1) {
		perror("Error writing num2");
	}
	if(fwrite(&str_indicator, sizeof(char), 1, f) != 1) {
		perror("Error reading string");
	}
	if(fwrite(string, sizeof(char), len, f) != len) {
		perror("Error reading string");
	}
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[20];
	int price;
	char country[20];
} Flower;

void inputFlower(Flower *f);
void outputFlower(Flower f);
void searchFlower(Flower *f, int f_size, char *counrty);
void saveData(Flower *f, int f_size);

int main() {
	Flower *arrayOfFlowers;
	int aof_size;
	scanf("%d", &aof_size);
	arrayOfFlowers = malloc(sizeof(Flower)*aof_size);
	for(int i = 0; i < aof_size; i++) {
		inputFlower(arrayOfFlowers+i);
	}
	for(int i = 0; i < aof_size; i++) {
		outputFlower(*(arrayOfFlowers+i));
	}
	searchFlower(arrayOfFlowers, aof_size, "aaa");
	saveData(arrayOfFlowers, aof_size);
	free(arrayOfFlowers);
	return 0;
}

void inputFlower(Flower *f) {
	scanf("%s", f->name);
	scanf("%d", &f->price);
	scanf("%s", f->country);
}

void outputFlower(Flower f) {
	printf("%s\n", f.name);
	printf("%d\n", f.price);
	printf("%s\n", f.country);
}

void searchFlower(Flower *f, int f_size, char *counrty) {
	for(int i = 0; i < f_size; i++) {
		if(!strcmp((f+i)->country, counrty)) {
			outputFlower(*(f+i));
		}
	}
}

void saveData(Flower *f, int f_size) {
	char filename[100];
	scanf("%s", filename);
	FILE *fp = fopen(filename, "wb");
	int str_size;
	
	for(int i = 0; i < f_size; i++) {
		str_size = sizeof((f+i)->name);
		fwrite(&str_size, sizeof(int), 1, fp);
		fwrite((f+++i)->name, sizeof((f+i)->name), 1, fp);
		fwrite(&((f+i)->price), sizeof(int), 1, fp);
		str_size = sizeof((f+i)->country);
		fwrite(&str_size, sizeof(int), 1, fp);
		fwrite((f+i)->country, sizeof((f+i)->country), 1, fp);
	}
	fclose(fp);
}



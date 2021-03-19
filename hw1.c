#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENTS_SIZE 20
#define GRADES_SIZE 5 

typedef struct Student {
	char name[100];
	char fac_num[10];
	char faculty[10];
	char specialty[100];
	char education_type[20];
	int course;
	float grades[GRADES_SIZE];
} Student;

void print_student(Student *students, int *students_size, char *fac_num);
void add_student(Student *students, int *students_size);
void print_all_students(Student *students, int *students_size);
void remove_student(Student *students, int *students_size, char *fac_num);
void avg_grade(Student *students, int *students_size, char *fac_num);
void all_avg_grade(Student *students, int *students_size);

int main() {
	int students_size = 3;
	Student s1 = {"Vankata", "123456789", "FKST", "KSI", "regularly", 1, {3, 5, 3, 3, 4}};
	Student s2 = {"Pesho", "111111111", "FETT", "AE", "regularly", 3, {5, 5, 3, 4, 6}};
	Student s3 = {"Simo", "121212121", "FKST", "KSI", "in absentia", 1, {6, 6, 6, 5, 6}};
	Student students[STUDENTS_SIZE] = {s1, s2, s3};
	int user_input = 0;
	char fac_num[10];
	
	while(user_input != 7) {
		system("clear");
		printf("1. Add student \n2. Print student \n3. Remove student \n4. Print All Students \n5. Average grade of student \n6. Average grade of all students \n7. Exit \nChoose an option: ");
		scanf("%d", &user_input);
		system("clear");
		switch(user_input) {
			case 1:
				add_student(students, &students_size);
				break;
			case 2:
				printf("Enter faculty number: ");
				scanf("%s", fac_num);
				system("clear");
				print_student(students, &students_size, fac_num);
				break;
			case 3:
				printf("Enter faculty number: ");
				scanf("%s", fac_num);
				system("clear");
				remove_student(students, &students_size, fac_num);
				break;
			case 4:
				print_all_students(students, &students_size);
				break;
			case 5:
				printf("Enter faculty number: ");
				scanf("%s", fac_num);
				system("clear");
				avg_grade(students, &students_size, fac_num);
				break;
			case 6:
				all_avg_grade(students, &students_size);
				break;
			case 7:
				break;
			default:
				printf("This option is invalid! Try with another!\n");  
		}
		printf("Press ENTER to continue...\n");
		getchar();
		getchar();
	}
	
	printf("End of program. Bye!\n");
	return 0;
}

void print_student(Student *students, int *students_size, char* fac_num) {
	int student_found_flag = 1;
	for(int i = 0; i < *students_size; i++) {
		if(!strcmp(( *(students+i) ).fac_num, fac_num)) {
			Student student = *(students+i);
			printf(
			"Name: %s \nFaculty number: %s \nFaculty: %s \nSpecialty: %s \nEducation type: %s \nCourse: %d \nGrades: ",
			student.name, 
			student.fac_num, 
			student.faculty, 
			student.specialty, 
			student.education_type, 
			student.course);
			for(int j = 0; j < GRADES_SIZE; j++) {
				printf("%.2f ", student.grades[j]);
			}
			printf("\n");
			student_found_flag = 0;
		}
	}
	
	if(student_found_flag) {
		printf("Student with faculty number %s not found!\n", fac_num);
	}
}

void add_student(Student *students, int *students_size) {
	Student student;
	printf("Enter student's name: ");
	scanf("%s", student.name);
	printf("Enter student's faculty number(9 digits): ");
	scanf("%s", student.fac_num);
	printf("Enter student's faculty: ");
	scanf("%s", student.faculty);
	printf("Enter student's specialty: ");
	scanf("%s", student.specialty);
	printf("Enter student's education_type: ");
	scanf("%s", student.education_type);
	printf("Enter student's course: ");
	scanf("%d", &(student.course));
	printf("Enter student's grades(%d): \n", GRADES_SIZE);
	for(int i = 0; i < GRADES_SIZE; i++) {
		printf("Grade %d: ", i+1);
		scanf("%f", &(student.grades[i]));
	}
	*( students + ( (*students_size)++ ) ) = student;
	printf("Student with facluty number %s was added!\n", student.fac_num);
}

void print_all_students(Student *students, int *students_size) {
	for(int i = 0; i < *students_size; i++) {
		printf("=====================================================\n");
		print_student(students, students_size, (*(students+i)).fac_num);
	}
	printf("=====================================================\n");
}

void remove_student(Student *students, int *students_size, char *fac_num) {
	int student_found_flag = 1;
	for(int i = 0; i < *students_size; i++) {
		if(!strcmp(( *(students+i) ).fac_num, fac_num)) {
			for(int j = i; j < (*students_size)-1; j++) {
				*(students+j) = *(students+j+1);
			}
			student_found_flag = 0;
			break;
		}
	}
	
	if(student_found_flag) {
		printf("Student with faculty number %s not found!\n", fac_num);
	} else {
		(*students_size)--;
		printf("Student with faculty number %s was deleted!\n", fac_num);
	}
}

void avg_grade(Student *students, int *students_size, char *fac_num) {
	int student_found_flag = 1;
	float avg = 0;
	
	for(int i = 0; i < *students_size; i++) {
		if(!strcmp(( *(students+i) ).fac_num, fac_num)) {
			Student student = *(students+i);
			for(int j = 0; j < GRADES_SIZE; j++) {
				avg += student.grades[j];
			}
			student_found_flag = 0;
		}
	}
	
	if(student_found_flag) {
		printf("Student with faculty number %s not found!\n", fac_num);
	} else {
		printf("The average grade of the student with faculty number %s is %.2f!\n", fac_num, avg / GRADES_SIZE);
	}
}

void all_avg_grade(Student *students, int *students_size) {
	float avg = 0;
	for(int i = 0; i < *students_size; i++) {			
		Student student = *(students+i);
		for(int j = 0; j < GRADES_SIZE; j++) {
			avg += student.grades[j];
		}
	}
	
	printf("The average grade of all students is %.2f!\n", avg / (GRADES_SIZE * (*students_size)));
}


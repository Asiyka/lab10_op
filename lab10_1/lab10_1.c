#define _CRT_SECURE_NO_WARNINGS

#define STRLEN 100

#define NUMBER_OF_MARKS 5
#define NUMBER_WITH_MIN 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//створюємо структуру студент
struct Sstudent {
		char surname[STRLEN];
		char name[STRLEN];
		//створюємо структуру день народження
		struct Sbirthday {
			int day;
			int month;
			int year;
		}student_birthday;
		int marks[NUMBER_OF_MARKS];
		double avrg_mark;
	//створюємо вказівник на наступний елемент списку
	struct Sstudent *next;
};

struct Sstudent* create_list_from_file(FILE* file, int number_of_students) {
	//зчитуємо з файла нового студента і передаємо ці значення в карент стюдент

	struct Sstudent* start_of_list = NULL;
	char* adres_of_cut_elem;
	char str[STRLEN];
	struct Sstudent* new_student = (struct Sstudent*)malloc(sizeof(struct Sstudent));
	while (!feof(file)) {
		//зберігаємо адресу початку списка
		if (start_of_list == NULL) {
			start_of_list = new_student;
		}

		fgets(str, STRLEN, file);
		adres_of_cut_elem = strtok(str, "\t");
		strcpy(new_student->surname, adres_of_cut_elem);
		adres_of_cut_elem = strtok(NULL, "\t");
		strcpy(new_student->name, adres_of_cut_elem);
		adres_of_cut_elem = strtok(NULL, "\t");
		new_student->student_birthday.day = (int)strtol(adres_of_cut_elem, &adres_of_cut_elem, 10);
		new_student->student_birthday.month = (int)strtol(adres_of_cut_elem + 1, &adres_of_cut_elem, 10);
		new_student->student_birthday.year = (int)strtol(adres_of_cut_elem + 1, &adres_of_cut_elem, 10);
		for (int i = 0; i < 5; i++)
		{
			adres_of_cut_elem = strtok(NULL, "\t");
			new_student->marks[i] = atoi(adres_of_cut_elem);
		}
		new_student->next = NULL;
		struct Sstudent* next_student = (struct Sstudent*)malloc(sizeof(struct Sstudent));
		next_student->next = NULL;
		if (number_of_students-1) {
			new_student->next = next_student;

		}
		new_student = next_student;
		
		number_of_students--;
	}

		return start_of_list;

}

void output_list(struct Sstudent* start_of_list) {
	FILE* file = fopen("output.txt", "w");
	if (start_of_list) {
		printf("Surname      \t\t Name\t\t   Date of birth\tExamination marks\n");
		fprintf(file, "Surname      \t\t Name\t\t   Date of birth\tExamination marks\n");
		printf("------------------------------------------------------------------------\n");
		fprintf(file, "------------------------------------------------------------------------\n");
		struct Sstudent* output_s = NULL;
		int i = 1;
		for( output_s = start_of_list; output_s != NULL; i++)
		{
			printf("%-2d| ", i);
			printf("%-20s ", output_s->surname);
			printf("%-20s", output_s->name); 
			printf("%2d.", output_s->student_birthday.day);
			printf("%d.", output_s->student_birthday.month);
			printf("%4d\t\t", output_s->student_birthday.year);
			for (int j = 0; j < 5; j++) {
				printf("%-1d ", output_s->marks[j]);
			}
			printf("\n");
			output_s = output_s->next;
		}

	}
	else {
		printf("List is empty");
	}
	printf("\n");

}

void swap(struct Sstudent* first_student, struct Sstudent* second_student) {
	struct Sstudent* tmp = second_student->next;
	first_student->next = tmp;
	second_student->next = first_student;
}
struct Sstudent* sort(struct Sstudent* start_of_list, int number_of_students) {
	struct Sstudent* first_student = start_of_list;
	struct Sstudent* second_student = start_of_list->next;
	struct Sstudent* new_start_of_list = start_of_list;
	struct Sstudent* prew_student = new_start_of_list;

	int j = 0;
	for(first_student = start_of_list; j < number_of_students; first_student = new_start_of_list, second_student = first_student->next, prew_student = new_start_of_list, j++){
	int i = 0;
	while (second_student != NULL) {

		if (strcmp(first_student->surname, second_student->surname) < 0) 
		{
			if (i == 0) 
			{
				new_start_of_list = second_student;
				prew_student = new_start_of_list;
				swap(first_student, second_student);
				second_student = first_student->next;
				i++;
			}
			else 
			{
				swap(first_student, second_student);
				prew_student->next = second_student;
				prew_student = second_student;
				second_student = first_student->next;
			}

		}
		else 
		{
			first_student = first_student->next;
			second_student = first_student->next;

			if (i) {
				prew_student = prew_student->next;
			}
		}
		i++;
	}
	}
	
	return new_start_of_list;
}

void search_min(struct Sstudent* start_of_list, int** arr, int number_of_students) {
	struct Sstudent* curent_student = start_of_list;
	while (curent_student != NULL){
		double avrg = 0;
		for (int i = 0; i < NUMBER_OF_MARKS; i++) {
			avrg += curent_student->marks[i];
		}
		curent_student->avrg_mark = avrg / NUMBER_OF_MARKS;
	curent_student = curent_student->next;
	}
	struct Sstudent* first_student = start_of_list;
	for (int i = 0; i < 5 && first_student!=NULL; i++) {


		double min = 5;//5-ти бальна система оцінювання
		curent_student = start_of_list;
		for (int j = 0; curent_student != NULL; j++) {
			if (curent_student->avrg_mark < min) {
				int flag = 1;
				for (int k = 0; k < 5; k++) {
					if (arr[k] == curent_student) {
						flag = 0;
					}
				}
				if (flag) {
					arr[i] = curent_student;
					min = curent_student->avrg_mark;
				}
			}
			curent_student = curent_student->next;
		}
	}

}
		
struct Sstudent* insert_student(struct Sstudent* start_of_list) {
	struct Sstudent* inserted_student = (struct Sstudent*)malloc(sizeof(struct Sstudent));
	struct Sstudent* new_start_of_list = start_of_list;

	printf("Plese enter SURNAME of student:\n");
	scanf("%s", inserted_student->surname);
	printf("Plese enter NAME of student:\n");
	scanf("%s", inserted_student->name);
	printf("Plese enter DAY of student birthday:\n");
	scanf("%d", &inserted_student->student_birthday.day);
	printf("Plese enter MONTH of student birthday:\n");
	scanf("%d", &inserted_student->student_birthday.month);
	printf("Plese enter YEAR of student birthday:\n");
	scanf("%d", &inserted_student->student_birthday.year);
	for (int i = 0; i < NUMBER_OF_MARKS; i++) {
		printf("Plese enter %d MARK of student:\n", i+1);
		scanf("%d", &inserted_student->marks[i]);
	}

	if (strcmp(inserted_student->surname, start_of_list->surname) > 0) {
	new_start_of_list = inserted_student;
	inserted_student->next = start_of_list;
	}

	struct Sstudent* prew_student = new_start_of_list;
	struct Sstudent* next_student = new_start_of_list->next;

	for (prew_student = start_of_list, next_student = start_of_list->next; next_student != NULL; prew_student = prew_student->next, next_student = next_student->next) {
		if (strcmp(inserted_student->surname, prew_student->surname) < 0 && strcmp(inserted_student->surname, next_student->surname) > 0) {
			prew_student->next = inserted_student;
			inserted_student->next = next_student;
		}
	}


	if (strcmp(inserted_student->surname, prew_student->surname) < 0) {
		prew_student->next = inserted_student;
		inserted_student->next = NULL;
	}

	return new_start_of_list;
}

struct Sstudent* delet_students(struct Sstudent* start_of_list, int number_of_students, int* number_of_deleted_students) {
	struct Sstudent* curent_student = start_of_list;
	struct Sstudent* prew_student = NULL;
	struct Sstudent* next_student = start_of_list->next;
	struct Sstudent* new_start_of_list = start_of_list;

	for (int j = 0; j < number_of_students; j++) {
		if (prew_student == NULL) {
			int flag = 1;
			for (int i = 0; i < NUMBER_OF_MARKS; i++) {
				if (curent_student->marks[i] == 2) {
					
					flag = 0;
					(*number_of_deleted_students)++;
					if (j == number_of_students - 1 && flag == 0) {
						new_start_of_list = NULL;
					}
					else if (j == number_of_students - 1 && flag == 1) {
						curent_student->next = NULL;
					}
					else {
					new_start_of_list = next_student;
					curent_student = new_start_of_list;
					next_student = curent_student->next;
					}

					break;
				}
			}
			if (flag) {
				prew_student = curent_student;
				curent_student = curent_student->next;
				if (curent_student) {
					next_student = curent_student->next;
				}
			}
			
			continue;
		}
		else if (next_student != NULL) {
			int flag = 1;
			for (int i = 0; i < NUMBER_OF_MARKS; i++) {
				if (curent_student->marks[i] == 2) {
					prew_student->next = next_student;
					curent_student = curent_student->next;
					next_student = curent_student->next;
					flag = 0;
					(*number_of_deleted_students)++;
					break;
				}
			}
			if (flag) {
				prew_student = curent_student;
				curent_student = curent_student->next;
				next_student = curent_student->next;
			}
			continue;
		}
		else if (next_student == NULL) {
			for (int i = 0; i < NUMBER_OF_MARKS; i++) {
				if (curent_student->marks[i] == 2) {
					prew_student->next = NULL;
					(*number_of_deleted_students)++;
					break;
				}
			}
		}
	}

	return new_start_of_list;
}



int main() {
	int number_of_students = 0;



	FILE* file;
	file = fopen("students.txt", "r");
	char str_numb[STRLEN];
	int size;
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);
	while (!feof(file)) {
		fgets(str_numb, STRLEN, file);
		number_of_students++;
	}
	if (size == 0) {
		printf("File is EMPTY");
		return;
	}
	fclose(file);

	file = fopen("students.txt", "r");

	printf("List of students from file\n\n");

	struct Sstudent* start_of_list = create_list_from_file(file,number_of_students);
	output_list(start_of_list);
	fclose(file);

	if (number_of_students != 1) {
		printf("List of students after sorting\n\n");
		start_of_list = sort(start_of_list, number_of_students);
		output_list(start_of_list);
		printf("\n");
	}

	if (number_of_students >= 5) {
		printf("5 students with minimal avarage mark\n\n");
	}
	else {
		printf("%d students with minimal avarage mark\n\n", number_of_students);
	}
	//створюємо масив вказівників на адреси мінімальних студентів
	int** arr = (int**)malloc(NUMBER_WITH_MIN * sizeof(int*));
	for (int i = 0; i < 5; i++) {
		arr[i] = 0;
	}
	search_min(start_of_list, arr, number_of_students);

	int i = 1;
	struct Sstudent* output_s = arr[0];
	while(output_s && i<=5) {
			printf("%-2d| ", i);
			printf("%-20s ", output_s->surname);
			printf("%-20s", output_s->name);
			printf("%2d.", output_s->student_birthday.day);
			printf("%d.", output_s->student_birthday.month);
			printf("%4d\t\t", output_s->student_birthday.year);
			for (int j = 0; j < 5; j++) {
				printf("%-1d ", output_s->marks[j]);
			}
			printf("\t%-6lf", output_s->avrg_mark);
			printf("\n");

			output_s = arr[i];
			i++;

	}
	printf("\n");


	int added_students = 0;
	int n = 0;
	do{
		printf("Do you want to add new student? 1 - yes 0 - no\n");
		scanf("%d", &n);
		if (n) {
			start_of_list = insert_student(start_of_list);
			number_of_students++;
			added_students++;
			
		}
	}while(n);
	if (added_students) {
		if (added_students == 1) {
			printf("%d student was added\n\n", added_students);
		}
		else {
			printf("%d students were added\n\n", added_students);
		}
		printf("Look of list after adding students\n\n");
		output_list(start_of_list);
	}
	else {
		printf("No students were added\n\n");
	}
	int number_of_deleted_students = 0;
	start_of_list = delet_students(start_of_list, number_of_students, &number_of_deleted_students);
	if (number_of_deleted_students) {
		if (number_of_deleted_students == 1) {
			printf("%d student was deleted\n\n", number_of_deleted_students);
		}
		else{
			printf("%d students were deleted\n\n", number_of_deleted_students);
		}
		if (number_of_students != number_of_deleted_students) {
			printf("Look of list after deleting students\n\n");
		}
		output_list(start_of_list);

		FILE* file = fopen("output.txt", "w");
		if (start_of_list) {
			printf("Surname      \t\t Name\t\t   Date of birth\tExamination marks\n");
			fprintf(file, "Surname      \t\t Name\t\t   Date of birth\tExamination marks\n");
			printf("------------------------------------------------------------------------\n");
			fprintf(file, "------------------------------------------------------------------------\n");
			struct Sstudent* output_s = NULL;
			int i = 1;
			for (output_s = start_of_list; output_s != NULL; i++)
			{
		fprintf(file, "%-2d| ", i);
		fprintf(file, "%-20s ", output_s->surname);
		fprintf(file, "%-20s", output_s->name);
		fprintf(file, "%2d.", output_s->student_birthday.day);
		fprintf(file, "%d.", output_s->student_birthday.month);
		fprintf(file, "%4d\t\t", output_s->student_birthday.year);
		for (int j = 0; j < 5; j++) {
			fprintf(file, "%-1d ", output_s->marks[j]);
		}
		fprintf(file, "\n");
		output_s = output_s->next;
			}

		}
		else {
			printf("List is empty");
		}
		printf("\n");
	}
	else {
		printf("No students were deleted");
	}



	return 0;
}
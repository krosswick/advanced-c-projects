//NAME: Kyle Rosswick
//CLASS: CS 2050
//PAWPRINT: klrmt5
//HOMEWORK: 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MODEL 25
#define MAX_LINE 50

typedef struct Car{
	char *model;
	char *color;
	int year;
	struct Car* next;
} car;

car* read_from_file(FILE*);
car* insert_in_sorted_order(car*, char*, char*, int);
car* create_car(char*, char*, int);
void print_cars(car*);
int update_car(car*, char*, int);
int search(car*, char*);
char* verify_color(FILE*, char*);
car* remove_car(car*, char* );

int main(int argc, char **argv){

	int year = 0;
	char choice;
	char model[MAX_MODEL];
	char color[MAX_LINE];
	car *start = NULL;

	if(argc != 3){
		printf("\n\nIncorrect number of command line arguments. Exiting...\n\n");
		exit(0);
	}

	char *input = argv[1];
	char *input2 = argv[2];

	FILE *fPtr = fopen(input, "r");

		if(fPtr == NULL){
			printf("\n\nPointer is null. Exiting...\n\n");
			exit(0);
		}

	FILE *cPtr = fopen(input2, "r");

		if(cPtr == NULL){
			printf("\n\nPointer is null. Exiting...\n\n");
			exit(0);
		}


	//car *start = NULL;

	start = read_from_file(fPtr);
	
	print_cars(start);

	printf("\n\nWhat would you like to do?  A)dd car // C)hange a car // D)elete a car // Q)uit program: ");

	scanf("%c", &choice);

//	getchar();	

	switch(choice){

	case 'A':
	case 'a':

		getchar();

		printf("\nEnter a model name to ADD: ");

		fgets(model, sizeof color, stdin);

		if(search(start, model) == 1){

			printf("\nThat model already exists. Try again:");
		}

		else{

			printf("\nEnter model year:");

			scanf("%d", &year);

			getchar();

			printf("\nEnter a color:");

			fgets(color, sizeof color, stdin);

			strtok(input, "\n");

			getchar();

			strcpy(color, verify_color(fPtr, color));

			while(strcmp(color, "NO") == 0){
	
				printf("\nPlease enter a valid color:");

				fgets(color, sizeof color, stdin);

				getchar();

				strcpy(color, verify_color(cPtr, color));

			}

			start = insert_in_sorted_order(start, model, color, year);

			print_cars(start);

			getchar();
		}
break;

	case 'C':
	case 'c':

			printf("\nEnter a model name to CHANGE:");
			
			fgets(model, sizeof model, stdin);

			strtok(input, "\n");

			getchar();

			while(search(start, model) == 0){

				printf("\nThat model already exists, try again:");
		
				fgets(model, sizeof model, stdin);

				getchar();
			}

			printf("\nEnter the year of the model:");
	
			scanf("%d", &year);

			while(year > 2017){

				printf("\nThat car is from the future. Choose a year that is 2017 or less:");

				scanf("%d", &year);
				
				getchar();
			}

			update_car(start, model, year);
			
			print_cars(start);

			getchar();
break;

	case 'D':
	case 'd':

			printf("\nEnter a model to DELETE: ");

			fgets(model, sizeof model, stdin);

			strtok(input, "\n");

			getchar();

			while(search(start, model) == 0){

				printf("\nThat model does not exist. Trt again:");

				fgets(model, sizeof model, stdin);
			
				getchar();
			}

			start = remove_car(start, model);

			print_cars(start);
break;

	case 'Q':
	case 'q':

			printf("\nExiting...\n");
			exit(0);

			free(model);
			free(color);
break;

	}

	free(start);

	fclose(fPtr);

	fclose(cPtr);	

	return 0;
}

car* read_from_file(FILE *fPtr)
{
	char vehicle[MAX_LINE];
	char *model;
	char *color;
	int year;
	char *pipe = "|";

	car* start = NULL;

	while(fgets(vehicle, MAX_LINE, fPtr)){

		model = strtok(vehicle, pipe);
		color = strtok(NULL, pipe);
		year = atoi(strtok(NULL, pipe));

		start = insert_in_sorted_order(start, model, color, year);

	}	

	return start;
}

car* insert_in_sorted_order(car *start, char *model, char *color, int year)
{
	if(start == NULL){
		start = create_car(model, color, year);
	}

	else{
		car *newCar = create_car(model, color, year);
		car *crnt = start;
		car *prev = NULL;
	
			while(crnt != NULL && strcmp(newCar->model, crnt->model) > 0){
				prev = crnt;
				crnt = crnt->next;
			}

			if(prev == NULL){
				newCar->next = start;
				return newCar;			
			}

			else{
				newCar->next = crnt;
				prev->next = newCar;
			}
			
	}
		
	
	return start;
	
}

car* create_car(char *model, char *color, int year)
{
	car *newCar = malloc(sizeof(car));
	newCar->model = malloc(sizeof(char)*MAX_MODEL);
	newCar->color = malloc(sizeof(char)*MAX_MODEL);

	strcpy(newCar->model, model);
	strcpy(newCar->color, color);
	newCar->year = year;
	newCar->next = NULL;

	return newCar;	
}

void print_cars(car *start)
{
	printf("\n\nThe list of the cars in the inventory are:\n");

	while(start == NULL){
		printf("\n\nHead of list is null...Exiting...\n");
		exit(0);
	}

	while(start != NULL){
		printf("%d %s %s\n", start->year, start->model, start->color);
		start=start->next;
	}
}

int update_car(car *start, char *targetModel, int year)
{
	car *up = start;

	while(up != NULL){

		if(strcmp(up->model, targetModel) == 0){
			return 1;

			up->year = year;
			
		}
		
		up = up->next;
	}

	return -1;
		


}

int search(car *start, char *model)
{
	car *ptr;

	ptr = start;

	while(ptr != NULL){

		if(strcmp(ptr->model, model) == 0){

			return 1;

			ptr = ptr->next;
		}
	}

	return 0;
}

car* remove_car(car *start, char *targetModel)
{
	car *curr = start;
	car *prev = NULL;

	if(start == NULL){

		return NULL;
	}

	while(curr != NULL){

		if(strcmp(curr->model, targetModel) == 0){
			
			break;
		}

	prev = curr;

	curr = curr->next;

	}

	if(curr != NULL){

		if(prev == NULL){

			start = curr->next;

		}

		else{

			prev->next = curr->next;
		}

	free(curr);	

	}

	return start;

}

char* verify_color(FILE *cPtr, char *color)
{
	char fcolor[MAX_LINE];

	while(1){

		fseek(cPtr, 0, 0);

			while(fgets(color, MAX_LINE, cPtr)){

				fscanf(cPtr, "%s", fcolor);

					if(strcmp(fcolor, color) == 0){

						return color;

					}	

			}

		while(strcmp (color, "NO") == 0){

			printf("\nPlease enter a valid color");
			
			fgets(color, sizeof color, stdin);

			getchar();

			strcpy(color, verify_color(cPtr, color));
		}

		fseek(cPtr, 0, 0);

		while(fgets(color, MAX_LINE, cPtr)){
			
			fscanf(cPtr, "%s", fcolor);

			printf("%s", color);
		}

	printf("\nEnter a color:");

	scanf("%s", color);

	}
	

	rewind(cPtr);
}

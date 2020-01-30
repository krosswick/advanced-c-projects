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

	if(argc != 3){
		printf("\n\nIncorrect number of command line arguments. Exiting...\n\n");
		exit(0);
	}

	char *input = argv[1];
	char *input2 = argv[2];

	char choice;
//	int year = 0;

	FILE *fPtr = fopen(input, "r");

		if(fPtr == NULL){
			printf("\n\nPointer is null. Exiting...\n\n");
			exit(0);
		}

	FILE *fPtr2 = fopen(input2, "r");

		if(fPtr2 == NULL){
			printf("\n\nPointer is null. Exiting...\n\n");
			exit(0);
		}


	car *start = NULL;

//	char model[MAX_LINE];
//	char color[MAX_MODEL];

	start = read_from_file(fPtr);
	
	print_cars(start);

	printf("\n\nWhat would you like to do?  A)dd car // C)hange a car // D)elete a car // Q)uit program: ");

	scanf("%c", &choice);

/*	getchar();

	while(choice != 'Q'){

		if(choice == 'A'){

			printf("Enter a MODEL name to add\n");
			fgets(model, sizeof model, stdin);
		
			if(search(start, model) == 1){
		
				printf("\nThis car is already in the list, try again:");
			}

			else{
				printf("Enter a model year\n");

				scanf("%d", &year);

				getchar();

				printf("\nEnter a color:");

				fgets(color, sizeof color, stdin);

				getchar();

				strcpy(color, verify_color(fPtr, color));

					while(strcmp(color, "NO") == 0){

						printf("Enter a valid color.\n");
						fgets(color, sizeof color, stdin);

						getchar();
	
						strcpy(color, verify_color(fPtr2, color));
					}

				start = insert_in_sorted_order(start, model, color, year);
				
				print_cars(start);
				
				getchar();
			}
		}

		else if(choice == 'C'){

			printf("\nEnter a MODEL to change: ");
			
			fgets(model, sizeof model, stdin);

			getchar();

				while(search(start, model) == 0){

					printf("\nThat model does not exist, enter one that does:");

					fgets(model, sizeof model, stdin);

					getchar();
				}

			printf("\nEnter the model year: ");

			scanf("%d", &year);

			getchar();

				while(year > 2017){
	
					printf("\nThat car is from the future. Please enter a year that has happened: ");
			
					scanf("%d", &year);

					getchar();
				}

			update_car(start, model, year);

			print_cars(start);

			getchar();
		}

		else if(choice == 'D'){

			printf("\nEnter a MODEL name to delete: ");

			fgets(model, sizeof model, stdin);

			getchar();

				while(search(start, model) == 0){

					printf("\nIf you delete something that does not exist, the universe will blow up. Enter a car that exists: ");
	
					fgets(model, sizeof model, stdin);
				}

			start = remove_car(start, model);

			print_cars(start);
		}

		else if(choice == 'Q'){

			printf("\nExiting...");
		
			exit(0);
		}

			else{
				printf("\nInvalid choice. Enter A, C, D, or Q: ");
			}
	}*/			

	free(start);

	fclose(fPtr);

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
			up->year = year;
			return 1;
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

			ptr = ptr->next;

			return 1;
		}
	}

	return 1;
}

/*char* verify_color(FILE *fPtr2, char *color)
{
	char fcolor[MAX_LINE];

	while(1){

	fseek(fPtr2, 0, 0);

		while(!feof(fPtr2)){

			fscanf(fPtr2, "%s", fcolor);
	
				if(strcmp(fcolor, color) == 0){

					return color;
				}
			
		}

	printf("\nInvalid color! Choose from list of valid colors:");

	fseek(fPtr2, 0, 0);

	while(!feof(fPtr2)){

		fscanf(fPtr2, "%s", fcolor);

		printf("%s", color);
	}	

	printf("\nEnter a color:");

	scanf("%s", color);

	}
}*/

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

//NAME: Kyle Rosswick
//PAWPRINT: klrmt5
//CLASS: CS2050
//LAB #2

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct data{

	int x;
	int y;
}Data;

struct data* read_data(char*, int);

void divide_numbers(struct data*, int);

struct data* sort(struct data*, int);

void print_data(struct data*, int);

double distance(struct data*, struct data*);

int main(int argc, char *argv[])
{
	if(argc != 3){
		printf("\nIncorrect number of command line arguments.\n");
		exit(0);
	}

	int size = atoi(argv[1]);

	//printf("\nEnter 5 sets of points(x , y):\n");

	Data *set = read_data(argv[2], size); 

	//divide_numbers(set, size);
	
	set = sort(set, size);

	print_data(set, size);

	free(set);

	return 0;
}

Data* read_data(char *fn, int size)
{
	FILE *fPtr = fopen(fn, "r");
	int i;

	if(fPtr == NULL){
		printf("\nError: Can not open file.");
	}

	Data *set = malloc(sizeof(Data)*size);

	for(i=0; i<size; i++){
		fscanf(fPtr, "%d %d", &(set + i)->x , &(set + i)->y);
	}

	fclose(fPtr);

	return set;
}

/*void divide_numbers(struct data *set, int size)
{
	int i;
	float num = 0;

	for(i=0; i<size; i++){
		num = (set + i)->x / (set + i)->y;
		printf("\n%d divided by %d divided is: %f\n", (set + i)->x, (set + i)->y, num);
	}
}*/

Data* sort(struct data *set, int size)
{
	int i;
	int j;
	int temp;
	Data *origin = malloc(sizeof(Data));
		origin->x = 0;
		origin->y = 0;

	for(i=0; i<size; i++){
		for(j=0; j<size -1; j++){
			if( distance ( (set + j), origin ) > distance( (set + j + 1), origin ) ){

				temp = (set + j)->x;
				(set + j)->x = (set + j + 1)->x;
				(set + j + 1)->x = temp;

				temp = (set + j)->y;
				(set + j)->y = (set + j + 1)->y;
				(set + j + 1)->y = temp;
			}
		}
	}

	free(origin);

	return set;
}

void print_data(struct data *set, int size)
{
	int i;

	printf("\n\nPoints sorted based on the distance from the origin:\n");

	for(i=0; i<size; i++){
		printf("\n(%d,%d)\n\n", (set + i)->x, (set + i)->y);
	}

}

double distance(struct data *first, struct data *second)
{
	double dist = 0;

	dist = sqrt(pow(((first->x) - (second->x)) , 2) + (pow(((first->y) - (second->y)) , 2)));

	return dist;
}

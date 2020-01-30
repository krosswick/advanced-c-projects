//NAME: Kyle Rosswick
//PAWPRINT: klrmt5
//CS 2050
//LAB: 1
#include <stdio.h>
#include <stdlib.h>

#define MAXNAME 10

int read_info(char*, int*, char**, float*);
void print_array(int*, char**, float*, int);
//int maxGPA(float*, int);
float avgGPA(float*, int);

int main(int argc, char*argv[])
{

	if(argc != 2){
		printf("\nIncorrect number of command line arguments.\nCorrect useage: ./a.out <input_file.txt>\n");
		return 0;
	}
	
	char *input = argv[1];
	int size = 0;
		FILE *fPtr = fopen(input, "r");
			if(fPtr == NULL){
				printf("\n Can not open file.\n");
				return 0;
			}
		fscanf(fPtr, "%d", &size);
		fclose(fPtr);
	
	int *data = malloc(sizeof(int)*size);
	char **name = malloc(sizeof(char*)*size);

	int i;
	for(i=0; i<size; i++){
		*(name + i) = malloc(sizeof(char) * MAXNAME);
	}

	float *gpa = malloc(sizeof(float)*size);

	size = read_info(input, data, name, gpa);	
		if(size == -1){
			printf("\nFile can not be opened.\n");
			return 0;
		}

	print_array(data, name, gpa, size);

	float avg = avgGPA(gpa, size);
	printf("The average GPA is %.2f\n", avg);

	//int max = maxGPA(gpa, size);
	//printf("The student with the highest GPA is !Murphy! !Student ID 689876! and GPA %.2f\n", *(gpa + max));

	free(data);
	free(gpa);
	for(i=0; i <size; i++){
		free(*(name + i));
	}
	free(name);

	return 0;
}


int read_info(char *inputFile, int *data, char **name, float *gpa)
{
	FILE *fPtr = NULL;
	fPtr = fopen(inputFile, "r");
	int i;
	int size;
	
	if(fPtr == NULL){
		printf("\nFile can not be opened.\n");
		return -1;
	}

	fscanf(fPtr, "%d", &size);

	for(i=0; i<size; i++){
		fscanf(fPtr, "%s %d %f", *(name + i), (data + i), (gpa + i));
		//printf("%d at %p\n", *(data + i), (data + i));
	}


	fclose(fPtr);

	return size;
}

void print_array(int *ptr, char **name, float *gpa, int size)
{
	int i;
	
	printf("NAME     ID      GPA\n");
	for(i=0; i<size; i++){
		printf("%s\t %d   %.2f\n", *(name + i), *(ptr + i), *(gpa + i));
	}

	printf("\n");

	return;
}

float avgGPA(float *gpa, int size)
{
	float avg = 0;
	float sum = 0;
	int i;

	for(i=0; i<size; i++){
		sum = sum + *(gpa + i);
		avg = sum / size;
	}

	return avg;
}

/*int maxGPA(float *gpa, int size)
{
	int i;
	float *large;

	for(i=0; i<size; i++){

		if(large < *(gpa + i)){
			*(large + i) = *(gpa + i);
		}
	}

	return *(large + i);
}*/

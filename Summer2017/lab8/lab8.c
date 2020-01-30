//NAME: Kyle Rosswick
//CLASS: CS2050
//PAWPRINT: klrmt5
//LAB: 8
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 300
static int valid = 0;
static int invalid = 0;
void readToken(FILE *fPtr);
void checkTime(char*);

int main(int argc, char *argv[])
{
	if(argc != 2){
		printf("\n\nIncorrect number of command line arguments. Format should be: ./a.out <filename>");
		exit(0);
	}

	FILE *fPtr = fopen(argv[1], "r");

	readToken(fPtr);

	printf("\nThere were %d tokens in the file.", (valid + invalid));

	printf("\nThere were %d valid tokens in the file.", valid);

	return 0;	

}

void readToken(FILE *fPtr)
{
	char *token;

	const size_t line_size = 300;

	token = malloc(line_size);

	while(fgets(token, line_size, fPtr) != NULL){
		
		checkTime(token);
	}
	
}

void checkTime(char *token)
{
	char *temp;
	char buf1[10];
	char buf2[10];
	char copy[30];
	int count = 0;

	strcpy(copy, token);
	temp = strtok(token, ":");
	
	if(strlen(copy) < 9){

		while(temp != NULL && count < 2){

			if(count == 0){
				strcpy(buf1, temp);
			}
		
			if(count == 1){
				strcpy(buf2, temp);
			}

			temp = strtok(NULL, token);

			count++;
		}

		if(strlen(buf1) == 2 && strlen (buf2) == 5){

			if(atoi(buf1) > 0 && atoi(buf1) < 13){
				

				if((buf2[3] == 'm' || buf2[3] == 'M') && (((buf2[2] == 'a') || buf2[2] == 'A') || ((buf2[2] == 'p') || buf2[2] == 'P'))){
					
					char t1[3];
					
					t1[0] = buf2[0];

					t1[1] = buf2[1];

					t1[3] = '\0';

				if(atoi(t1) > 0 && atoi(t1) <= 60){

					printf("\n%s\n", copy);
					valid++;
				}

				else{
					invalid++;
				}
				}

				else{
					invalid++;
				}
			}

			else{
				invalid++;
			}
		}

		else{
			invalid++;
		}
	}

	else{
		invalid++;
	}				
}

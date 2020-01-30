//NAME: Kyle Rosswick
//PAWPRINT: klrmt5
//LAB: 8
//CLASS: CS2050
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool isATime(char*);
bool isADate(char*);
bool isAPhone(char*);

int main(int argc, char argv[])
{
	if(argc != 2){
		printf("\nIncorect number of commandline arguments.");
		exit(1);
	}

	FILE *fPtr = fopen();

	char line[20];

	while(fgets(line, 20, fPtr)){

		bool check = false;

		check = isATime(line);

		if(check == true){
			//printf("\nTime is %s", time);
			count++
		}
	
		check = isADate(line);
	
		if(check == true){
			//print
			count++
		}

		check = isAPhone(line);

		if(check == true){
			//printf
			count++
		}

	}

	fclose(fPtr);
}

bool isAPhone(char *word)
{
	bool check;	

	char temp[12];

	strcpy(temp, word);
	temp = strtok(word, "-");

	if(isdigit(temp)){
		if(temp[4] = "-"){
			if(temp[8] = "="){
				return true;
			}
		}
	}


	return false;
}

bool isATime(char *word)
{
	char copy[20];
	strcpy(copy, word);

	char *token = strtok(cpoy, ":");

	int hour = atoi(token);

	if(hour < 1 || hour > 12){

		return false;
	}

	if(copy[])



}

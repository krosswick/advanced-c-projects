//NAME: Kyle Rosswick
//CLASS: CS2050
//LAB: #3
//PAWPRINT: klrmt5

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void collatzDriver();
void collatz(int);
void hexConverterDriver();
int hexConverter(int);
//int factorial(int);
//int costFunction(int);

int main(void)
{
	int choice;

	printf("\n\nPick an option by entering its number:\ncollatz driver(1)\nhexConverter(2)\nExit(3)\nEnter your choice:");
	scanf("%d", &choice);

	while(choice < 1 || choice > 3){
		printf("\nPlease choose option 1, 2 , or 3:");
		scanf("%d", &choice);
	}//error checking user input to make sure they stay in the paramaters of the switch

	switch(choice){

	case 1: collatzDriver();
		
break;
	case 2: hexConverterDriver();
	
break;
	case 3: printf("\nExiting...");
		exit(0);
break;
	} // switch gives user option to choose which function to use.

	return 0;
}

/*int factorial(int num)	
{
	if(num == 1){
		return 1;
	}

	return(num*factorial(num-1));
}

int costFunction(int num)
{
	if(num == 0){
		return 2;
	}
	
	return(num * costFunction(num - 1)) + 4 * num;
}*/

void collatzDriver()
{

	int number;

	printf("\n\nEnter a positive nonzero number or enter -1 to exit:");
	scanf("%d->", &number); // taking value to use function on

	if(number == -1){
		printf("Exiting...\n");
		exit (0);
	} // giving user option to quit program

	while(number <= 0){
		printf("\nInvalid input. Enter a number that is > 0:");
		scanf("%d", &number);
	}//error checking the user to make sure they stay in the paramaters of the function
	
	collatz(number);
	
	
	
}

void collatz(int number)
{

	if(number %2 == 0){
	
		number = number / 2;
	}//checks even number -- divies by 2

	else if(number %2 == 1){

		number = 3 * number + 1;
	}//checks odd number -- multiplys by 3 and adds 1

	printf("->%d", number);

	if(number != 1){
		collatz(number);	
	} // stops loop if the number == 1, keeps going if not
}

void hexConverterDriver()
{
	int number;
	int newnum;

	printf("Enter a positive nonzero number or enter -1 to exit:");
	scanf("%d", &number);

	while(number <= 0){
		printf("Invalid input. Enter a number that is > 0:");
		scanf("%d", &number);
	}

	if(number == -1){
		printf("Exiting...\n");
		exit(0);
	}
	
	newnum = hexConverter(number);
	printf("%d", newnum);

}

int hexConverter(int number)
{
	int digit = number%10;
	int newnum = number / 10;
	static int power = -1;

	power++;

	if(newnum == 0){
		int value = digit * pow (16, power);
		power = -1;
		return value;
	}

	else{
		int value = digit * pow(16, power);
		value += hexConverter(newnum);
		return value;
		}
}

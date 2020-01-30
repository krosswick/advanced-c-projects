//NAME: Kyle Rosswick
//LAB: 6
//PAWPRINT: klrmt5
//CLASS: CS2050
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Integer_
{

	int num;
	struct Integer_* nextInt;
	struct Integer_* prevInt;

}Integer;

Integer *addInt(Integer*, Integer*);
void printNums(Integer*);
void freeNums(Integer*);
Integer* deleteInt(Integer*);

int main()
{
	int choice;
	int value;
	Integer *newNum = malloc(sizeof(Integer));
	Integer *top = NULL;

	do{

	printf("\n\nPlease select an option:\n");
	printf("\n1:Add a number\n2:Delete a number\n3:Print number list\n4:Quit");
	printf("\n\nYour choice:");
	scanf("%d", &choice);

	while(choice < 1 || choice > 4){
		printf("\nThat option does not exist. Choose option 1, 2, 3 or 4: ");
		scanf("%d", &choice);
	}

	switch(choice){

		case 1:

			printf("\n\nEnter a number to add:");
			scanf("%d", &value);

			newNum->num = value;
			newNum->nextInt = NULL;
			newNum->prevInt = NULL;

			top = addInt(top, newNum);
	break;

		case 2:

			top = deleteInt(top);
	break;

		case 3:
			printNums(top);
	break;

		case 4:
			printf("\n\nExiting program...");
			freeNums(top);
			exit(0);
	break;

			
	}
	
	}while(choice !=4);

	return 0;
}

Integer *addInt(Integer *top, Integer *node)
{
	
	if(top == NULL){
		top = node;
	}

	else{
		top->nextInt = node;
		node->prevInt = top;
		top = node;
	}

	return top;
}

void printNums(Integer *top)
{
	Integer *temp;

	temp = top;

	while(temp->prevInt != NULL){
		temp = temp->nextInt;
	}

	while(temp != top){
		temp = temp->prevInt;
	}

	printf("%d->", temp->num);
}

void freeNums(Integer *top)
{
	Integer *temp;

	temp = top;

	while(top != NULL){
		temp = top->prevInt;
		free(top);
		top = temp;
	}
}

Integer* deleteInt(Integer *top)
{
	Integer *temp;

	temp = top->prevInt;
	free(top);

	top = temp;
	
	return top;
}

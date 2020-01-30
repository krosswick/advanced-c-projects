//NAME: Kyle Rosswick
//PAWPRINT: klrmt5
//LAB: 7
//CLASS: cs2050
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Integer_
{
	int num;
	struct Integer_ *leftPtr;
	struct Integer_ *rightPtr;
}Integer;

Integer *addNode(Integer*, Integer*);
void printInOrder(Integer*);
void searchTree(Integer*, int);

int main()
{
	int choice;
	int value;
	Integer *temp, *temp2, *root;
	root = NULL;

	do{

	printf("\n\n1:Add number\n2:Take a number off\n3:Print numbers\n4:Quit\nPlease select an option:");
	scanf("%d", &choice);

	while(choice < 1 || choice > 4){
		printf("\nThat is not an option. Please select 1, 2, 3, or 4\nPlease select an option:");
		scanf("%d", &choice);
	}

	switch(choice){

		case 1:
			temp = (Integer*)malloc(sizeof(Integer));
			temp->leftPtr = NULL;
			temp->rightPtr = NULL;
			printf("\nInsert number:");
			scanf("%d", &temp->num);

			if(root == NULL){
				root = temp;
			}
		
			else{
				temp2 = addNode(root, temp);
			}

		break;

		case 2:
			printf("\nEnter a number to delete:");
			scanf("%d", &value);
			searchTree(temp2, value);
		break;

		case 3:
			if(root == NULL){
				printf("\nList is empty.");
			}

			else{
				printInOrder(root);
			}
		break;

		case 4:
			printf("\nExiting program...");
			exit(0);
		break;
	}
	}while(choice != 4);

	return 0;			


}

Integer *addNode(Integer *root, Integer *value)
{
	if(value->num < root->num){

		if(root->leftPtr == NULL){
			root->leftPtr = value;
		}

		else{
			addNode(root->leftPtr, value);
		}
	}

	if(value->num > root->num){

		if(root->rightPtr == NULL){
			root->rightPtr = value;
		}

		else{
			addNode(root->rightPtr, value);
		}
	}

	return root;
}

void printInOrder(Integer *root)
{
	if(root != NULL){
		printInOrder(root->leftPtr);
		printf("%d ", root->num);
		printInOrder(root->rightPtr);
	}
}

void searchTree(Integer *root, int value)
{
	Integer *t1, *t2, *t3;

	if(root == NULL){
		printf("\nEither the tree is empty or that number does not live in the tree!\n");
		return;
	}

	else{
		t1 = root;
		t2 = t1;

		while(t1->num != value){
			t2 = t1;
			
				if(value < t1->num){
					t1 = t1->leftPtr;
				}

				else{
					t1 = t1->rightPtr;
				}
		}

	if(t1->leftPtr != NULL && t1->rightPtr != NULL){
		t3 = t1->rightPtr;

			while(t3->leftPtr != NULL){
				t2 = t3;
				t3 = t3->leftPtr;
			}

		t1->num = t3->num;
		t1 = t3;
	}

	if(t1->leftPtr == NULL && t1->rightPtr == NULL){

		if(t2->rightPtr == t1){
			t2->rightPtr = NULL;
		}

		else{
			t2->leftPtr = NULL;
		}

		free(t1);
		return;
	}

	if(t1->leftPtr == NULL && t1->rightPtr == NULL){
			
		if(t2->leftPtr == t1){
			t2->leftPtr = t1->rightPtr;
		}

		else{
			t2->rightPtr = t1->rightPtr;
		}

		free(t1);
		return;
	}

	if(t1->leftPtr != NULL && t1->rightPtr == NULL){

		if(t2->leftPtr == t1){
			t2->leftPtr = t1->leftPtr;
		}

		else{
			t2->rightPtr = t1->leftPtr;
		}

		free(t1);
		return;
	}

	}
}

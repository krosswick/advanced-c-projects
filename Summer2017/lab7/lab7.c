//NAME: Kyle Rosswick
//PAWPRINT: klrmt5
//CLASS: cs2050
//LAB: 7
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bt_
{
	int value;
	struct bt_ *right;
	struct bt_ *left;
}BST;

BST *insert(BST*, int);
int search(BST*, int);
BST* findMin(BST*);
BST* delete(BST*, int);
void printTree(BST*);
void displayBST(BST*, int);
void padding(char, int);

int main(int argc, char *argv[])
{
	int value;
	int num;
	int result;
	FILE *fPtr;
	BST *root = NULL;

	fPtr = fopen(argv[1], "r");

	if(argc != 2){
		printf("\nIncorrect number of command line arguments...");
		exit(0);
	}

	if(fPtr == NULL){
		printf("\nFile pointer is null.\n");
		exit(0);
	}

	while(!feof(fPtr)){
		fscanf(fPtr, "%d", &value);
		root = insert(root, value);
	}

	
	fclose(fPtr);

	printTree(root);

	printf("\nEnter a number to search for:");
	scanf("%d", &num);

	result = search(root, num);
	
	if(result == 0){
		printf("%d was found", num);
	}

	else{
		printf("%d was not found", num);
	}

	printf("\nEnter a number to remove from the tree");
	scanf("%d", &num);

//	root = delete(root, num);
	printTree(root);


	return 0;
}

BST *insert(BST* root, int value)
{
	BST *temp = malloc(sizeof(BST));

	if(root == NULL){
		temp->left = NULL;
		temp->right = NULL;
		temp->value = value;
		return temp;
	}

	if(value < root->value){
		root->right = insert(root->right,value);
	}
	
	if(value> root->value){
		root->left = insert(root->left, value);
	}	

	return root;
	
}

int search(BST* root, int value)
{
	if(root != NULL){

		if(value == root->value){
			return 1;
		}

		else if(value < root->value){
			return search(root->left, value);
		
		}

		else{
			return search(root->right, value);
		}
		
	}	

	return 0;
}

BST* findMin(BST *root)
{
	BST *cur = root;

	if(root == NULL){
		printf("\nRoot is null.");
		return NULL;
	}

	while(cur->left != NULL){
		cur = cur->left;
	}

	return(cur);

}

/*BST *delete(BST *root, int value)
{
	BST *temp;	

	if(root == NULL){
		return NULL;
	}

	if(value > root->value){
		root->left = delete(root->left, value);
	}

	else if(value > root->value){
		root->right = delete(root->right, value);
	}

	else if(root->left != NULL & root->right != NULL){
		temp = findMin(root->right);
		root->value = temp->value;
		root->right = delete(root->right, temp->value);
	}
			
	else{

		if()


}*/

void printTree(BST *root)
{
	displayBST(root, 0);
}

void displayBST(BST *root, int depth)
{
	if(root == NULL){
		padding(' ', depth);
		printf("-\n");
		return;
	}

	displayBST(root->left, depth + 4);
	padding(' ', depth);
	printf("%d\n", root->value);
	displayBST(root->right, depth + 4);
}

void padding(char toPrint, int numTimes)
{
	int i;

	for(i=0; i<numTimes; i++){
		printf("%c", toPrint);
	}
}

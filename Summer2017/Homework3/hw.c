//NAME: Kyle Rosswick
//PAWPRINT: klrmt5
//CLASS: cs2050
//HOMEWORK: 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCITYNAME 30
#define MAXLINELENGTH 50

typedef struct n_
{
	int zipCode;//a zip code in a given city/state
	char *city;//will point to city name
	char state[3];//State abbreviation- 3 because of null
	struct n_* left;// both left and right connect to other nodes
	struct n_* right;
} Node;

Node* importTree(char*);
Node* addNode(Node*, Node*);
int findState(Node*, char*);
Node* findZipCode(Node*, int);
void freeTree(Node*);

int main(int argc, char **argv)
{
	if(argc != 2){//Error check for commandline arguments
		printf("\nIncorrect number of command line arguments. Format should be: ./a.out <filename>...\n");
		exit(0);
	}

	int choice;
	int value = 0;
	int zip = 0;
	Node *zNode = NULL;
	Node *root = NULL;//hold root of the tree
	char *state = malloc(sizeof(char)*3);

	root = importTree(argv[1]);//read the file and make bst

	do{//put menu in loop

	printf("\n\n1.)Find the number of zip codes in a state.\n2.)Find a zip code.\n3.)Exit.\n\nSelect an option:");
	scanf("%d", &choice);

	while(choice < 1 || choice > 3){//check that user dosnt screw up the option
		printf("\nInvalid option! Please select 1, 2, or 3.\nSelect an option:");
		scanf("%d", &choice);
	}

	switch(choice){

		case 1:
			printf("\nEnter the state that you want to look for:");
			scanf("%s", state);

			value = findState(root, state);//assigns the value findState retuns to value

			if(value == 0){
				printf("\nNothing found for that state. Make sure you are abbreviating the state name if you are not doing so."); // if it returns 0 then your state does not exist
			}
	
			else{
				printf("\nThe state has %d zip codes.", value);
			}
		break;

		//end of case 1

		case 2:
			printf("\nEnter the zip code you want to find:");
			scanf("%d", &zip);//this is the zip code you will search for

			zNode = findZipCode(root, zip);

			if(zNode == NULL){
				printf("\nNo results found for %d. Make sure the zip code is 5 digits long if you are not doing so.", zip); // if it retuns null then your zip code isnt found
			}

			else{
				printf("\nThis is what I found for the zip code you entered:"); // makes it sounds fancy like siri
				printf("\nCity: %s", zNode->city);//points to city
				printf("\nState: %s", zNode->state);//points to state
			}

		break;

		//end of case 2

		case 3:
			printf("\n\nExiting the program...\n\n"); // this will simply exit the program
			freeTree(root);//free before you exit
			free(state);
			exit(0);
		break;

		//end of case 3
	}

	}while(choice != 3); //while choice isnt 3 - program will loop

	return 0;
}

Node* importTree(char *filename) //the function you guys gave out 
{

	Node* root = NULL;

	FILE *fPtr = fopen(filename, "r");

	if(!fPtr){
		printf("\nError opening file.");
		return NULL;
	}

	while(!feof(fPtr)){
		Node* new = malloc(sizeof(Node));

			if(!new){
				printf("\nFailed to allocate memory. Exiting program...\n\n");
				exit(0);
			}

		new->city = malloc(sizeof(char)*MAXCITYNAME);
			
			if(!(new->city)){
				printf("\nFailed to allocate memory. Exiting program...\n\n");
				exit(0);
			}

		new->left = NULL;
		new->right = NULL;

		char *line = malloc(sizeof(char)*MAXLINELENGTH);

			if(!line){
				printf("\nFailed to allocate mamory. Exiting program...\n\n");
				exit(0);
			}

		if(fgets(line, MAXLINELENGTH, fPtr) == NULL){

				if(!feof(fPtr)){
					printf("\nFile reading ended prematurely. Check for errors in the file.\n");
					exit(1);
				}
	
			free(new->city);
			free(line);
			free(new);
			fclose(fPtr);
			break;
		}

		char *tmp = strtok(line, ",");
		new->zipCode = atoi(tmp);
		tmp = strtok(NULL, ",");
		strcpy(new->city, tmp);
		new->city[strlen(tmp) + 1] = '\0';
		tmp = strtok(NULL, ",");
		strcpy(new->state, tmp);
		new->state[2] = '\0';

			root = addNode(root, new);
				if(!root){
					printf("\nRoot of tree is null. Exiting program...\n\n");
					exit(0);
				}

		free(line);
	}

	return root;
}

Node* addNode(Node *root, Node *newNode)
{
	if(newNode == NULL){
		printf("\nPointer is null.");
		exit(1);
	}

	if(root == NULL){ //new node will make the tree
		return newNode;
	}

	else{
		if(newNode->zipCode > root->zipCode){ //sorting larger zip codes to right side
			root->right = addNode(root->right, newNode);	
		}

		if(newNode->zipCode < root->zipCode){//sorts smaller zip codes on the left
			root->left = addNode(root->left, newNode);
		}
	}

	return root;
}

int findState(Node *root, char *state)
{
	if(root == NULL){ 
		return 0;
	}

	else{
		if(strcmp(root->state, state) == 0){// bumps return if there is a match -- strcmp will return 0 if its a match
			return 1 + findState(root->left, state) + findState(root->right, state);
		}
	}

	return findState(root->left, state) + findState(root->right, state);//traverse the tree

}

Node* findZipCode(Node *root, int zip)
{
	if(root == NULL){
		return NULL;
	}

	else{
		if(root->zipCode == zip){
			return root;
		}

		Node *x = NULL;

		//check left zips

		x = findZipCode(root->left, zip);

		if(x != NULL){
			return x;
		}

		//check right zips

		x = findZipCode(root->right, zip);

		if(x != NULL){
			return x;
		}
	}

	return NULL; // this will be the case if nothing is found
}

void freeTree(Node *root)
{
	if(root == NULL){
		return;
	}

	freeTree(root->left);//freeing all the stuff
	freeTree(root->right);
	free(root->city);
	free(root);

}

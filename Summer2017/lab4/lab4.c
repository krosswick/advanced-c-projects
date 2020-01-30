//NAME: KLRMT5
//PAWPRINT: KLRMT5
//LAB: 4
//CLASS: CS2050

#include <stdio.h>
#include <stdlib.h>

typedef struct node_{
	int data;
	struct node_ *next;
}node;

void print_list(node*);
void free_list(node*);
node* create_list(char*);
node* insert_at_head(node*, int);

int main(int argc, char *argv[])
{
	if(argc != 2){
		printf("\n\nIncorrect numer of commanld line arguments\n\nExiting...\n\n");
		exit(0);
	}

	node *list = NULL;

	char *input = argv[1];

	list = create_list(input);

	print_list(list);
	
	free_list(list);

	return 0;
}

node* create_list(char *file)
{
	int number;
	FILE *fPtr;

	node *start;

	start = NULL;

	fPtr = fopen(file, "r");

	while(fscanf(fPtr, "%d", &number) == 1){ //run untill fptr is at the end of file, also retrieve data
		start = insert_at_head(start, number);
	}

	fclose(fPtr);

	return start;//return start of list
		

}

void print_list(node *list)
{
	node *temp;

	temp = list;//move list using a place holder

	while(temp != NULL){
		printf("%d-> ", temp->data);
		temp = temp->next;//incrament
	}
	
	printf("NULL\n");
}


void free_list(node *list)
{
	node *start, *temp;//temp to loop thorugh

	start = list;//point to head of list
	temp = start;

	while(start != NULL){//loop to free

		start = temp->next;//moving to next node
		free(temp);
		temp = start;//change temp, go again
	}
}

node* insert_at_head(node *start, int data)
{
	if(start == NULL){//if list is empty
		start = malloc(sizeof(node));

		start->data = data;//assign data
		start->next = NULL;//next pointer points to null
	}

	else{
		node *new = (node*)malloc(sizeof(node));

		new->data = data;//assign data

		new->next = start;//moves to head of list

		start = new;
			
	}

	return start;

}

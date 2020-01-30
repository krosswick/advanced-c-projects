//NAME: Kyle Rosswick
//PAWPRINT: klrmt5
//CLASS: CS2050
//LAB: 6
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct word_
{
	char word[10];
	struct word_* nextWord;
	struct word_* prevWord;
}Word;

Word* addWord(Word*, Word*);
void printSentence(Word*);
void freeSentence(Word*);
Word* undoWord(Word**);

int main()
{
	int choice;

	Word *last = NULL;

	Word *undo = NULL;

	do{

	Word *newWord;

	printf("\n\nPlease select an option:\n");
	printf("\n1:Add word\n2:Undo word\n3:Redo word\n4:Quit\n\n");
	printf("Your choice:");
	scanf("%d", &choice);

	while(choice < 1 || choice > 4){
		printf("\nThat is not an option, please select option 1, 2, 3, or 4:");
		scanf("%d", &choice);
	}

	switch(choice){

		case 1:
			newWord = malloc(sizeof(Word)); // allocating space for words

			printf("\nEnter a word to add:");
			scanf("%s", newWord->word);

			newWord->nextWord = NULL;
			newWord->prevWord = NULL;			

			last = addWord(last, newWord);//adds word
			undo = addWord(undo,newWord);//reserves word for redoing
			printSentence(last);
		break;


		case 2:
	
			undoWord(&last);

			printSentence(last);
		break;

		case 3:
			last = addWord(last,undo);
			printSentence(last);	

		break;

		case 4:

			printf("\nExiting program...");
			freeSentence(last);//free memory
			exit(0);	
		break;
	}

	}while(choice != 4);

	return 0;
}

Word* addWord(Word *lastWord, Word *newWord)
{
	if(lastWord == NULL){
		lastWord = newWord;
	}

	else{
		lastWord->nextWord = newWord;
		newWord->prevWord = lastWord;
		lastWord = newWord;
	}

	return lastWord;

}

void printSentence(Word *lastWord)
{
	Word *temp;

	temp = lastWord;

	while(temp->prevWord != NULL){
		temp = temp->prevWord;
	}

	while(temp != NULL){
		printf("%s ", temp->word);
		temp = temp->nextWord;

	}

}			

void freeSentence(Word *lastWord)
{
	Word *temp;

	temp = lastWord;

	while(lastWord != NULL){
		lastWord = lastWord->prevWord;
		free(temp);
		temp = lastWord;
	}
}

Word* undoWord(Word **lastWordPtr){

	Word* undone = *lastWordPtr;

	(*lastWordPtr) = (*lastWordPtr)->prevWord;
	(*lastWordPtr)->nextWord = NULL;

	undone->nextWord = NULL;

	undone->prevWord = NULL;

	return undone;
}

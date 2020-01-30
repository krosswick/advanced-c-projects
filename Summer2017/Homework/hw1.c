//NAME: Kyle Rosswick
//CLASS: CS2050
//PAWPRINT: klrmt5
//HOMEWORK: #1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNAME 20

int count_lines(FILE*);
void allocate_memory(int**, int**, char***, int);
void read_lines(FILE*, int*, int*, char**, int);
void print_players(int*, int*, char**, int);
void sort_by_goals(int*, int*, char**, int);
int find_mvp(int*, int*, int);
int find_by_name(char**, char*, int);
void write_lines(FILE*, int*, int*, char**, int);

int main(int argc, char *argv[])
{
	if(argc != 3){
		printf("\n\nIncorrect number of commandline arguments. Please enter -- ./a.out input.txt output.txt\n");
		exit(0);
	}

	int *goals = NULL;
	int *assists = NULL;
	char **names = NULL;
	int size = 0;
	int mvp;
	int target;
	int i;
	
	char *fPlayer = (char*)malloc(MAXNAME*sizeof(char));

	char *input = argv[1];
	char *output = argv[2];

	FILE *fPtr = fopen(input, "r");

		if(fPtr == NULL){
			printf("\n\nPointer is null. Exiting program...\n");
			return 0;
		} //error checking for null pointer

	FILE *wPtr = fopen(output, "w");

		if(wPtr == NULL){
			printf("\n\nPointer is null. Exiting program...\n");
			return 0;
		} //error check for null pointer

	size = count_lines(fPtr); //counting lines and assigning number of lines to size

	allocate_memory(&goals, &assists, &names, size); //allocating memory for my pointers


	printf("\nRead the following %d players from file.\n\n", size); // check to make sure lines are being counted correctly (should be 9).	
	
	read_lines(fPtr, goals, assists, names, size);// loads info from file to be printed

	print_players(goals, assists, names, size);// prints loaded info

	sort_by_goals(goals, assists, names, size);//sorts data by goals

	printf("\n\nSorting by goals...\n\n");

	print_players(goals, assists, names, size);//reprint to show data in sorted fasion

	mvp = find_mvp(goals, assists, size);//tells user who had the most points (goals + assists)

	printf("\nMVP was %s with %d total points!", *(names + mvp), (*(goals + mvp) + *(assists + mvp)));//derefrencing to print values

	printf("\n\nSearch player by name here:");
	scanf("%s", fPlayer);

	target = find_by_name(names, fPlayer, size);//searches file for player match
	
	if(target != -1){
		printf("\n\n%s has %d goals and %d assists!\n", *(names + target), *(goals + target), *(assists + target));//function returns index value if there is a match
	}

	else{
		printf("This player does not exist!");//function returns 0 if no match is found
	}

	write_lines(wPtr, goals, assists, names, size);

	free(fPlayer);
	free(goals);
	free(assists);

	for(i=0; i<size; i++){
		free(*(names + i));
	}
	free(names);//freeing all allocated data

	fclose(fPtr);
	fclose(wPtr);//closing files

	return 0;
}

int count_lines(FILE *fPtr)
{
	int c = 0;
	int lines = 0;

	if(fPtr == NULL){
		printf("\n\nPointer is null. Exiting program...\n");
		return 0;
	}	// error check for null pointer

	while((c = fgetc(fPtr)) != EOF){
		if(c == '\n'){
			lines++;
		}
	}	//check for hidden newline characters in the txt file to detect new lines. Counts each line as long as it dosnt mark the end of the file.

	rewind(fPtr); //rewinding for future use

	return lines;
}

void allocate_memory(int **goals, int **assists, char ***names, int size)
{
	int i;

	*goals = malloc(sizeof(int)*size);
	*assists =  malloc(sizeof(int)*size);
	*names = malloc(sizeof(char*)*size);	

		for(i=0; i<size; i++){
		
			*(*names + i) = malloc(sizeof(char)*MAXNAME);
		}
}

void read_lines(FILE *fPtr, int *goals, int *assists, char **names, int size)
{
	int i;
	char *hold = malloc(MAXNAME*sizeof(char));
	char *token = NULL;
	char *space = " ";

	for(i=0; i<size; i++){
		if(fgets(hold, MAXNAME, fPtr) != NULL){ //loops through file

			token = strtok(hold, space);
			strcpy(names[i],  token);//breaks up names into tokens
		
			token = strtok( NULL, space);//goes back to previous line that was left off and continues 
			int tgoals =atoi(token);
			goals[i] = tgoals;//incramenting 

			token = strtok(NULL, space);
			int tassists = atoi(token);
			assists[i] = tassists;
		}
	}

	free(hold);

}

void print_players(int *goals, int *assists, char **names, int size)
{
	int i;

	printf("%-35s %-10s %-10s\n", "[Names]", "[Goals]", "[Assists]");
	
	for(i=0; i<size; i++){//loop through file
		printf("%-35s %-10d %-10d\n", *(names + i), *(goals + i), *(assists + i));
	}

	return;
}

void sort_by_goals(int *goals, int *assists, char **names, int size)
{
	int left, right, temp;
	char tNames[MAXNAME];


	for(left=1; left<=size - 1; left++){
		right = left;
		
		while(right > 0 && goals[right] > goals[right-1]){
			temp =  goals[right];
			goals[right] = goals[right-1];//swap
			goals[right-1] = temp;//hold

			temp = assists[right];
			assists[right] = assists[right-1];//swap
			assists[right-1] = temp;//hold

			strcpy(tNames, names[right]);//pointer to name
			strcpy(names[right], names[right-1]);//swap
			strcpy(names[right-1], tNames);//hold

			right--;
		}
	}

}

int find_mvp(int *goals, int *assists, int size)
{
	int *points = (int*)malloc(size*sizeof(int));
	int i;	
	int mvp;
	int max = 0;

	for(i=0; i<size; i++){
		*(points + i) = *(goals + i) + *(assists + i);//checks who has the most "points" by adding goals and assists-- stores into points
	
		if(*(points + i) > max){
			max = *(points + i);
			mvp = i;//returns index of the mvp
		}
	}

	free(points);

	return mvp;
}

int find_by_name(char **names, char *target, int size)
{
	int i;

	for(i=0; i<size; i++){
		
		if(strcmp(target, *(names + i)) == 0){//checks for match, returns "i" if there is
			
			return i;
		}
	}

	return -1;//if no plater is found
}

void write_lines(FILE *wPtr, int *goals, int *assists, char **names, int size)
{
	int i;

	for(i=0; i<size; i++){//loop through file
		fprintf(wPtr, "%s %d %d\n", *(names + i), *(goals + i), *(assists + i));
	}

	rewind(wPtr);
}

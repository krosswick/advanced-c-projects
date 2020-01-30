#include <stdio.h>
#include <stdlib.h>

int main( void )
{

	int numInts = 10;
	int *arrPtr;
	int *itemPtr;
	int i;
	int val;
	
	printf("\n\nThe value of arrPtr = %p\n", arrPtr);
	printf("The memory location for arrPtr = %p\n\n", &arrPtr);
	
	// malloc needs to know the number of bytes to allocate
	// sizeof(int) returns the number of bytes for an int
	// the number of int values times the size of an int gives the number of bytes
	arrPtr = malloc(numInts * sizeof(int));

	printf("arrPtr = %p, size of int = %lu\n", arrPtr, sizeof(int));
	printf("The memory location for arrPtr = %p\n\n", &arrPtr);
	
	for ( i = 0; i < numInts; i++)
	{
		// Adding i increments the pointer to the memory location of the next int.
		// i is NOT the number of bytes to add.
		// If an int is 4 bytes then the itemPtr will be moved forward
		// four bytes each time i is incremented.
		itemPtr = arrPtr + i;  
		val = i * 10;
		printf("Storing %i at memory location = %p\n", val, itemPtr);
		*itemPtr = val;
	}
	
	for ( i = 0; i < numInts; i++)
	{
		itemPtr = arrPtr + i;
		printf("%i: value = %i at memory location = %p\n", i, *itemPtr, itemPtr);
	}
	
	for ( i = 0; i < numInts; i++)
	{
		printf("%i: value = %i\n", i, arrPtr[i]);
	}

	free(arrPtr);

	return 0;
}
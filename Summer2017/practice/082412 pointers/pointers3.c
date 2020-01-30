#include <stdio.h>
#include <stdlib.h>

int main( void )
{

	int nelem = 10;
	char *arrPtr;
	char *itemPtr;
	int i;
	int index;
	
	arrPtr = malloc(nelem * sizeof(char));

	printf("arrPtr = %p, size of char = %lu\n\n", arrPtr, sizeof(char));
	
	for ( i = 0; i < nelem; i++)
	{
		itemPtr = arrPtr + i;
		printf("Storing char at memory location = %p (index = %i)\n", itemPtr, i);
		*itemPtr = 'x';
	}

	free(arrPtr);

	return 0;
}
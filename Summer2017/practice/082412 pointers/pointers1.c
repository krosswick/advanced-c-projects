#include <stdio.h>

int main( void )
{

	int i = 5;
	int *iPtr;
	
	iPtr = &i;
	
	printf("iPtr = %p  address of i = %p\n\n", iPtr, &i);
	printf("Address of iPtr = %p\n\n", &iPtr);

	return 0;
}
#include<stdio.h>

int main()
{
	int num1 = 123;
	int num2 = 234;
	int num3 = 345;
	
	int *pr1, *pr2, **pr3;

	pr2 = &num1;
	pr1 = &num3;
	pr3 = &pr2;

	printf("\n\n*pr2 is: %d\n", *pr2);
	printf("\npr3 is: %p\n", pr3);
	printf("\n*pr3 is: %p\n", *pr3);
	printf("\n**pr3 is: %d\n", **pr3);
	printf("\n&pr1 is: %p\n", &pr1);

	*pr3 = &num2;

	printf("\n*pr2 is: %d\n", *pr2);
	printf("\npr3 is: %p\n", pr3);

	printf("\n\n----These are the addresses----\n\n\npr1 is: %p = 5000\n", pr1);
	printf("\npr2 is: %p = 6000\n", pr2);
	printf("\npr3 is: %p = 7000\n", pr3);
	printf("\nnum1 is: %p = 2000\n", &num1);
	printf("\nnum2 is: %p = 3000\n", &num2);
	printf("\nnum3 is: %p = 4000\n", &num3);

	//char *iptr = 'x';

	//printf("\n%c\n", *iptr);


	return 0;
}

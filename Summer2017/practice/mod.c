#include <stdio.h>
#define S_SIZE 10
int main(){

	int i;
	char s[10] = { 'g', 'o', 'm', 'i', 'z', 'z', 'o', 'u'};

	for(i = S_SIZE - 2; i > 4; i--){
		printf("%c ", s[i]);
	}

	return 0;
}

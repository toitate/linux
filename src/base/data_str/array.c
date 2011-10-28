
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <memory.h>

int integer;

char ch;

void array();
void array_char(); 

int
main(void) {
	
	array();
	printf("\n");
	printf("\n");
	array_char();

	return 0;
}



void array() {

	char array[7] = {0};
	printf("\n%s %d %p\n", array, sizeof(array), array);
	char temp[7] = {'o','i','t','a','t','e'};//temp[7]=NULL or \0
	memcpy(array, temp, sizeof(array));
	printf("%s %d %p %c %p\n", 
		array, sizeof(array), array, array[0], &array[0]);

	int array_int[7] = {0};
	printf("\n%s %d %p\n", array_int, sizeof(array_int), array_int);
	int temp_int[7] = {1,2,3,4,5,6};//temp_int[7]=0
	memcpy(array_int, temp_int, sizeof(temp_int));
	int i = 0;
	for (i; i<7; i++) printf("%d", array_int[i]); 
	printf(" %d %p %d %p\n", 
		sizeof(array_int), array_int, array_int[0], &array_int[0]);

}


void array_char() {

	char *message[] = {
		"first",
		"second",
		"third",
		"forth"
	};

	int i = 0;
	for(i; i<4; i++) 
		printf("%s %d %p\n", message[i], sizeof(message[i]), message[i]);
	printf("%d\n", sizeof(message));	
}


#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <memory.h>


void primitive();
void array();
void primitive_max();

int
main(void) {
	
	primitive();
	array();
	printf("\n");
	primitive_max();

	return 0;
}



void primitive() {

	//Integer Type
	printf("\n%d %d\n", sizeof(int), sizeof(int *));
	//Integer Variable
	int i = 99;
	printf("%d %p\n", i, &i);
	//Integer Pointer
	int *j = &i;
	printf("%d %p\n", *j, j);

	//Character Type
	printf("\n%d %d\n", sizeof(char), sizeof(char *));
	//Character Variable
	char c = 'z';
	printf("%c %p\n", c, &c);
	//Character Pointer
	char *d = &c;
	printf("%c %p\n", *d, d);

}

void array() {

	//Array Caracter
	char array[7] = {0};
	printf("\n%s %d %p\n", array, sizeof(array), array);
	char temp[7] = {'o','i','t','a','t','e'};//temp[7]=NULL or \0
	memcpy(array, temp, sizeof(array));
	printf("%s %d %p %c %p\n", array, sizeof(array), array, array[0], &array[0]);

	//Array Integer
	int array_int[7] = {0};
	printf("\n%s %d %p\n", array_int, sizeof(array_int), array_int);
	int temp_int[7] = {1,2,3,4,5,6};//temp_int[7]=0
	memcpy(array_int, temp_int, sizeof(temp_int));
	int i = 0;
	for (i; i<7; i++) printf("%d", array_int[i]); 
	printf(" %d %p %d %p\n", sizeof(array_int), array_int, array_int[0], &array_int[0]);

}

void primitive_max() {

	printf("%d, %d\n", INT_MAX, INT_MIN);
	printf("%d, %d\n", CHAR_MAX, CHAR_MIN);

}





/* 
 * 
 * 
 * 
 * 
 * 
*/

#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <memory.h>


void integer();
void array();
void integer_max();
void check_address();

int
main(void) {
	
	integer();
	array();
//	check_address();


	return 0;
}



void integer() {

	//Integer
	printf("\n%d %d\n", sizeof(int), sizeof(int *));
	int i = 99;
	printf("%d %p\n", i, &i);
	int *j = &i;
	printf("%d %p\n", *j, j);

	//Character
	printf("\n%d %d\n", sizeof(char), sizeof(char *));
	char c = 'z';
	printf("%c %p\n", c, &c);
	char *d = &c;
	printf("%c %p\n", *d, d);

}

void array() {

	//Array
	char array[7] = {0};
	printf("\n%s %d %p\n", array, sizeof(array), array);
	char temp[7] = {'o','i','t','a','t','e'};
	memcpy(array, temp, sizeof(array));
	printf("%s %d %p\n", array, sizeof(array), array);

	//Array Integer
	int array_int[7] = {0};
	printf("\n%s %d %p\n", array_int, sizeof(array_int), array_int);
	int temp_int[7] = {1,2,3,4,5,6};
	memcpy(array_int, temp_int, sizeof(temp_int));
	int i = 0;
	for (i; i<6; i++) printf("%d", array_int[i]); 
	printf(" %d %p\n", sizeof(array_int), array_int);

}

void integer_max() {

	printf("int  max is %d, min is %d\n", INT_MAX, INT_MIN);
}

void pointer() {
	
	int number = 9;
	int *pointer;
	//*pointer = 99; 
	printf("int  number is %p\n", &number);
	printf("int  umber is %d\n", number);

	printf("int *pointer is %p\n", pointer);
	printf("int *pointer is %d\n", &pointer);


}

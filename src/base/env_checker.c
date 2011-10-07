
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


void check_size();
void check_max();
void check_address();

int
main(void) {
	
	printf("int\n");

	check_size();
	check_max();
	check_address();


	return 0;
}

void check_size() {

	printf("int size is %d bytes\n", sizeof(int));
	printf("int *size is %d bytes\n", sizeof(int *));
}

void check_max() {

	printf("int  max is %d, min is %d\n", INT_MAX, INT_MIN);
}

void check_address() {
	
	int number = 9;
	int *pointer;
	//*pointer = 99; 
	printf("int  number is %p\n", &number);
	printf("int  umber is %d\n", number);

	printf("int *pointer is %p\n", pointer);
	printf("int *pointer is %d\n", &pointer);


}


#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <memory.h>

int integer;

char ch;

void primitive();
void array();
void primitive_max();
void array_char(); 

int
main(void) {
	
	primitive();
	array();
	printf("\n");
	primitive_max();
	printf("\n");
	array_char();

	return 0;
}



void primitive() {

	int i;
	const int ci;
	static int si;

	int *pi;
	const int *cpi;
	static int *spi;

	printf("%d %d\n\n", sizeof(int), sizeof(int *));

	printf("%d %p\n", i, &i);
	printf("%d %p\n", ci, &ci);
	printf("%d %p\n\n", si, &si);

	printf("%d %p\n", *pi, pi);
	printf("%d %p\n", *cpi, cpi);
	printf("%d %p\n\n", *spi, spi); //Segmentation Fault

	printf("%d %p\n", integer, &integer);



	printf("\n%d %d\n", sizeof(char), sizeof(char *));

	printf("%c %p\n", ch, &ch);
	char c ;
	printf("%c %p\n", c, &c);
	c = 'z';
	printf("%c %p\n", c, &c);

	char *d;
	printf("%c %p\n", *d, d);
	d = &c;
	printf("%c %p\n", *d, d);

}

void array() {

	char array[7] = {0};
	printf("\n%s %d %p\n", array, sizeof(array), array);
	char temp[7] = {'o','i','t','a','t','e'};//temp[7]=NULL or \0
	memcpy(array, temp, sizeof(array));
	printf("%s %d %p %c %p\n", array, sizeof(array), array, array[0], &array[0]);

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


void array_char() {

	char *message[] = {
		"first",
		"second",
		"third",
		"forth"
	};

	int i = 0;
	for(i; i<4; i++) printf("%s %d\n", message[i], sizeof(message[i]));
	printf("%d\n", sizeof(message));	
}

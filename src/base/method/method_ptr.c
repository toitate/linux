/*
 * Method Pointer
 * return type (* pointer name) (argument list);
 *
*/

#include <stdio.h>

int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int div(int a, int b);
int mod(int a, int b);

void array_ptr();

int
main() {
	
	array_ptr();

	return 0;
}

void array_ptr() {
	int i = 0;

	int (*p[5])(int a, int b) = {add, sub, mul, div, mod};
	for(i; i<5; i++) printf("%d\n", (*p[i])(10,2));
}

int add(int a, int b) {	return (a + b);}
int sub(int a, int b) {	return (a - b);}
int mul(int a, int b) {	return (a * b);}
int div(int a, int b) {	return (a / b);}
int mod(int a, int b) {	return (a % b);}

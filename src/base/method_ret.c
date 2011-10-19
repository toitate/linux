#include <stdio.h>


struct structure {
	int id;
	char name[10];
};


int integer();
char character();
struct structure structure_ret();

int *integer_p();
char *character_p();
struct structure *structure_ret_p();

char *array_p();

int
main() {

	int a = integer();
	printf("%d %p\n\n", a, &a);

	char c = character();
	printf("%c %p\n\n", c, &c);

	struct structure str = structure_ret();
	printf("%d %s %d %p\n\n", str.id, str.name, sizeof(str), &str);

	printf("\n\n");

	int *i = integer_p();
	printf("%d %p\n\n", *i, i);

	char *d = character_p();
	printf("%c %p\n\n", *d, d);

	struct structure *str_p = structure_ret_p();
	//TODO This is wrong. There is array within structure.
	printf("%d %s %d %p\n\n", str_p->id, str_p->name, sizeof(str_p), str_p);

	//TODO This is wrong. Do not return array from function.
	char *array;
	array = array_p();
	printf("%s %p\n", array, array);	

	return 0;
}


int integer() {
	int a = 9;
	printf("%d %p\n", a, &a);
	return a;
}

char character() {
	char c = 'c';
	printf("%c %p\n", c, &c);
	return c;
}

struct structure structure_ret() {

	struct structure str = {99, "oitate"};
	printf("%d %s %d %p\n", str.id, str.name, sizeof(str), &str);
	return str;
}



int *integer_p() {
	int temp = 9;
	int *a = &temp;

	printf("%d %p\n", *a, a);
	return a;
}

char *character_p() {
	char temp = 'c';
	char *c = &temp;

	printf("%c %p\n", *c, c);
	return c;
}

//TODO This method is wrong.
struct structure *structure_ret_p() {

	struct structure temp = {99, "oitate"};
	struct structure *str = &temp;
	printf("%d %s %d %p\n", str->id, str->name, sizeof(str), &str);
	return str;
}

//TODO This method is wrong.
char *array_p() {
	char str[] = "this is wrong."; 
	return str;
}


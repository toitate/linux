
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <memory.h>

void primitive_int();
void primitive_char();
void primitive_max();
void structure(); 

int
main(void) {
	
	primitive_int();
	printf("\n");
	primitive_char();
	printf("\n");
	primitive_max();
	printf("\n");
	structure();

	return 0;
}



void primitive_int() {

	int i;
	const int ci;
	static int si;
	
	int *pi;
	const int *pci;
	static int *psi;

	printf("%d %d\n", sizeof(int), sizeof(int *));

	printf("%d %p %d %p\n", i, &i, *&i, &*&i);
	printf("%d %p\n", ci, &ci);
	printf("%d %p\n\n", si, &si);

	printf("%d %p\n", *pi, pi);
	printf("%d %p\n", *pci, pci);
	//printf("%d %p\n\n", *psi, psi); //Segmentation Fault
}

void primitive_char() {

	char c;
	const char cc;
	static char sc;

	char *pc;
	const char *pcc;
	static char *psc; 

	printf("%d %d\n", sizeof(char), sizeof(char *));

	printf("%c %p %c %p\n", c, &c, *&c, &*&c);
	printf("%c %p\n", cc, &cc);
	printf("%c %p\n\n", sc, &sc);

	printf("%c %p\n", *pc, pc);
	printf("%c %p\n", *pcc, pcc);
	//printf("%c %p\n", *psc, psc);//Segmentation fault

}

void primitive_max() {

	printf("%d, %d\n", INT_MAX, INT_MIN);
	printf("%d, %d\n", CHAR_MAX, CHAR_MIN);

}

void structure() {

	struct data {
		int int_data;
		char char_data;
	};
	struct data str_data;
	struct data *p_data;

	printf("%d %d %d\n", sizeof(struct data), sizeof(str_data), sizeof(p_data));

	printf("%d %c %p\n", str_data.int_data, str_data.char_data,	str_data);
	printf("%p %p %p\n", p_data->int_data, p_data->char_data, p_data);
}

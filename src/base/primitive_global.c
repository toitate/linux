
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <memory.h>


int i;
const int ci;
static int si;

int *pi;
const int *pci;
static int *psi;

char c;
const char cc;
static char sc;

char *pc;
const char *pcc;
static char *psc; 

void primitive_int();
void primitive_char();

int
main(void) {
	
	primitive_int();
	printf("\n");
	primitive_char();

	return 0;
}



void primitive_int() {

	printf("%d %p\n", i, &i);
	printf("%d %p\n", ci, &ci);
	printf("%d %p\n\n", si, &si);

	//segmantation fault
	//printf("%d %p\n", *pi, pi);
	//printf("%d %p\n", *pci, pci);
	//printf("%d %p\n\n", *psi, psi);
}


void primitive_char() {

	printf("%c %p\n", c, &c);
	printf("%c %p\n", cc, &cc);
	printf("%c %p\n\n", sc, &sc);

	//segmantation fault
	//printf("%c %p\n", *pc, pc);
	//printf("%c %p\n", *pcc, pcc);
	//printf("%c %p\n", *psc, psc);
}




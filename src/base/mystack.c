#include <stdio.h>

#define MAX 100
#define OK  0
#define NG  -1


int stack[MAX];
int *sp;
int *sp_max;
int *sp_min;

void init();
int push(int data);
int pop(int *data_p);

int
main() {
	int i = 0;

	init();
	
	for (i; i<5; i++) {
		push(i);
	}
	for (i; i>0; i--) {
		int data;
		pop(&data);
		printf("%d\n", data);
	}

	return 0;
}

void init() {
	sp = stack;
	sp_max = stack + (MAX-1);
	sp_min = stack;
}

int push(int data) {

	int ret;
	if(sp == sp_max) ret = NG;
	else {
		*sp = data;
		sp++;
		ret = OK;
	}
	return ret;
}

int pop(int *data_p) {

	int ret;
	if (sp ==sp_min) ret = NG;
	else {
		sp--;
		*data_p = *sp;
		ret = OK;
	}
	return ret;
}


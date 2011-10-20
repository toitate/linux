#include <stdio.h>

#define MAX 10 
#define OK   0
#define NG  -1


char queue[MAX];
char *head;
char *tail;
char *queue_max;
char *queue_min;

void init();
int push(char data);
int pop(char *data_p);

int
main() {
	int i = 0;

	init();
	
	for (i; i<4; i++) {
		push('a');
		push('b');
		push('c');
		push('d');
	}
	for (i; i>0; i--) {
		char data;
		pop(&data);
		printf("%c\n", data);
	}

	return 0;
}

void init() {
	head = queue;
	tail = head;
	queue_min = queue;
	queue_max = queue + (MAX-1);
}

int push(char data) {

	int ret;
	if(head == queue_min && tail == queue_max || tail == head-1) ret = NG;
	else {
		*tail = data;
		tail++;
		if (tail > queue_max) tail = queue_min;
		ret = OK;
	}
	return ret;
}

int pop(char *data_p) {

	int ret;
	if (tail == head) ret = NG;
	else {
		*data_p = *head;
		head++;
		if (head > queue_max) head = queue_min;
		ret = OK;
	}
	return ret;
}



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#include "list.h"

//8 bytes = 4 bytes + 4bytes;
typedef struct {
	int value;
	struct list_d *next;
} list_d;


list_d *init();
void del(list_d *list);
list_d *search(list_d *list);
void add(list_d *list, int value);
void clear(list_d *list);

void print(list_d *list);

list_d *init() {
	list_d* head;
	
	head = (list_d *)malloc(sizeof(list_d));
	if (head == NULL) exit(1);

	head->value = 0;
	head->next = NULL;

	return head;
}

void add(list_d *list, int value) {
	list_d *elem;
	list_d *tail;

	if(list == NULL) exit(1);
	if(value<0) exit(1);

	elem = (list_d *)malloc(sizeof(list_d));
	if (elem == NULL) exit(1);
	elem->value = value;
	elem->next = NULL;

	tail = search(list);
	tail->next = elem;//TODO
	
}

list_d *search(list_d *list) {
	list_d *elem = list;

	while (elem->next != NULL) {
		elem = (list_d *)elem->next;//TODO
	}
	return elem;

}

void clear(list_d *list) {
	list_d *elem = (list_d *)list->next;
	list_d *prev = list;
	
	while (elem != NULL) {
		prev->next = elem->next;
		free(elem);
		elem = (list_d *)prev->next;
	}
}

void del(list_d *list) {

	clear(list);
	free(list);
}


void print(list_d *list) {
	
	list_d *elem = list;

	while (elem->next != NULL) {
		elem = (list_d *)elem->next;//TODO
		printf("%p = %d %p:\n", elem, elem->value, elem->next);
	}
}

int main() {
	
	printf("%d\n\n", sizeof(list_d));

	list_d *list = init();

	add(list, 10);
	add(list, 20);
	add(list, 30);
	print(list);
	del(list);

	return 0;
}

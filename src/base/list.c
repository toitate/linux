/*
 * Data Structure
 *
 * void *malloc(size_t size)
 * void free(void *memblock)
 * void *memset(void *dest, int c, size_t count)
 * void *memcpy(void *dest, const void *src, size_t count)
 *
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef strcut l_data {
	char ch;
	struct l_data *pre;
	struct l_data *next;
}

void add_head(struct l_data new_list);
void add_tail(struct l_data new_list);
void remove_all();

struct l_data remove_head();
struct l_data remove_tail();

struct l_data get_attr(int n);
void set_attr(int n, struct l_data new_data);
void remove_attr(int n);

int get_count();
int empty();

int insert_after(int n, struct l_data new_data);
int insert_before(int n, struct l_data new_data);

int find_data(struct l_data data);
struct l_data get_next();
void get_head_pos();
struct l_data get_before();
void get_tail_pos();

struct l_data *head, *tail, *ptr;


int
main() {
	struct l_data data;
	char ch;
/*
	ch = getche();
	while (isalpha(ch)) {
		data.ch = ch;
		add_tail(data);
		ch = getche();
	}

	printf("\n");

	do {
		data = get_next();
		if (data.ch)
			putch(data.ch);
	} while (data.ch);

	remove_all();
*/
	return 0;
}


void add_head(struct l_data new_list) {

	struct l_data *p;

	p = (struct l_data *)malloc(sizeof(struct l_data));

	*p = new_list;
	
	p->pre = NULL;
	p->next = head;

	if (head) head->pre = p;

	head = p;

}

void add_tail(struct l_data new_list) {

	struct l_data *p;

	p = (struct l_data *)malloc(sizeof(struct l_data));

	if (tail) tail->next = p;
	else tail->pre = p;
	
	*p = new_list;
	
	p->pre = tail;
	p->next = NULL;
	
	tail = p;

}

void remove_all() {

	struct l_data *p, *next;
	
	for (p=head; p; p=next) {
		next = p->next;
		free(p);
	}

	tail = head = NULL;
}

struct l_data remove_head(){

	struct l_data ret;
	
	ret.ch = '\0';//NULL;

	if (head) {
		ret = *head;
		free(head);
		head = ret.next;
		if (head) head->pre = NULL;
		else tail = NULL;
	}

	ret.next = NULL;
	return ret;
}

struct l_data remove_tail() {

	struct l_data ret;
	
	ret.ch = '\0';//NULL;

	if (tail) {
		struct l_data *p;
		ret = *tail;
		if (tail->pre) tail->pre->next = NULL; 
		free(tail);
		tail = ret.pre;
		if (!tail) head = NULL;
	}

	ret.next = NULL;
	return ret;
}

struct l_data get_attr(int n) {

	struct l_data *p;
	struct l_data ret;

	ret.ch = '\0';
	ret.next = NULL;

	if (n<0) return ret;

	for (p=head; p; p = p->next) {
		if (n-- == 0) return *p;
	}

	return ret;
}

void set_attr(int n, struct l_data new_data) {

	struct l_data *p;
	struct l_data *next, *pre;

	if (n<0) return ret;

	for (p=head; p; p = p->next) {
		if (n-- == 0) {
			next = p->next;
			pre = p->pre;
			*p = new_data;
			p->next = next;
			p->pre = pre;
			return;
		}
	}

	return ret;
}

void remove_attr(int n) {

	struct l_data *p;
	struct l_data *pre;

	if (n < 0) return ret;
	if (n == 0) return ret;
	if (n < 0) return ret;

	for (p=head; p; p = p->next) {
		if (n-- == 0) {
			next = p->next;
			pre = p->pre;
			*p = new_data;
			p->next = next;
			p->pre = pre;
			return;
		}
	}
}

int get_count() {

	struct l_data *p;
	int n = 0;

	if (head) {
		for (p = head; p ; p=p->next)
			n++;
	}
	return n;
}

int empty() {

	return head ? 0 : 1;
}

int insert_after(int n, struct l_data new_data) {

	return 0;
}

int insert_before(int n, struct l_data new_data) {

	return 0;
}

int find_data(struct l_data data) {
	return 0;
}

struct l_data get_next() {
}

void get_head_pos() {
}


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

typedef strcut column {
	char ch;
	struct column *pre;
	struct column *next;
}

void add_head(struct column c);
void add_tail(struct column c);
void remove_all();

struct column remove_head();
struct column remove_tail();

struct column get_attr(int n);
void set_attr(int n, struct column new_data);
void remove_attr(int n);

int get_count();
int empty();

int insert_after(int n, struct column new_data);
int insert_before(int n, struct column new_data);

int find_data(struct column data);
struct column get_next();
void get_head_pos();
struct column get_before();
void get_tail_pos();

struct column *head, *tail, *ptr;


int
main() {
	struct column data;
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


void add_head(struct column c) {

	struct column *p;
	
	p = (struct column *)malloc(sizeof(struct column));
	*p = c;
	p->pre = NULL;
	p->next = head;
	if (head) head->pre = p;
	head = p;
}

void add_tail(struct column c) {

	struct column *p;

	p = (struct column *)malloc(sizeof(struct column));
	if (tail) tail->next = p;
	else tail->pre = p;
	*p = c;
	p->pre = tail;
	p->next = NULL;
	tail = p;
}

void remove_all() {

	struct column *p, *next;
	
	for (p=head; p; p=next) {
		next = p->next;
		free(p);
	}
	tail = head = NULL;
}

struct column remove_head(){

	struct column ret;
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

struct column remove_tail() {

	struct column ret;
	
	ret.ch = '\0';//NULL;

	if (tail) {
		struct column *p;
		ret = *tail;
		if (tail->pre) tail->pre->next = NULL; 
		free(tail);
		tail = ret.pre;
		if (!tail) head = NULL;
	}

	ret.next = NULL;
	return ret;
}

struct column get_attr(int n) {

	struct column *p;
	struct column ret;

	ret.ch = '\0';
	ret.next = NULL;

	if (n<0) return ret;

	for (p=head; p; p = p->next) {
		if (n-- == 0) return *p;
	}

	return ret;
}

void set_attr(int n, struct column new_data) {

	struct column *p;
	struct column *next, *pre;

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

	struct column *p;
	struct column *pre;

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

	struct column *p;
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

int insert_after(int n, struct column new_data) {

	return 0;
}

int insert_before(int n, struct column new_data) {

	return 0;
}

int find_data(struct column data) {
	return 0;
}

struct column get_next() {
}

void get_head_pos() {
}


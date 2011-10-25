#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FOUND 0
#define MAX 256

void search();
void search_file();

int
main() {
	search();
	search_file();
	return 0;
}


void search() {

	char a[] = "deabkisabpoiab";
	char b[] = "ab";
	char *a_p = a;
	char *b_p = b;

	int n = strlen(a);
	int m = strlen(b);
	int cnt = 0;
	int i = 0;

	for (i; i<=n-m; i++) 
		if (strncmp(&a[i], b, m) == FOUND) cnt++;
	printf("%d\n", cnt);

	n = strlen(a_p);
	m = strlen(b_p);
	cnt = 0;
	i = 0;
	
	for (i; i<=n-m; i++) 
		if (strncmp(a_p+i, b_p, m) == FOUND) cnt++;
	printf("%d\n", cnt);
}

void search_file() {

	FILE *fp;
	char buf[MAX];
	char b[] = "ab";
	const char *file = "search.txt";	

	int m = strlen(b);
	int cnt = 0;

	if ((fp=fopen(file, "r")) == NULL) exit(EXIT_FAILURE);
	while(fgets(buf, MAX, fp) != NULL) {
		int n = strlen(buf);
		int i = 0;
		for (i; i<=n-m; i++)
			if (strncmp(buf, b, m) == FOUND) cnt++;
	}

	printf("%d\n", cnt);
	fclose(fp);
}


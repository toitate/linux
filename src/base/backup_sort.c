#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char sort(char a[], int head, int tail);
void swap(char *a, char *b);

int
main() {
	char *a = "saheufhasdjhaflehf";
	int n = strlen(a);
	a = sort(a, 0, --n);
	printf("%s\n", a);
	return 0;
}


char *sort(char *a, int head, int tail) {

	if ((tail-head) == 1) {
		if (*a[head] > *(a[tail])) swap(a[head], a[tail]);
	} else {
		int t = (head+tail)/2;
		int i = -1;
		int j = n;

		while (i < j) {
			while (*(a+(++i)) < t);
			while (*(a+(--j)) > t);
			if (i < j) swap(a+i, a+j);
			else if (i == j) {
				sort(a, i);
				sort(a+i+1, n-i-1);

			} else {
				sort(a, j+1);
				sort(a+i, n-i);
			}
			
		}
	}
	return a;
}

void swap(char *a, char *b) {
	char *temp = a;
	a = b;
	b = temp;
}

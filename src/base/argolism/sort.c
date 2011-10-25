#include <stdio.h>

#define LEN 10 



int *quick_sort(int array[], int head, int tail); 
void display(int array[], int len);

int
main() {
	
	int array[LEN] = {14,2,21,5,37, 9, 12, 3, 47, 22};
	int *array_sort = quick_sort(array, 0, LEN-1);
	display(array, LEN);
	return 0;
}


int *quick_sort(int array[], int head, int tail) {

	int x = array[head];
	int i = head;
	int j = tail;
	
	while (1) {
		int temp;
		while (array[i] < x) i++;
		while (x < array[j]) j--;
		if (i>=j) break;
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
		i++;
		j--;
	}
	display(array, LEN);//for degug

	if (head < i-1) {
		quick_sort(array, head, i-1);
	}
	if (j+1 < tail) {
		quick_sort(array, j+1, tail);
	}
	return array;
}

void display(int array[], int len) {
	int i;
	for(i=0; i<len; i++)
		printf("%4d", array[i]);
	printf("\n");
}


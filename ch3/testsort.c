#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "sort.h"
int main(void)
{
	srand(time(0));
	int i;
	int n = 7;
	printf("%d elements to sort\n", n);
	int v[n];
	printf("Unsorted: ");
	for (i = 0; i < n; ++i) {
		v[i] = rand() % 100;
		printf("%d | ", v[i]);
	}	
	printf("\n");
	
	clock_t start = clock();
	shellsort(v, n);
	clock_t end = clock();
	printf("Sorted: ");

	for (i = 0; i < n; ++i) {
		printf("%d | ", v[i]);
	}
	printf("\n");
	printf("%.7f ms\n", (double)(end - start) \
		       / CLOCKS_PER_SEC * 1000.0 );	

	return 0;
}

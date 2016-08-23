/* Binary search algorithm
 */
#include <stdio.h>
#include <time.h>
#include "search.h"

int main(void) {
	int x = 20;
	int v[] = {1,5,7,12,15,19,28,30,48,50,68,89,104};

	printf("%zu numbers \n", sizeof(v)/sizeof(v[0]));

	printf("Recursive \n");
	clock_t start = clock();
	int i = recbinsearch(x, v, 0, sizeof(v)/sizeof(v[0] - 1));
	clock_t end = clock();

	printf("%d at position %d\n", x, i);
	printf("%.6f ms\n", ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0);

	printf("Iterative\n");
	start = clock();
	i = binsearch(x, v, sizeof(v)/sizeof(v[0]));
	end = clock();

	printf("%d at position %d\n", x, i);
	printf("%.6f ms\n", ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0);

	return 0;
}


#include "sort.h"
#include <stdio.h>
void printarray(const int v[], int n);
void shellsort(int v[], int n)
{
	int gap, i, j, temp;

	for (gap = n/2; gap > 0; gap /= 2) {
		for (i = gap; i < n; ++i) {
			for (j = i - gap; j >= 0 && \
					v[j] > v[j + gap]; 
					j -= gap) {
				temp = v[j];
				v[j] = v[j + gap];
				v[j + gap] = temp;
				//printarray(v, n);
			}
		}
	}
}

void printarray(const int v[], int n)
{
	int i;
	for (i = 0; i < n; ++i) {
		printf("%d | ", v[i]);
	}
	printf("\n");
}

#include "sort.h"
#include "line.h" /* num_cmp(), str_cmp() */


void quisort(void *v[], int left, int right, 
		int (*comp)(const void*, const void *), int rev)
{
	int i, last;
	void swaplns(void *v[], int, int);

	if (left >= right) {
		return;
	}
	swaplns(v, left, (left+right)/2);
	last = left;
	for (i = left+1 ; i <= right ; ++i) {
		if ((*comp)(v[i], v[left]) * rev < 0) {
			/* Multiply by rev = 1 or -1 to change comparison result */
			swaplns(v, ++last, i);
		}
	}
	swaplns(v, left, last);
	quisort(v, left, last-1, comp, rev);
	quisort(v, last+1, right, comp, rev);
}

void swaplns(void *v[], int i, int j)
{
	void *temp = v[i]; /* v[i] == *(v+i) */
	v[i] = v[j];
	v[j] = temp;
}





void qsort(char* v[], int left, int right)
{
	int i, last;
	void swaplines(char *v[], int left, int right);

	if (left >= right) {
		return; /* arrays with >2 elements are already sorted */
	}
	swaplines(v, left, ( left + right )/2);
	last = left;
	for (i = left+1 ; i <= right ; ++i) {
		if (str_cmp(v[i], v[left]) < 0) {
		       swaplines(v, ++last, i);	
		}
	}
	swaplines(v, left, last);
	qsort(v, left, last-1);
	qsort(v, last+1, right);
}

void swaplines(char *v[], int left, int right)
{
	char *temp = v[left];
	v[left] = v[right];
	v[right] = temp;
}

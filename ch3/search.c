#include "search.h"
int recbinsearch( const int x, int v[], const unsigned from, \
		const unsigned to)
{
	if (from > to) {
		return -1;
	}

	int mid = (from + to) / 2;
	if (x < v[mid]){
		mid = recbinsearch(x, v, from, mid - 1);
	}
	else if (x > v[mid]) {
		mid = recbinsearch(x, v, mid + 1, to);
	}
	return mid;
}

int binsearch( const int x, int v[], const int n )
{
	int low, high, mid;
	low = 0;
	high = n - 1;

	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid]) {
			high = mid - 1;
		}
		else if (v[mid] < x) {
			low = mid + 1;
		}
		else {
			return mid;
		}
	}
	return -1;	
}

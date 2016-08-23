#include <stdio.h>
unsigned int invertbits(unsigned int x, int p, int n);
int main(void)
{
	unsigned int x = 0;
	int pos = 0;
	int nBits = 9;
	printf("%d\n", invertbits(x, pos, nBits ));

	return 0;
}

unsigned int invertbits(unsigned int x, int p, int n)
{
	return x ^ (~(~0 << n) << p);
}


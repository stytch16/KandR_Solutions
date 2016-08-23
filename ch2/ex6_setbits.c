#include <stdio.h>
#include <math.h>
unsigned int setbits(unsigned int x, const int pos,\
	       const int nBits, unsigned int y);

int main(void)
{
	unsigned int x;
	unsigned int y;

	x = 93;
	y = 48;
	printf("%d\n", setbits(x, 3, 6, y));

	return 0;
}

unsigned int setbits(unsigned int x, const int pos,\
	       const int nBits, unsigned int y)
{
	unsigned int z = ~(~0 << nBits) << pos;
	return (y & z) | (x & ~z);
}

#include <stdio.h>
unsigned int rightrot(unsigned int x, int n);
unsigned int rightrot1(unsigned int x, int n);
int wordlength(void);
int main(void)
{
	unsigned int x = 230;
	int n = 5;
	printf("%d\n", rightrot(x, n));
	return 0;
}

unsigned int rightrot(unsigned int x, int n)
{

	int i;
	for (i = 0; i < n; ++i) {
		if (x & 1) {
			printf("Rotating 1\n");
			x = x >> 1;
			x = x |\
			    (~((unsigned)~0>>1)); 
		}
		else{
			printf("Rotating 0\n");
			x = x >> 1;
		}
	}
	return x;
}

unsigned int rightrot1(unsigned int x, int n)
{
	int wordlength(void);
	unsigned int rbits;

	printf("Word length of host machine = %d\n", \
			wordlength() );
	if (( n = n % wordlength() ) > 0 ) {
		rbits = ~(~0 << n) & x;
		rbits = rbits << (wordlength() - n + 1);
		x = x >> n;
		x = x | rbits;
	}
	return x;
}

int wordlength(void)
{
	int i;
	unsigned v = ~0;
	for (i = 0; (v = (v >> 1)) > 0; ++i);
	return i;
}
		

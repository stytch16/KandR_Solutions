#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

/* Function macro */
#define abs(x) ( (x) < 0 ? -(x) : (x) )

void itoa(int n, char s[]);
void reverse(char s[]);
void swap(char s[], unsigned int i, unsigned int j);

int main(void)
{
	int n = -2147483648;
	char s[MAXLINE];
	itoa(n, s);
	printf("%s\n", s);
	return 0;
}

void itoa(int n, char s[])
{
	int i;
	int sign;
	
	i = 0;
	sign = n;

	do {
		s[i++] = abs( n % 10 ) + '0';
		printf("%d\n", abs(n%10));
	} while ((n /= 10) != 0);

	if (sign < 0){
		s[i++] = '-';
	}
	s[i] = '\0';
	reverse(s);
}

void reverse(char s[])
{
	int i, j;
	for (i = 0, j = strlen(s) - 1; i < j; ++i, --j)
	{
		swap(s, i, j);
	}
}

void swap(char s[], unsigned int i, unsigned int j)
{
	int c = s[i];
	s[i] = s[j];
	s[j] = c;
}

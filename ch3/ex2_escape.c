#include <stdio.h>
#define MAXLINE 1000
void escape(char dest[], const char source[]);
int main(void)
{
	int i;
	int c;
	char s[MAXLINE];
	for (i = 0;( c = getchar() ) != EOF; ++i) {
		s[i] = c;
	}	

	char t[MAXLINE];
	escape(t, s);

	printf("%s\n", t);
	return 0;
}

void escape(char dest[], const char source[]) {
	int i, j;
	for (i = 0, j = 0; source[i] != '\0'; ++i)
	{
		switch (source[i]) {
			case '\n':
			       	dest[j++] = '\\';
			       	dest[j++] = 'n';
				break;
			case '\t':
			       	dest[j++] = '\\';
			       	dest[j++] = 't';
				break;
			case '\\':
			       	dest[j++] = '\\';
			       	dest[j++] = '\\';
				break;
			case '\b':
				dest[j++] = '\\';
				dest[j++] = 'b';
			default:
				dest[j++] = source[i];
				break;
		}
	}
	dest[j] = '\0';
}

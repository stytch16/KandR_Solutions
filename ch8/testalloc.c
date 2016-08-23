#include <stdio.h>
#include "alloc.h"

int main(void)
{
	char* test, *p;
	char abc;
	char* test2;
	char _012;
	test = (char *)my_malloc(sizeof(char) * 128);
	for (p = test, abc = 'a'; abc <= 'z'; ++p, ++abc) {
		*p = abc;
	}
	*p = '\0';
	test2 = (char *)my_malloc(sizeof(char) * 200);
	for (p = test2, _012 = '0' ; _012 <= '9' ; ++p, ++_012) {
		*p = _012;
	}
	*p = '\0';
	printf("GOT |%s|\n", test);
	printf(" AND |%s|\n", test2);
	my_free(test);
	my_free(test2);
	/* after freeing, what happens?? */
	test = (char *)my_malloc(sizeof(char) * 1024);
	/* do operations */
	my_free(test);
	return 0;
}

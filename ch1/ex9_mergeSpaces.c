#include <stdio.h>

int main(void)
{
	int prev, next;
	
	for (prev = '\n'; (next = getchar()) != EOF; prev = next){
		if (next != ' ' || prev != next) {
			putchar(next);
		}
	}

	return 0;
}

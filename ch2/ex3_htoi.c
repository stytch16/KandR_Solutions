/* Program to convert a string of hexdecimal digits into its equivalent integer value 
 * including an optional 0x or 0X
 *
 * e.g. 
 * >> '0x10f'
 * >>  271
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "line.h"

#define HEX_BASE 16
#define MAX_LENGTH 8  /* ULONG_MAX = 2^32-1 = 16^8-1. 
			 Set max length of input to 8 - 1 = 7
			 such that 16^7 + ... < ULONG_MAX */
#define MAX_LINE 1000

unsigned long htoi(const char s[]);

int main(void)
{
	char line[MAX_LINE];

	while ( getLine(line, MAX_LINE) > 0 ) {
		printf("%lu\n", htoi(line));	
	}
	return 0;
}

unsigned long htoi(const char s[]) 
{
	unsigned long dec = 0ul;
	char hex[MAX_LENGTH];
	reverse(s, hex);
	
	strip(hex);

	int i;
	for (i = 0; hex[i] != 'x' && hex[i] != '\0'; ++i) {
		if (isdigit(hex[i])) {
			dec += (pow(16, i) * (hex[i] - '0'));
		}
		else {
			dec += (pow(16, i) * (hex[i] - 'a' + 10));
		}
	}
	return dec;
}

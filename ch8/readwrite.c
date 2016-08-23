/* Purpose: Access read & write system calls
 * Input: 1. File Descriptor
 *               Small non-neg int to identify opened file
 *               Like a FILE *
 *               0, 1, 2 = stdin, stdout, stderr
 *        2. Char array, buffer for holding file data
 *        3. Number of bytes to be read/ written
 * Output: 
 *     - read() returns the number of bytes successfully read
 *     from the file. It will be <= nbytes requested.
 *     A return value of 0 indicates EOF reached. -1 
 *     indicates error reading.
 *     - write() returns number of bytes successfully
 *     transferred
 * Invariant (if any): Any number of bytes can read or
 *                     written in one call. Multiple calls
 *                     will pick up where the previous ones
 *                     left off. */

#include <stdio.h>
#include <unistd.h>
/* http://pubs.opengroup.org/onlinepubs/7908799/xsh/read.html */
/* http://pubs.opengroup.org/onlinepubs/7908799/xsh/write.html */
#define BUFSZ 1024

/* Read from stdin, write to stdout */
int main(void)
{
	char buf[BUFSZ]; /* BUFSZ included in some header */
	int n; /* n bytes read */
	while ( (n = read(0, buf, BUFSZ)) > 0) {
		write(1, buf, n);
	}
	return 0;
}

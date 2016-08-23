#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFSZ 1024
#define PERMS 0666 /* RW for owner, group, others */

/* for fcntrl.open()
 * http://man7.org/linux/man-pages/man2/open.2.html */
int main(int argc, char *argv[])
{
	int fd; /* file descriptor */
	int fdwrite = 1; /* file descriptor for writing */
			/* set to default 1 for stdout */
	int i = 0; /* argv index */
	char buf[BUFSZ]; /* read file data */
	ssize_t filelen; /* length of read file */

	if (argc == 1) {
		fprintf(stderr, "cat [-o] file1 file2 ...\n");
		exit(1);
	}

	if ( ! (strcmp(argv[1], "-o"))) {
		if ( (fdwrite = creat(argv[2], PERMS)) < 0){
			perror(argv[2]);
		} else {
			i = 2; /* file to be read is at index 3 now*/
		}
	}	
	while (argv[++i]) {
		if ((fd = open(argv[i], O_RDONLY, 0)) < 0) {
			perror(argv[i]);
		} else {
			while ( (filelen = read(fd, buf, BUFSZ)) > 0) {
				if (write(fdwrite, buf, filelen) != filelen) {
					perror(argv[i]);
				}
			}
		}
		close(fd);
	}
	close(fdwrite);
	exit(0);
}

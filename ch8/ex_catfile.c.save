#include "fio.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
	_FILE *fp, *ofp;
	void filecopy( _FILE *, _FILE *);
	
	ofp = _fopen("outtest.txt", "w");

	if (argc == 1) {
		filecopy(_stdin, ofp);
	} else {
		while (--argc > 0) {
			if (!(fp = _fopen(*++argv, "r"))) {
				exit(1); /* signal failure */
			} else {
				filecopy(fp, ofp);
				_fclose(fp);
			}
		}
	}
	_fclose(ofp);
	exit(0);
}

void filecopy(_FILE *ifp, _FILE *ofp)
{
	int c;
	while ( ( c = _getc(ifp) ) != _EOF) {
		/* EOF is returned if an EOF is reached by the
		 * read function. EOF is not written to the buffer
		 * stream though */
		_putc(c, ofp);
	}
}

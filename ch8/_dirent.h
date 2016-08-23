
#define NAME_MAX 14 /* longest filename length - sys dependent */
typedef struct  {
	long ino; /* inode number */
	char name[NAME_MAX + 1]; /* filename */
} Dirent;

typedef struct  {
	int fd; /* file descriptor */
	Dirent d; /* directory entry */
} _Dir; /* analagous to FILE but for directories */

_Dir *_opendir(char *dirname);
Dirent *_readdir(_Dir *dfd);
void _closedir(_Dir *dfd);


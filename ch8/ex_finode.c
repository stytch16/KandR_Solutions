#define _GNU_SOURCE
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#define MAXSTREAM 1024
typedef short RC; /* return code */

RC get_inode(char *);
RC dirwalk(char *, short(*fn)(char *));
int main(int argc, char *argv[])
{
	if (argc == 1) {
		get_inode(".");
	} else {
		while (--argc > 0) {
			if(get_inode(*++argv) == -1) {
				fprintf(stderr, "%s: could not get inode entry\n", *argv);
			}
		}
	}
	return 0;
}

RC get_inode(char *name) 
{
	struct stat stbuf;
	if (stat(name, &stbuf) == -1) {
		perror(name);
		return -1;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
		if (dirwalk(name, get_inode) ) { /* recursive walk */
			fprintf(stderr, "failed to walk through %s\n", name);
		}
	}
	fprintf(stdout, "%s\n"
			"-->SN: %lu\n"
			"-->SIZE: %lu bytes\n"
			"-->LAST ACCESSED: %s"
			"-->LAST MODIFIED: %s"
			"-->LAST INODE CHANGED: %s\n", 
			name,  
			stbuf.st_ino,
			stbuf.st_size, 
			asctime(gmtime(&stbuf.st_atime)), 
			asctime(gmtime(&stbuf.st_mtime)), 
			asctime(gmtime(&stbuf.st_ctime)));
	return 0;
}

RC dirwalk(char *dir, short(*fn)(char *))
{
	char name[MAXSTREAM];
	struct dirent *dir_entry;
	DIR *dir_file;

	if ((dir_file = opendir(dir)) == NULL) {
		perror(dir);	
		return -1;
	}
	/* readdir returns a pointer to dir_entry at current position of directory stream
	 * specified by dir_file. It will position to the pointer to the next dir_entry until EOF -> NULL  */
	while ( (dir_entry = readdir(dir_file)) != NULL) {
		if (!strcmp(dir_entry->d_name, ".") || !strcmp( dir_entry->d_name, "..")) {
			continue; /* skip over current dir file and parent dir file */	
		}
		if (strlen(name) + strlen(dir_entry->d_name) + 2 > sizeof name) {
			fprintf(stderr, "error: %s/%s exceeds memory space\n", name, dir_entry->d_name);
		} else {
			sprintf(name, "%s/%s", dir, dir_entry->d_name); 
			(*fn)(name);
		}
	}
	closedir(dir_file);
	return 0;
}

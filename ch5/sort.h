#ifndef SORT
#define SORT 

void quisort(void *v[], int left, int right, int (*comp)(const void *, const void *), int rev);
/* fourth parameter is a function ptr */
/* int (*comp)(void *, void *) <--- comp is ptr to function with arguments, */
/* void * & void *, and returns an int */

void qsort(char* lineptr[], int left, int right);

#endif /* ifndef SORT */

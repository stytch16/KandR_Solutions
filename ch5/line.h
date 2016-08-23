#ifndef LINE
#define LINE 

void str_cat(char* dest, char* source);
int str_end(char *str, char *sub);
void str_copy(char *dest, char *source);
void str_ncopy(char *dest, const char *source, int n);
void str_ncat(char *dest, const char *source, int n);
int str_cmp(const char *s, const char *t);
int str_ncmp(const char *s, const char *t, int n);
int get_line(char *s, int max);
int atoi(const char *a);
double atof(const char *a);
char* itoa(char *a, int n);
char* reverse(char *start, char *end) ;
void swap(char *s, char *t);
int str_index(char *str, char *sub);

#endif /* ifndef LINE */

#ifndef LINE_H
#define LINE_H 

void escape(char dest[], const char source[]);
void expand(const char shorthand[], char expanded[]);
void itoa(int n, char s[]);
void itoa_pad(int n, char s[], const int width);
void reverse(char s[]);
void swap(char s[], unsigned int i, unsigned int j);
int itob(int n, char s[], int b);

#endif /* ifndef LINE_H */

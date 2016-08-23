#ifndef LINE_H
#define LINE_H

int count(const char s[]);
int getLine(char line[], const int max);
void copy(char dest[], const char source[]);
int strip(char s[]);
void clear(char s[], const int len);
void reverse(const char s[], char r[]);
int prepend(char dest[], const char source[], const int lim);
int append(char dest[], const char source[], const int lim);
void printHiddenChar(const char s[]);
void squeeze(char s1[], const char s2[]);
int find(const char s[], const char c);
int any(const char s1[], const char s2[]);
#endif /* ifndef LINE_H



 */

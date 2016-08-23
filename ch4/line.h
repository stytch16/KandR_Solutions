#ifndef LINE_H
#define LINE_H 

int getLine(char s[], int lim);
/* Purpose: Get line input from user
 * Input: A string to store line input and the max storage limit of string
 * Output: Length of string
 */

void escape(char dest[], const char source[]);
void expand(const char shorthand[], char expanded[]);
void itoa(int n, char s[]);
void itoa_pad(int n, char s[], const int width);
void reverse(char s[]);
void swap(char s[], unsigned int i, unsigned int j);
int itob(int n, char s[], int b);

int strindex(const char s[], const char t[]);
/* Purpose: string t in string s?
 * Input: 2 strings
 * Output: returns pos of string t in s if found. otherwise, -1
 */

int rstrindex(const char s[], const char t[]);
/* Purpose: string t in string s?
 * Input: 2 string
 * Output: returns rightmost pos of string t in s if found. otherwise, -1
 */ 

int atoi(const char s[]);
/* Purpose: get int value of a string representation of a int
 * Input: string representing int e.g. -123
 * Output: int value
 * Invariant (if any): see atof */

double atof(const char s[]);
/* Purpose: get float value of a string representation of a float
 * Input: string representing float e.g. 1.23e-3
 * Output: float value
 * Invariant (if any): 1.23e-3 = 1 * 23/100 * 1/(10^3) */

#endif /* ifndef LINE_H */

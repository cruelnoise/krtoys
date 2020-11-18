#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 200000
#define MAXLEN 1000
#define MEMSIZE MAXLINES * MAXLEN

int read_lines(char *linebuf[], int nlines);
void write_lines(char *linebuf[], int nlines);

char *alloc(int n);
void afree(char *p);

void qsort(char *v[], int left, int right);

#include "main.h"

int get_line(char line[], int maxlen);

/* read lines until memory full or EOF */
int read_lines(char *linebuf[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    
    for (nlines = 0; (len = get_line(line, MAXLEN)) > 0; nlines += 1) {
        if (nlines >= maxlines || (p = alloc(len)) == 0) {
            return -1;
        }
        else {
            if (len == 1) {
                nlines -= 1;
                continue;
            }
            line[len - 1] = '\0'; // delete newline
            strcpy(p, line);
            linebuf[nlines] = p;
        }
    }
    return nlines;
}

/* write lines to stdout*/
void write_lines(char *linebuf[], int nlines) {
    int i;

    for (i = 0; i < nlines; i += 1) {
        printf("%s\n", linebuf[i]);
    }
}

int get_line(char line[], int maxlen) {
    int i, c;
    while ((isalnum(c = getchar())) == 0 && c != '\n' && c != EOF) {
        ;
    }
    if (isalnum(c)) {
        line[0] = c;
        i = 1;
    }
    else {
        i = 0;
    }
    for (; i < maxlen - 1 && (c = getchar()) != EOF && c != '\n'; i += 1) {
        line[i] = c;
    }
    if (c == '\n') {
        line[i] = c;
        i += 1;
    }
    line[i] = '\0';
    return i;
}


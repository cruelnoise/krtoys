#include "main.h"

int get_line(char line[], int maxlen);
void strcpy(char *to, char *from);

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
    
    for (i = 0; i < maxlen - 1 && (c = getchar()) != EOF && c != '\n'; i += 1) {
        line[i] = c;
    }
    if (c == '\n') {
        line[i] = c;
        i += 1;
    }
    line[i] = '\0';
    return i;
}

void strcpy(char to[], char from[]) {
    int i;
    for (i = 0; from[i] != '\0'; i += 1) {
        to[i] = from[i];
    }
    to[i] = '\0';
}

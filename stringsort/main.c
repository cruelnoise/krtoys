#include "main.h"

int main() {
    int nlines;
    char *linebuf[MAXLINES];
    
    if ((nlines = read_lines(linebuf, MAXLINES)) >= 0) {
        qsort(linebuf, 0, nlines - 1);
        printf("\n");
        write_lines(linebuf, nlines);
        return 0;
    }
    else {
        printf("error: input too big to sort.\n");
        return 1;
    }
}

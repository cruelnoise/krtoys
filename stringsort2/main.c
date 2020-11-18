#include "stringsort.h"

int read_lines(struct Bucket *);

int main() {
    struct Bucket *root;
    int nlines;

    root = NULL;
    if ((nlines = read_lines(root)) >= 0) {
        //traverse_tree(root, sort_bucket);
        traverse_tree(root, print_bucket);
        return 0;
    }
    else {
        printf("error: input too big to sort.\n");
        return 1;
    }
}

int get_line(char *, int);

int read_lines(struct Bucket *root) {
    int len, nlines;
    char line[MAXLEN];
    char *storage, *next, *last;

    fprintf(stderr, "Entering read_lines");

    storage = (char *)malloc(INITSTOR);
    next = storage;
    last = storage + sizeof(storage);

    for (nlines = 0; (len = get_line(line, MAXLEN)) > 0; nlines += 1) {
        fpritnf(stderr, "Entering loop %d\n", nlines);
        // throw away empty lines 
        if (len == 1) {
            nlines -= 1;
            continue;
        }
        // dynamic memory allocation woooo
        if ((next + len) > last) {
            if ((storage = (char *)realloc(storage, sizeof(storage) * 2)) == NULL) {
                return -1;
            }
            last = storage + sizeof(storage);
        }
        line[len - 1] = '\0'; // remove newline
        strcpy(next, line);
        if (add_to_tree(root, next) != 0) {
            return -1;
        }
        next = next + len;
    }
    fprintf(stderr, "Exiting read_lines");
    return nlines;
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

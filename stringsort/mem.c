#include "main.h"

static char membuf[MEMSIZE]; // storage for alloc
static char *memptr = membuf; // next free position

// retuns pointer to n characters of space.
char *alloc(int n) {
    if (membuf + MEMSIZE - memptr >= n) {
        // it fits
        memptr += n; // set memptr to first item after space allocated
        return memptr - n; // return the begginning of the allocated space
    }
    else {
        // not enough space
        return 0;
        }
}

// frees everything after p.
void afree(char *p) {
    if (p >= membuf && p < membuf + MEMSIZE) {
        memptr = p;
    }
}

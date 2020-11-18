#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 500 
#define INITSTOR 1000
#define INITBLOC 50 

struct Bucket {
    char id;
    struct Bucket *left;
    struct Bucket *right;
    char **holder;
    char **next;
};

void traverse_tree(struct Bucket *, void (*)(struct Bucket *));
void sort_bucket(struct Bucket *);
void print_bucket(struct Bucket *);
int add_to_tree(struct Bucket *, char *);

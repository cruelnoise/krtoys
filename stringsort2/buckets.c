#include "stringsort.h"

/* traverses the tree, applying method at each node. */
void traverse_tree(struct Bucket *n, void (*method)(struct Bucket *)) {
    if (n->left != NULL) {
        traverse_tree(n->left, method);
    }
    method(n);
    if (n->right != NULL) {
        traverse_tree(n->right, method);
    }
}

/* sorts the contents of the given bucket */
void sort_bucket(struct Bucket *n) {
}

/* prints the contents of the given bucket. */
void print_bucket(struct Bucket *n) {
    char **p;
    p = n->holder;
    while (p < n->next) {
        printf("%s\n", *p);
    }
}

int add_to_bucket(struct Bucket *, char *);
           
/* searches through the tree for a node with id == *s */
/* adds pointer to *s to the holder. */
/* if the appropriate bucket doesn't exist create it. */
int add_to_tree(struct Bucket *n, char *s) {
    if (n == NULL) {
        n = (struct Bucket *)malloc(sizeof(struct Bucket));
        n->id = *s;
        n->holder = (char **)malloc(INITBLOC * sizeof(char *));
        n->next = n->holder;
        n->left = NULL;
        n->right = NULL;
    }
    if (n->id == *s) {
        return add_to_bucket(n, s);
    }
    else if (n->id > *s) {
        return add_to_tree(n->left, s);
    }
    else {
        return add_to_tree(n->right, s);
    }
}

/* adds s to bucket n, dealing with memory */
int add_to_bucket(struct Bucket *n, char *s) {
    if (n->next - n->holder >= sizeof(n->holder)/sizeof(n->next)) {
        if ((n->holder = (char **)realloc(n->holder, sizeof(n->holder) * 2)) == NULL) {
                return -1;
        }
    }
    *n->next = s;
    n->next += 1;
    return 0;
}

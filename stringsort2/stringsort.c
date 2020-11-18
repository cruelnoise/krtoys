#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define PTRBLOC 250 
#define CHARBLOC 20000 
#define MAXLEN 200 

struct Bucket {
    char id;
    struct Bucket *left;
    struct Bucket *right;
    char **array;
    int next;
    int last;
};

struct Bucket *new_bucket(char c) {
    struct Bucket *n;
    n = (struct Bucket *)malloc(sizeof(struct Bucket));
    n->id = c;
    n->left = NULL;
    n->right = NULL;
    n->array = (char **) malloc(PTRBLOC * sizeof(char *));
    n->next = 0;
    n->last = PTRBLOC;
    return n;
}

/* drop (into) a bucket */
struct Bucket *drop_item(struct Bucket *n, char *s) {
    if (n == NULL) {
        n = new_bucket(*s);
    }
    if (n->id == *s) {
        if (n->next >= n->last) {
            n->last += n->last;
            n->array = (char **)realloc(n->array, n->last * sizeof(char *));
            if (n->array == NULL) {
                return NULL;
            } 
            
        }
        n->array[n->next] = s;
        n->next += 1;
    }
    else if (n->id > *s) {
        n->left = drop_item(n->left, s);
        if (n->left == NULL) {
            return NULL;
        }
    }
    else {
        n->right = drop_item(n->right, s);
        if (n->right == NULL) {
            return NULL;
        }
    }
    return n;
}

void traverse_tree(struct Bucket *n, void (*method)(struct Bucket *)) {
    if (n != NULL) {
        if (n->left != NULL) {
            traverse_tree(n->left, method);
        }
        method(n);
        if (n->right != NULL) {
            traverse_tree(n->right, method);
        }
    }
    else {
        printf("don't hand me that NULL shit\n");
    }
}

void swap(char *v[], int i, int j) {
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void my_qsort(char *v[], int left, int right) {
    int i, pivot;
    static int sorted;
    if (sorted == 0) {
        fprintf(stderr, "sorts: %6d", sorted);
    }
    fprintf(stderr, "\b\b\b\b\b\b");
    sorted += 1;
    fprintf(stderr, "%6d", sorted);
    if (left >= right) {
        return;
    }

    swap(v, left, (left + right) / 2);
    pivot = left;
    for (i = left + 1; i <= right; i += 1) {
        if (strcmp(v[i], v[left]) < 0) {
            pivot += 1;
            swap(v, pivot, i);
        }
    }
    swap(v, left, pivot);

    my_qsort(v, left, pivot - 1);
    my_qsort(v, pivot + 1, right);
}

void sort_bucket(struct Bucket *n) {
    int i, last, left, right;
    if (n != NULL) {
        my_qsort(n->array, 0, n->next - 1);
    }
}

void print_bucket(struct Bucket *n) {
    int i;
    if (n != NULL) {
        for (i = 0; i < n->next; i += 1) {
            printf("%s\n", n->array[i]);
        }
    } 
}
    
int get_line(char line[], int maxlen) {
    int i, c, tmp;
    while (isalnum(c = getchar()) == 0 && c != '\n' && c != EOF) {
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

struct Bucket *read_to_tree(struct Bucket *n) {
    int len, next, last;
    char *store, line[MAXLEN];
    
    store = (char *)malloc(CHARBLOC);
    next = 0;
    while ((len = get_line(line, MAXLEN)) > 0) {
        if (len == 1) {
            continue;
        }

        if (next + len >= CHARBLOC) {
            store = (char *)malloc(CHARBLOC);
            next = 0;
            if (store == NULL) {
                return NULL;
            }
        }
      
        line[len-1] = '\0';
        strcpy(&store[next], line);
        n = drop_item(n, &store[next]);
        next += len;
    }
    return n;
}              
        

int main() {
    struct Bucket *n;
    n = NULL;
    if ((n = read_to_tree(n)) != NULL) {
        traverse_tree(n, sort_bucket);
        printf("\n");
        traverse_tree(n, print_bucket);
    }
    else {
        printf("I guess we ran out of memory or something.\n");
        return 1;
    }
    return 0;
}

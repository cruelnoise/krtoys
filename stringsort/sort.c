#include "main.h"

void swap(char *v[], int i, int j);

void qsort(char *v[], int left, int right) {
    static int sorted;
    int i, last;
    if (sorted == 0) {
        fprintf(stderr, "lines sorted: 000000");
    }
    sorted += 1;
    fprintf(stderr, "\b\b\b\b\b\b%6d", sorted);

    if (left >= right) {
        return;
    }

    swap(v, left, (left + right) / 2); // swap middle to pivit
    last = left;
    for (i = left + 1; i <= right; i += 1) {
        // if i is greater than left 
        if (strcmp(v[i], v[left]) < 0) {
            // move the storage position one right
            last += 1;
            // swap to to the storage position
            swap(v, last, i);
        }
    }
    swap(v, left, last); // swap the pivot and the storage position?
                         // I guess just to make sure the pivot doesn't get
                         // stuck there?
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j) {
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

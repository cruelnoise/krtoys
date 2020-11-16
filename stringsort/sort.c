#include "main.h"

void swap(char *v[], int i, int j);
int strcmp(char str1[], char str2[]);

void qsort(char *v[], int left, int right) {
    int i, last;
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

int strcmp(char s[], char t[]) {
   int i;
   for (i = 0; s[i] == t[i]; i += 1) {
       if (s[i] == '\0') {
           return 0;
       }
   }
   return s[i] - t[i];
}

// solutions.c
#include "solutions.h"
#include <stdlib.h>

static int total = 0;

int running_total(int arg) {
    total += arg;
    return total;
}

int* reverse(int array[], int length) {
    int* reversed = (int*)calloc(length, sizeof(int));
    for (int i = 0; i < length; i++) {
        reversed[i] = array[length - 1 - i];
    }
    return reversed;
}

void reverse_in_place(int array[], int length) {
    for (int i = 0; i < length / 2; i++) {
        int temp = array[i];
        array[i] = array[length - 1 - i];
        array[length - 1 - i] = temp;
    }
}

int num_occurences(int array[], int length, int value) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (array[i] == value) {
            count++;
        }
    }
    return count;
}

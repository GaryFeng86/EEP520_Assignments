#include <stdlib.h>

static int total = 0; // Used for running_total, static so it retains state between calls

int running_total(int arg) {
    total += arg;
    return total;
}

int* reverse(int* array, int length) {
    int* reversed = (int*)calloc(length, sizeof(int));

    for (int i = 0; i < length; ++i) {
        reversed[i] = array[length - i - 1];
    }

    return reversed;
}

void reverse_in_place(int* array, int length) {
    for (int i = 0; i < length / 2; ++i) {
        int temp = array[i];
        array[i] = array[length - i - 1];
        array[length - i - 1] = temp;
    }
}

int num_occurrences(int* array, int length, int value) {
    int count = 0;

    for (int i = 0; i < length; ++i) {
        if (array[i] == value) {
            count++;
        }
    }

    return count;
}

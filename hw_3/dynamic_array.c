#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* private functions *********************************************************/

/* Position in the buffer of the array element at position index */
static int index_to_offset ( const DynamicArray * da, int index ) {
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const DynamicArray * da, int offset ) {
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( DynamicArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( DynamicArray * da ) {

    double * temp = (double *) calloc ( 2 * da->capacity, sizeof(double) );
    int new_origin = da->capacity - (da->end - da->origin)/2,
           new_end = new_origin + (da->end - da->origin);

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        temp[new_origin+i] = DynamicArray_get(da,i);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;

}

/* public functions **********************************************************/

DynamicArray *DynamicArray_new(void) {
    DynamicArray *da = (DynamicArray *)malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;
    da->buffer = (double *)calloc(da->capacity, sizeof(double));
    da->origin = da->capacity / 2;
    da->end = da->origin;

    numConstructedArrays++;

    return da;
}

void DynamicArray_destroy(DynamicArray * da) {
    free(da->buffer);
    da->buffer = NULL;
    return;
}

int DynamicArray_size(const DynamicArray * da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

char * DynamicArray_to_string(const DynamicArray * da) {
    assert(da->buffer != NULL);
    char * str = (char *) calloc (20,DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if ( DynamicArray_get(da,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } else {
            snprintf ( temp, 20, "%.5lf", DynamicArray_get(da,i) ); 
        }
        if ( i < DynamicArray_size(da) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }

    }
    str[j] = ']';
    return str;
}

void DynamicArray_print_debug_info(const DynamicArray * da) {

    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    printf ( "  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
      da->capacity, 
      da->origin, 
      da->end,
      DynamicArray_size(da));

    free(s);

}

void DynamicArray_set(DynamicArray * da, int index, double value) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if ( index >= DynamicArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

double DynamicArray_get(const DynamicArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= DynamicArray_size(da) ) {
        return 0;
    } else {
        return da->buffer[index_to_offset(da,index)];
    }
}

void DynamicArray_push(DynamicArray * da, double value ) {
    DynamicArray_set(da, DynamicArray_size(da), value );
}

void DynamicArray_push_front(DynamicArray * da, double value) {
    assert(da->buffer != NULL);
    while ( da->origin == 0 ) {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da,0,value);
}

double DynamicArray_pop(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, DynamicArray_size(da)-1);
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, 0);
    da->origin++;
    return value;    
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    assert(da->buffer != NULL);
    DynamicArray * result = DynamicArray_new();
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(da, i)));
    }
    return result;
}

DynamicArray *DynamicArray_subarray(DynamicArray *da, int a, int b) {
    assert(da->buffer != NULL);
    assert(b >= a);

    DynamicArray *result = DynamicArray_new();

    for (int i = a; i < b; i++) {
        DynamicArray_push(result, DynamicArray_get(da, i));
    }

    numConstructedArrays++;

    return result;
}

double DynamicArray_min(const DynamicArray *da) {
    assert(DynamicArray_size(da) > 0);
    double min_val = DynamicArray_get(da, 0);
    for (int i = 1; i < DynamicArray_size(da); ++i) {
        double current = DynamicArray_get(da, i);
        if (current < min_val) {
            min_val = current;
        }
    }
    return min_val;
}

double DynamicArray_max(const DynamicArray *da) {
    assert(DynamicArray_size(da) > 0);
    double max_val = DynamicArray_get(da, 0);
    for (int i = 1; i < DynamicArray_size(da); ++i) {
        double current = DynamicArray_get(da, i);
        if (current > max_val) {
            max_val = current;
        }
    }
    return max_val;
}

double DynamicArray_mean(const DynamicArray *da) {
    assert(DynamicArray_size(da) > 0);
    double sum = 0.0;
    for (int i = 0; i < DynamicArray_size(da); ++i) {
        sum += DynamicArray_get(da, i);
    }
    return sum / DynamicArray_size(da);
}

double DynamicArray_median(const DynamicArray *da) {
    assert(DynamicArray_size(da) > 0);
    DynamicArray *sorted = DynamicArray_copy(da);
    std::sort(sorted->buffer, sorted->buffer + DynamicArray_size(da));
    double median;
    if (DynamicArray_size(da) % 2 == 0) {
        // Even number of elements
        int mid = DynamicArray_size(da) / 2;
        median = (DynamicArray_get(sorted, mid - 1) + DynamicArray_get(sorted, mid)) / 2.0;
    } else {
        // Odd number of elements
        int mid = DynamicArray_size(da) / 2;
        median = DynamicArray_get(sorted, mid);
    }
    DynamicArray_destroy(sorted);
    return median;
}

double DynamicArray_sum(const DynamicArray *da) {
    double sum = 0.0;
    for (int i = 0; i < DynamicArray_size(da); ++i) {
        sum += DynamicArray_get(da, i);
    }
    return sum;
}
double DynamicArray_last(const DynamicArray *da) {
    assert(DynamicArray_size(da) > 0);
    return DynamicArray_get(da, DynamicArray_size(da) - 1);
}

double DynamicArray_first(const DynamicArray *da) {
    assert(DynamicArray_size(da) > 0);
    return DynamicArray_get(da, 0);
}

DynamicArray *DynamicArray_copy(const DynamicArray *da) {
    assert(da->buffer != NULL);

    DynamicArray *copy = DynamicArray_new();

    for (int i = 0; i < DynamicArray_size(da); ++i) {
        DynamicArray_push(copy, DynamicArray_get(da, i));
    }

    numConstructedArrays++;

    return copy;
}


DynamicArray *DynamicArray_range(double a, double b, double step) {
    assert(step != 0);

    DynamicArray *rangeArray = DynamicArray_new();

    if (a <= b) {
        for (double val = a; val <= b; val += step) {
            DynamicArray_push(rangeArray, val);
        }
    } else {
        for (double val = a; val >= b; val += step) {
            DynamicArray_push(rangeArray, val);
        }
    }

    numConstructedArrays++;

    return rangeArray;
}
DynamicArray *DynamicArray_concat(const DynamicArray *a, const DynamicArray *b) {
    assert(a->buffer != NULL && b->buffer != NULL);

    DynamicArray *concatenated = DynamicArray_new();

    for (int i = 0; i < DynamicArray_size(a); ++i) {
        DynamicArray_push(concatenated, DynamicArray_get(a, i));
    }

    for (int i = 0; i < DynamicArray_size(b); ++i) {
        DynamicArray_push(concatenated, DynamicArray_get(b, i));
    }

    numConstructedArrays++;

    return concatenated;
}

DynamicArray *DynamicArray_take(const DynamicArray *da, int n) {
    assert(da->buffer != NULL);

    DynamicArray *subArray = DynamicArray_new();

    if (n >= 0) {
        for (int i = 0; i < DynamicArray_size(da) && i < n; ++i) {
            DynamicArray_push(subArray, DynamicArray_get(da, i));
        }

        // Fill remaining elements with zero if needed
        for (int i = DynamicArray_size(subArray); i < n; ++i) {
            DynamicArray_push(subArray, 0.0);
        }
    } else {
        // Take from the end
        int startIdx = DynamicArray_size(da) + n;
        startIdx = (startIdx < 0) ? 0 : startIdx;

        for (int i = startIdx; i < DynamicArray_size(da); ++i) {
            DynamicArray_push(subArray, DynamicArray_get(da, i));
        }

        // Fill remaining elements with zero if needed
        for (int i = DynamicArray_size(subArray); i < -n; ++i) {
            DynamicArray_push(subArray, 0.0);
        }
    }

    numConstructedArrays++;

    return subArray;
}


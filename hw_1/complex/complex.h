// complex.h

#ifndef COMPLEX_H
#define COMPLEX_H

#include <math.h>

// Define a structure for complex numbers
struct Complex {
    double real;
    double im;
};

// Function prototypes
struct Complex add(struct Complex a, struct Complex b);
struct Complex negate(struct Complex a);
struct Complex multiply(struct Complex a, struct Complex b);
double magnitude(struct Complex a);

#endif


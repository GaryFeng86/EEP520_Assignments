#include <stdio.h>
#include <math.h>
#include "complex.h"

// Function to compare two doubles with a small epsilon
int compareDouble(double a, double b, double epsilon) {
    return fabs(a - b) < epsilon;
}

int main() {
    // Test add function
    struct Complex num1 = {1.0, 2.0};
    struct Complex num2 = {3.0, 4.0};
    struct Complex result = add(num1, num2);
    printf("Addition Test: %s\n", (compareDouble(result.real, 4.0, 0.0001) && compareDouble(result.im, 6.0, 0.0001)) ? "Passed" : "Failed");

    // Test negate function
    result = negate(num1);
    printf("Negate Test: %s\n", (compareDouble(result.real, -1.0, 0.0001) && compareDouble(result.im, -2.0, 0.0001)) ? "Passed" : "Failed");

    // Test multiply function
    result = multiply(num1, num2);
    printf("Multiplication Test: %s\n", (compareDouble(result.real, -5.0, 0.0001) && compareDouble(result.im, 10.0, 0.0001)) ? "Passed" : "Failed");

    // Test magnitude function
    double mag = magnitude(num1);
    printf("Magnitude Test: %s\n", compareDouble(mag, sqrt(5.0), 0.0001) ? "Passed" : "Failed");

    return 0;
}

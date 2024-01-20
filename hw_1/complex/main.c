#include <stdio.h>
#include "complex.h"

int main() {
    // Example usage of complex number functions
    struct Complex num1 = {1.0, 2.0};
    struct Complex num2 = {3.0, 4.0};

    // Addition
    struct Complex sum = add(num1, num2);
    printf("Sum: %.2f + %.2fi\n", sum.real, sum.im);

    // Negation
    struct Complex neg = negate(num1);
    printf("Negation: %.2f + %.2fi\n", neg.real, neg.im);

    // Multiplication
    struct Complex product = multiply(num1, num2);
    printf("Product: %.2f + %.2fi\n", product.real, product.im);

    // Magnitude
    double mag = magnitude(num1);
    printf("Magnitude: %.2f\n", mag);

    return 0;
}


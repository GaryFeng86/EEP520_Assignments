#include <iostream>
#include "typed_array.h"
#include "complex.h"

int main() {
    // Testing TypedArray class
    TypedArray<int> array;
    array.push(1);
    array.push(2);
    array.push_front(0);
    array.pop();
    array.pop_front();

    TypedArray<int> concatenated = array + array + array;

    std::cout << "Concatenated array: " << concatenated << std::endl;

    array.reverse();
    std::cout << "Reversed array: " << array << std::endl;

    // Testing Complex class
    Complex a(1, 2);
    Complex b(3, 4);

    Complex sum = a + b;
    Complex product = a * b;

    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Product: " << product << std::endl;

    return 0;
}

#include "gtest/gtest.h"
#include "typed_array.h"
#include "complex.h"

// Test TypedArray class methods

TEST(TypedArrayTest, PushAndPop) {
    TypedArray<int> array;
    array.push(1);
    array.push(2);
    EXPECT_EQ(array.get(0), 1);
    EXPECT_EQ(array.get(1), 2);
    array.pop();
    EXPECT_EQ(array.size(), 1);
}

TEST(TypedArrayTest, PushFrontAndPopFront) {
    TypedArray<int> array;
    array.push_front(1);
    array.push_front(2);
    EXPECT_EQ(array.get(0), 2);
    EXPECT_EQ(array.get(1), 1);
    array.pop_front();
    EXPECT_EQ(array.size(), 1);
}

TEST(TypedArrayTest, Concatenation) {
    TypedArray<int> array1, array2;
    array1.push(1);
    array1.push(2);
    array2.push(3);
    array2.push(4);
    TypedArray<int> concatenated = array1.concat(array2);
    EXPECT_EQ(concatenated.size(), 4);
    EXPECT_EQ(concatenated.get(0), 1);
    EXPECT_EQ(concatenated.get(1), 2);
    EXPECT_EQ(concatenated.get(2), 3);
    EXPECT_EQ(concatenated.get(3), 4);
}

TEST(TypedArrayTest, Reverse) {
    TypedArray<int> array;
    array.push(1);
    array.push(2);
    array.push(3);
    array.reverse();
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.get(0), 3);
    EXPECT_EQ(array.get(1), 2);
    EXPECT_EQ(array.get(2), 1);
}

// Test Complex class methods

TEST(ComplexTest, Addition) {
    Complex a(1, 2);
    Complex b(3, 4);
    Complex sum = a + b;
    EXPECT_EQ(sum.real(), 4);
    EXPECT_EQ(sum.imaginary(), 6);
}

TEST(ComplexTest, Multiplication) {
    Complex a(1, 2);
    Complex b(3, 4);
    Complex product = a * b;
    EXPECT_EQ(product.real(), -5);
    EXPECT_EQ(product.imaginary(), 10);
}

TEST(ComplexTest, Conjugate) {
    Complex a(1, 2);
    Complex conjugate = a.conjugate();
    EXPECT_EQ(conjugate.real(), 1);
    EXPECT_EQ(conjugate.imaginary(), -2);
}

TEST(ComplexTest, Equality) {
    Complex a(1, 2);
    Complex b(1, 2);
    EXPECT_EQ(a, b);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

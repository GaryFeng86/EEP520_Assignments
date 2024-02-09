#ifndef TYPED_ARRAY_H
#define TYPED_ARRAY_H

#include <stdexcept>
#include <iostream>

template <typename ElementType>
class TypedArray {
public:
    TypedArray();
    TypedArray(const TypedArray& other);
    TypedArray& operator=(const TypedArray& other);
    ~TypedArray();

    // Getters
    const ElementType& get(int index) const;
    int size() const;

    // Setters
    void set(int index, const ElementType& value);
    void push(const ElementType& value);
    void pop();
    void push_front(const ElementType& value);
    void pop_front();

    // Concatenation
    TypedArray concat(const TypedArray& other) const;

    // Reverse
    TypedArray& reverse();

    // Overloaded operators
    TypedArray operator+(const TypedArray& other) const;

private:
    ElementType* buffer_;
    int capacity_;
    int size_;
};

template <typename ElementType>
TypedArray<ElementType>::TypedArray()
        : buffer_(new ElementType[10]), capacity_(10), size_(0) {}

template <typename ElementType>
TypedArray<ElementType>::TypedArray(const TypedArray& other)
        : buffer_(new ElementType[other.capacity_]), capacity_(other.capacity_), size_(other.size_) {
    for (int i = 0; i < size_; ++i) {
        buffer_[i] = other.buffer_[i];
    }
}

template <typename ElementType>
TypedArray<ElementType>& TypedArray<ElementType>::operator=(const TypedArray& other) {
    if (this != &other) {
        delete[] buffer_;
        buffer_ = new ElementType[other.capacity_];
        capacity_ = other.capacity_;
        size_ = other.size_;
        for (int i = 0; i < size_; ++i) {
            buffer_[i] = other.buffer_[i];
        }
    }
    return *this;
}

template <typename ElementType>
TypedArray<ElementType>::~TypedArray() {
    delete[] buffer_;
}

template <typename ElementType>
const ElementType& TypedArray<ElementType>::get(int index) const {
    if (index < 0 || index >= size_) {
        throw std::range_error("Out of range index in array");
    }
    return buffer_[index];
}

template <typename ElementType>
int TypedArray<ElementType>::size() const {
    return size_;
}

template <typename ElementType>
void TypedArray<ElementType>::set(int index, const ElementType& value) {
    if (index < 0) {
        throw std::range_error("Negative index in array");
    }
    if (index >= capacity_) {
        ElementType* new_buffer = new ElementType[2 * capacity_];
        for (int i = 0; i < size_; ++i) {
            new_buffer[i] = buffer_[i];
        }
        delete[] buffer_;
        buffer_ = new_buffer;
        capacity_ *= 2;
    }
    buffer_[index] = value;
    size_ = std::max(size_, index + 1);
}

template <typename ElementType>
void TypedArray<ElementType>::push(const ElementType& value) {
    set(size_, value);
}

template <typename ElementType>
void TypedArray<ElementType>::pop() {
    if (size_ == 0) {
        throw std::range_error("Cannot pop from an empty array");
    }
    --size_;
}

template <typename ElementType>
void TypedArray<ElementType>::push_front(const ElementType& value) {
    if (size_ == capacity_) {
        ElementType* new_buffer = new ElementType[2 * capacity_];
        for (int i = 0; i < size_; ++i) {
            new_buffer[i + 1] = buffer_[i];
        }
        delete[] buffer_;
        buffer_ = new_buffer;
        capacity_ *= 2;
    } else {
        for (int i = size_; i > 0; --i) {
            buffer_[i] = buffer_[i - 1];
        }
    }
    buffer_[0] = value;
    ++size_;
}

template <typename ElementType>
void TypedArray<ElementType>::pop_front() {
    if (size_ == 0) {
        throw std::range_error("Cannot pop from an empty array");
    }
    for (int i = 0; i < size_ - 1; ++i) {
        buffer_[i] = buffer_[i + 1];
    }
    --size_;
}

template <typename ElementType>
TypedArray<ElementType> TypedArray<ElementType>::concat(const TypedArray& other) const {
    TypedArray result;
    for (int i = 0; i < size_; ++i) {
        result.push(buffer_[i]);
    }
    for (int i = 0; i < other.size_; ++i) {
        result.push(other.buffer_[i]);
    }
    return result;
}

template <typename ElementType>
TypedArray<ElementType>& TypedArray<ElementType>::reverse() {
    for (int i = 0; i < size_ / 2; ++i) {
        ElementType temp = buffer_[i];
        buffer_[i] = buffer_[size_ - i - 1];
        buffer_[size_ - i - 1] = temp;
    }
    return *this;
}
#endif
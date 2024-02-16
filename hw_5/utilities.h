#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <map>

template <typename ElementType>
class TypedArray {

public:

    TypedArray();
    TypedArray(const TypedArray& other);

    // Copy constructor
    TypedArray& operator=(const TypedArray& other);

    // Destructor
    ~TypedArray();

    // Getters
    ElementType &get(int index);
    ElementType &safe_get(int index) const;         // This is new. See Lecture5_Readme.md for a refresher.
    int size() const;

    // Setters
    void set(int index, ElementType value);

private:

    int capacity,
            origin,
            end;

    ElementType * buffer;

    const int INITIAL_CAPACITY = 10;

    int index_to_offset(int index) const;
    int offset_to_index(int offset) const;
    bool out_of_buffer(int offset) const;
    void extend_buffer(void);

};

std::map<std::string, int> occurrence_map(const std::string& path);

void sort_by_magnitude(std::vector<double> &vec);

template <typename ElementType>
void write_matrix_csv(const TypedArray<TypedArray<ElementType> >& matrix, const std::string& path);

template <typename ElementType>
TypedArray<TypedArray<ElementType> > read_matrix_csv(const std::string& path);

#endif // UTILITIES_H

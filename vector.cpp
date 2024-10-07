#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>

template <typename T>
class Vector {
private:
    T *elements;//pointer for the first element
    size_t capacity;//volume of the vector
    size_t size;//current size of the vector
    
    //expand capacity for vector
    void reserve(size_t newCapacity) {
        if(newCapacity > capacity) {
            T *newElements = new T[newCapacity];
            std::copy(elements, elements + size, newElements);
            delete[] elements;
            elements = newElements;
            capacity = newCapacity;
        }
    }
public:
    //construct function
    Vector() : elements(nullptr), capacity(0), size(0) {}

    //deconstuct function
    ~Vector() {
        delete[] elements;
    }

    //copy constructor
    Vector(const Vector &other) : capacity(other.capacity), size(other.size) {
        elements = new T[capacity];
        std::copy(other.elements, other.elements + size, elements);
    }

    //reconstruction for "="
    Vector& operator=(const Vector& other) {
        if(this != &other) {
            delete[] elements;
            capacity = other.capacity;
            size = other.size;
            elements = new T[capacity];
            std::copy(other.elements, other.elements + size, elements);
        }
        return *this;
    }

    void push_back(const T& value) {
        if(size == capacity) {
            reserve(capacity == 0 ? 1 : 2 * capacity);
        }
        elements[size++] = value;
    }

    size_t getSize() const {
        return size;
    }

    size_t getCapacity() const {
        return capacity;
    }

    //reconstruction for operator "[]"
    T& operator[](size_t index) {
        if(index >= size) {
            throw std::out_of_range("Index out of the range");
        }
        return elements[index];
    }

    const T& operator[](size_t index) const {
        if(index >= size) {
            throw std::out_of_range("Index out of the range");
        }
        return elements[index];
    }

    void insert(size_t index, const T& value) {
        if(index > size) {
            throw std::out_of_range("Index out of the range");
        }
        if(size == capacity) {
            reserve(capacity == 0 ? 1 : 2 * capacity);
        }
        for(size_t i = size; i > index; --i) {
            elements[i] = elements[i - 1];
        }
        elements[index] = value;
        ++size;
    }

    void pop_back() {
        if(size > 0) {
            --size;
        }
    }

    void clear() {
        size = 0;
    }

    //itrator
    T* begin() {
        return elements;
    }

    T* end() {
        return elements + size;
    }

    const T* begin() const {
        return elements;
    }

    const T* end() const {
        return elements + size;
    }

    void printElements() const {
        for(size_t i = 0; i < size; ++i) {
            std::cout << elements[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Vector<int> MyVector;
    int n;
    std::cin >> n;
    for(int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        MyVector.push_back(x);
    }
    for(auto it = MyVector.begin(); it < MyVector.end(); it++) {
        std::cout << it[0] << std::endl;
    }
    MyVector.insert(1,5);
    std::cout << MyVector.getCapacity() << MyVector.getSize() << std::endl;
    std::cout << MyVector[1];
    return 0;
}
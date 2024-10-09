#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <string>

template <typename T>
class Deque {
private:
    T* elements;
    size_t capacity;
    size_t frontIndex;
    size_t backIndex;
    size_t size;

private:
    void resize() {
        size_t newCapacity = capacity == 0 ? 1 : 2 * capacity;
        T* newElemetes = new T[newCapacity];
        size_t index = frontIndex;
        for(size_t i = 0; i < size; ++i) {
            newElemetes[i] = elements[index];
            index = (index + 1) % capacity;
        }
        delete[] elements;
        elements = newElemetes;
        capacity = newCapacity;
        frontIndex = 0;
        backIndex = size;
    }
public:
    Deque() : elements(nullptr), capacity(0), frontIndex(0), backIndex(0), size(0) {}

    ~Deque() {
        clear();
        delete[] elements;
    }

    void push_front(const T& value) {
        if(size == capacity) {
            resize();
        }
        frontIndex = (frontIndex - 1 + capacity);
        elements[frontIndex] = value;
        ++size;
    }

    void push_back(const T& value) {
        
    }
};
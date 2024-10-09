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
        frontIndex = (frontIndex - 1 + capacity) % capacity;
        elements[frontIndex] = value;
        ++size;
    }

    void push_back(const T& value) {
        if(size == capacity) {
            resize();
        }
        elements[backIndex] = value;
        backIndex = (backIndex + 1) % capacity;
        ++size;
    }

    void pop_front() {
        if(size == 0) {
            throw std::out_of_range("Deque is empty");
        }
        frontIndex = (frontIndex + 1) % capacity;
        --size;
    }

    void pop_back() {
        if(size == 0) {
            throw std::out_of_range("Deque is empty");
        }
        backIndex = (backIndex -  1 + capacity) % capacity;
        --size;
    }

    T& operator[](int index) {
        if(index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return elements[(frontIndex + index) % capacity];
    }

    size_t getSize() {
        return size;
    }

    void clear() {
        while(size > 0) {
            pop_front();
        }
    }

    void printElements() const {
        size_t index = frontIndex;
        for(size_t i = 0; i < size; ++i) {
            std::cout << elements[index] << " ";
            index = (index + 1) % capacity;
        }
        std::cout << std::endl;
    }
};

int main() {
    Deque<int> mydeque;
    mydeque.push_back(0);
    mydeque.push_front(1);
    auto x = mydeque[0];
    std::cout << x <<std::endl;
    mydeque.printElements();
    mydeque.pop_back();
    mydeque.printElements();
    mydeque.pop_front();
    mydeque.clear();
    return 0;
}
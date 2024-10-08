#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <string>

template <typename L>
class List {
private:
    struct Node
    {
        T *data;
        Node *next, *prev;

        //consrruct function of the list node
        Node(const T &value, Node *nextnode, Node *prevnode)
            :data(value), next(nextnode), prev(prevnode) {} 
    };
    Node *head;
    Node *tail;
    size_t size;

public:
    template <typename L>
    friend std::ostream &operator<<(std::ostream &os, const List<L> &pt)

public:
    //construct function of the list
    List() : head(nullptr), tail(nullptr), size(0) {}

    void clear() {
        while(head) {
            Node *temp = head;
            head = head->next;
            delete[] temp;
        }
        tail = nullptr;
        size = 0;
    }
    //deconstruction function of the list 
    ~List() {
        clear();
    }

    void push_back(const T &value) {
        Node* newNode = new Node(value, nullptr, tail);
        if(tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
        ++size;
    }

    void push_front(const T &value) {
        Node* newNode = new Node(value, head, nullptr);
        if(head) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
        ++size;
    }

    size_t getsize() {
        return size;
    }

    
};
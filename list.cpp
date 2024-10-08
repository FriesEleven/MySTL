#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <string>

template <typename T>
class List {
private:
    struct Node
    {
        T data;
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
    friend std::ostream &operator<<(std::ostream &os, const List<L> &pt);

public:
    //construct function of the list
    List() : head(nullptr), tail(nullptr), size(0) {}

    void clear() {
        while(head) {
            Node *temp = head;
            head = head->next;
            delete temp;
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

    T& operator[](size_t index) {
        Node* current = head;
        for(size_t i = 0; i < index; ++i) {
            if(!current) {
                throw std::out_of_range("Index out of the range");
            }
            current = current->next;
        }
        return current->data;
    }

    void pop_back() {
        if(size > 0) {
            Node* newTail = tail->prev;
            delete tail;
            tail = newTail;
            if(tail) {
                tail->next = nullptr;
            } else {
                head = nullptr;
            }
            --size;
        }
    }

    void pop_front() {
        if(size > 0) {
            Node* newHead = head->next;
            delete head;
            head = newHead;
            if(head) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
            --size;
        }
    }

    Node* begin() {
        return head;
    }

    Node* end() {
        return nullptr;
    }

    const Node* begin() const {
        return head;
    }

    const Node* end() const {
        return nullptr;
    }

    void printElements() {
        for(Node* current = head; current; current = current->next) {
            std::cout << current->data << " ";
        }
        std::cout << std::endl;
    }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const List<T> &pt) {
    for(typename List<T>::Node *current = pt.head; current; current = current->next) {
        os << "" << current->data;
    }
    os << std::endl;
    return os;
}

int main() {
    List<int> MyList;
    MyList.push_back(1);
    MyList.push_front(2);
    MyList.printElements();
    return 0;
}
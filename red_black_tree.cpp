#include <iostream>
#include <string>
#include <sstream>

enum Color {RED, BLACK};
template <typename Key, typename Value>
class RedBlackTree {
    class Node {
    public:
        Key key;
        Value value;
        Color color;
        Node *left;
        Node *right;
        Node *parent;

        Node(const Key &key, const Value &value, Color C, Node *p = nullptr) 
            : key(key), value(value), color(C), left(nullptr), right(nullptr), parent(p) {}
        
        Node() : color(Color::BLACK), left(nullptr), right(nullptr), parent(nullptr) {}
    };

};
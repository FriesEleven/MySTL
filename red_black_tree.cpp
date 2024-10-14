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

private:
    Node *root;
    size_t size;
    Node *Nil;

    Node *lookup(Kye key) {
        Node *cmpNode = root;
        while(cmpNode) {
           if(key < cmpNode->key) {
                cmpNode = cmpNode->left;
           } else if(key > cmpNode->key) {
                cmpNode = cmpNode->right;
           } else {
                return cmpNode;
           } 
        }
        return cmpNode;
    }

    void rightRotate(Node *node) {
        Node *l_son = node->left;
        node->left = l_son->right;
        if(l_son->right) {
            l_son->right->parent = node;
        }
        l_son->parent = node->parent;
        if(!node->parent) {
            root = l_son;
        } else if(node == node->parent->left) {
            node->parent->left = l_son;
        } else {
            node->parent->right = l_son;
        }
        l_son->right = node;
        node->parent = l_son;
    }

    void leftRotate(Node *node) {
        Node *r_son = node->right;
        node->right = r_son->left;
        if(r_son->left) {
            r_son->left->parent = node;
        }
        r_son->parent = node->parent;
        if(!node->parent) {
            root = r_son;
        } else if(node == node->parent->left) {
            node->parent->left = r_son;
        } else {
            node->parent->right = r_son;
        }
        r_son->left = node;
        node->parent = r_son;
    }

    void insertFixup(Node *target) {
        
    }
};
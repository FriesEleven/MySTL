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
       while(target->parent && target->parent->color == Color::RED) {
        if(target->parent == target->parent->parent->left) {
            Node *uncle = target->parent->parent->right;
            if(uncle && uncle->color == Color::RED) {
                target->parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                target->parent->parent->color = Color::RED;
                target = target->parent->parent;
            } else {
                if(target && target == target->parent->right) {
                    target = target->parent;
                    rightRotate(target);
                }
                target->parent->color == Color::BLACK;
                target->parent->parent->color = Color::RED;
                rightRotate(target->parent->parent);
            }
        } else {
            Node *uncle = target->parent->parent->left;
            if(uncle && uncle->color == Color::RED) {
                target->parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                target->parent->parent->color = Color::RED;
                target = target->parent->parent;
            } else {
                if(target && target == target->parent->left) {
                    target = target->parent;
                    rightRotate(target);
                }
                target->parent->color = Color::BLACK;
                target->parent->parent->color = Color::RED;
                leftRotate(target->parent->parent);
            }
        }
       }
       root->color = Color::BLACK;
    }

    void insertNode(cosnt Key &key, const Value &value) {
        Node *newNode = new Node(key, value, Color::RED);
        Node *parent = nullptr;
        Node *cmpNode = root;
        while(cmpNode) {
            parent = cmpNode;
            if(newNode->key < cmpNode->key) {
                cmpNode = cmpNode->left;
            } else if(newNode->key > cmpNode->key) {
                cmpNode = cmpNode->right;
            } else {
                delete newNode;
                return;
            }
        }
        size++;
        newNode->parent = parent;
        if(!parent) {
            root = newNode;
        } else if(newNode->key < parent->key) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
        insertFixup(newNode);
    }

    void inorderTraversal(Node *node) const {
        if(node) {
            inorderTraversal(node->left);
            std::cout << node->key << " ";
            std::cout << node->value << "";
            inorderTraversal(node->right);
        }
    }

    void replaceNode(Node *target, Node *newNode) {
        if(!target->parent) {
            root = target;
        } else if(target = target->parent->left) {
            target->parent->left = newNode;
        } else {
            target->parent->right = newNode;
        }
        if(newNode) {
            newNode->parent = target->parent;
        }
    }

    Node *findMinmunNode(Node *node) {
        while(node->left) {
            node = node->left;
        }
        return node;
    }

    Color getColor(Node *node) {
        if(node == nullptr) {
            return Color::BLACK;
        }
        return node->color;
    }
    
    void setColor(Node *node, Color color) {
        if(node == nullptr) {
            return;
        }
        node->color = color;
    }
    void removeFixup(Node *node) {
        
    }
};
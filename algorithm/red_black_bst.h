#ifndef RED_BLACK_BST_H
#define RED_BLACK_BST_H

#define RED true
#define BLACK false

template<class T>
class Node{
public:
    T key;
    int val;
    int num;
    Node *left, *right;
    bool color;

    Node(T key, int val, int num, bool color);

    ~Node();

    Node *leftRotate();

    Node *rightRotate();

    void reverseColor();
};

template<class T>
class RedBlackBST{
private:
    Node<T> *root;

    Node<T> *putKeyVal(Node<T> *node, int key, int val);

    Node<T> *deleteKey(Node<T> *node, int key);

    Node<T> *deleteMin(Node<T> *node, int key);

    bool isEmpty();

    static bool isRed(Node<T> *node);

    int size(Node<T> *node);

public:
    RedBlackBST();

    ~RedBlackBST();

    void putKeyVal(int key, int val);

    void deleteKey(int key);

    void deleteMin(int key);
};

#endif

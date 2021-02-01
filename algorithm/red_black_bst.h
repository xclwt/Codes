#ifndef RED_BLACK_BST_H
#define RED_BLACK_BST_H

#define RED true
#define BLACK false

class Node{
public:
    int key;
    int val;
    int num;
    Node *left, *right;
    bool color;

    Node(int key, int val, int num, bool color);

    ~Node();

    bool isRed();

    Node *leftRotate();

    Node *rightRotate();

    int size();

    void reverseColor();
};

class RedBlackBST{
private:
    Node *root;

    static Node *putKeyVal(Node *node, int key, int val);

public:
    void putKeyVal(int key, int val);

    void deleteKey(int key);
};

#include "red_black_bst.h"

template<class T>
Node<T>::Node(T key, int val, int num, bool color){
	this->key = key;
	this->val = val;
	this->num = num;
	this->color = color;
	this->left = nullptr;
	this->right = nullptr;
}

template<class T>
Node<T>::~Node(){}

template<class T>
Node<T>* Node<T>::leftRotate(){
    Node<T> *right = this->right;
    this->right = right->left;
    right->left = this;

    right->color = this->color;
    this->color = RED;

    right->num = this->num;
    this->num = 1 + this->left->size() + this->right->size();

    return right;
}

template<class T>
Node<T>* Node<T>::rightRotate(){
    Node<T> *left = this->left;
    this->right = left->right;
    left->right = this;

    left->color = this->color;
    this->color = RED;

    left->num = this->num;
    this->num = 1 + this->left->size() + this->right->size();

    return left;
}

template<class T>
void Node<T>::reverseColor(){
    this->color = RED;
    this->left->color = BLACK;
    this->right->color = BLACK;
}

template<class T>
RedBlackBST<T>::RedBlackBST(){

}

template<class T>
RedBlackBST<T>::~RedBlackBST(){

}

template<class T>
void RedBlackBST<T>::putKeyVal(int key, int val){
    root = putKeyVal(root, key, val);
    root->color = BLACK;
}

template<class T>
bool RedBlackBST<T>::isEmpty(){
    return root == nullptr;
}

template<class T>
bool RedBlackBST<T>::isRed(Node<T> *node){
    if (node == nullptr)
        return false;

    return node->color == RED;
}

template<class T>
int RedBlackBST<T>::size(Node<T> *node){
    if (node == nullptr)
        return 0;

    return node->num;
}

template<class T>
Node<T>* RedBlackBST<T>::putKeyVal(Node<T> *node, int key, int val){
    if (node == nullptr)
        return new Node<T>(key, val, 1, RED);

    int cmp = key - node->key;

    if (cmp < 0)
        node->left = putKeyVal(node->left, key, val);
    else if (cmp > 0)
        node->right = putKeyVal(node->right, key, val);
    else
        node->val = val;

    if (isRed(node->right) && !isRed(node->left))
        node = node->leftRotate();
    if (isRed(node->left) && isRed(node->left->left))
        node = node->rightRotate();
    if (isRed(node->left) && isRed(node->right))
        node->reverseColor();

    node->num = 1 + size(node->left) + size(node->right);

    return node;
}

template<class T>
void RedBlackBST<T>::deleteKey(int key){
    if (!isRed(root->left))
        ;
    root = deleteKey(root, key);
    if (!isEmpty())
        root->color = BLACK;
}

template<class T>
Node<T>* RedBlackBST<T>::deleteKey(Node<T> *node, int key){

}

template<class T>
void RedBlackBST<T>::deleteMin(int key){
    if (!isRed(root->left))
        ;
    root = deleteKey(root, key);
    if (!isEmpty())
        root->color = BLACK;
}

template<class T>
Node<T>* RedBlackBST<T>::deleteMin(Node<T> *node, int key){
    if (node->left == nullptr)
        return nullptr;

    if (!isRed(node->left) && !isRed(node->left->left))
        ;
}
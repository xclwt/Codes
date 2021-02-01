#include "red_black_bst.h"

Node::Node(int key, int val, int num, bool color){
	this->key = key;
	this->val = val;
	this->num = num;
	this->color = color;
	this->left = nullptr;
	this->right = nullptr;
}

Node::~Node(){}

bool Node::isRed(){
    return color;
}

Node* Node::leftRotate(){
    Node *right = this->right;
    this->right = right->left;
    right->left = this;

    right->color = this->color;
    this->color = RED;

    right->num = this->num;
    this->num = 1 + this->left->size() + this->right->size();
}

Node* Node::rightRotate(){
    Node *left = this->left;
    this->right = left->right;
    left->right = this;

    left->color = this->color;
    this->color = RED;

    left->num = this->num;
    this->num = 1 + this->left->size() + this->right->size();
}

int Node::size(){
    return this->num;
}

void Node::reverseColor(){
    this->color = RED;
    this->left->color = BLACK;
    this->right->color = BLACK;
}

void RedBlackBST::putKeyVal(int key, int val){
    root = putKeyVal(root, key, val);
    root->color = BLACK;
}

Node* RedBlackBST::putKeyVal(Node *node, int key, int val){
    if (node == nullptr)
        return new Node(key, val, 1, RED);

    int cmp = key - node->key;

    if (cmp < 0)
        node->left = putKeyVal(node->left, key, val);
    else if (cmp > 0)
        node->right = putKeyVal(node->right, key, val);
    else
        node->val = val;

    if(node->right->isRed() && !node->left->isRed())
        node = node->leftRotate();
    if(node->left->isRed() && node->left->left->isRed())
        node = node->rightRotate();
    if(node->left->isRed() && node->right->isRed())
        node->reverseColor();

    return node;
}

void RedBlackBST::deleteKey(int key){

}
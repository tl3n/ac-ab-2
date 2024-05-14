//
// Created by vasyl on 5/5/2024.
//

#include <iostream>
#include "BST.h"

using namespace std;

NodeBST::NodeBST() {
    this->data = 0.0;
    this->left = nullptr;
    this->right = nullptr;
}

NodeBST::NodeBST(float data) {
    this->data = data;
}

BST::BST() {
    root = NULL;
}

BST::BST(NodeBST* root) {
    this->root = root;
}

BST::~BST() {
    root = makeEmpty(root);
}

void BST::insert(float x) {
    root = insert(x, root);
}

void BST::remove(float x) {
    root = remove(x, root);
}

void BST::display() {
    inorder(root, 0);
    cout << endl;
}

NodeBST* BST::search(float x) {
    NodeBST* node = find(root, x);
    return node;
}

NodeBST* BST::getRoot() {
    return this->root;
}

NodeBST* BST::makeEmpty (NodeBST* t) {
    if(t == NULL)
        return NULL;
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    return NULL;
}

NodeBST* BST::insert(float x, NodeBST* t)
{
    if(t == NULL)
    {
        t = new NodeBST;
        t->data = x;
        t->left = t->right = NULL;
    }
    else if(x < t->data)
        t->left = insert(x, t->left);
    else if(x > t->data)
        t->right = insert(x, t->right);
    return t;
}

NodeBST* BST::findMin(NodeBST* t)
{
    if(t == NULL)
        return NULL;
    else if(t->left == NULL)
        return t;
    else
        return findMin(t->left);
}

NodeBST* BST::findMax(NodeBST* t) {
    if(t == NULL)
        return NULL;
    else if(t->right == NULL)
        return t;
    else
        return findMax(t->right);
}

NodeBST* BST::remove(float x, NodeBST* t) {
    NodeBST* temp;
    if(t == NULL)
        return NULL;
    else if(x < t->data)
        t->left = remove(x, t->left);
    else if(x > t->data)
        t->right = remove(x, t->right);
    else if(t->left && t->right)
    {
        temp = findMin(t->right);
        t->data = temp->data;
        t->right = remove(t->data, t->right);
    }
    else
    {
        temp = t;
        if(t->left == NULL)
            t = t->right;
        else if(t->right == NULL)
            t = t->left;
        delete temp;
    }

    return t;
}

void BST::inorder(NodeBST* t, int level) {
    if(t == NULL)
        return;

    inorder(t->left, level + 1);

    for (int i = 0; i < level; i++) {
        std::cout << "    ";
    }
    std::cout << t->data << std::endl;

    inorder(t->right, level + 1);
}

NodeBST* BST::find(NodeBST* t, float x) {
    if(t == NULL)
        return NULL;
    else if(x < t->data)
        return find(t->left, x);
    else if(x > t->data)
        return find(t->right, x);
    else
        return t;
}

void BST::printTree(NodeBST* root, int space)
{
    // Base case
    if (root == nullptr)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    printTree(root->right, space);

    // Print current node after spacing
    cout << endl;
    for (int i = 10; i < space; i++)
        cout << " ";
    cout << root->data << endl;

    // Process left child
    printTree(root->left, space);
}




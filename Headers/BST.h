//
// Created by vasyl on 5/5/2024.
//

#ifndef AC_LAB_3_BST_H
#define AC_LAB_3_BST_H

struct NodeBST {
    float data = 0.0;
    NodeBST* left = nullptr;
    NodeBST* right = nullptr;

    NodeBST();

    NodeBST(float data);
};

class BST {
public:
    BST();
    BST(NodeBST* root);
    ~BST();
    void insert(float x);
    void remove(float x);
    void display();
    NodeBST* search(float x);
    NodeBST* getRoot();
    void printTree(NodeBST* root, int space);

private:
    NodeBST* root;

    NodeBST* makeEmpty(NodeBST* t);
    NodeBST* insert(float x, NodeBST* t);
    NodeBST* findMin(NodeBST* t);
    NodeBST* findMax(NodeBST* t);
    NodeBST* remove(float x, NodeBST* t);
    void inorder(NodeBST* t, int level);
    NodeBST* find(NodeBST* t, float x);

};

#endif //AC_LAB_3_BST_H

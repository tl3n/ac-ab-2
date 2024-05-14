//
// Created by vasyl on 5/5/2024.
//

#ifndef AC_LAB_3_OPTIMALBSTSEARCH_H
#define AC_LAB_3_OPTIMALBSTSEARCH_H

#include <iostream>
#include <vector>
#include "BST.h"

using namespace std;

struct cell {
    float cost = 0.0;
    NodeBST* root;
};

float sum(float frequencies[], int i, int j);
BST findOptimalBST (float keys[], float frequencies[], int n);

#endif //AC_LAB_3_OPTIMALBSTSEARCH_H

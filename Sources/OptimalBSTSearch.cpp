//
// Created by vasyl on 5/5/2024.
//

#include "OptimalBSTSearch.h"

float sum(float frequencies[], int i, int j) {
    float sum = 0.0;
    for (int k = i; k <= j; ++k)
        sum += frequencies[k];

    return sum;
}

BST findOptimalBST (float keys[], float frequencies[], int n) {
    vector<vector<cell>> dp(n, vector<cell>(n, cell()));

    for (int i = 0; i < n; ++i) {
        dp[i][i].cost = frequencies[i];
        dp[i][i].root = new NodeBST(keys[i]);
    }

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            dp[i][j].cost = 9999.99;

            for (int k = i; k <= j; ++k) {
                float cost = ((k > i) ? dp[i][k - 1].cost : 0) +
                             ((k < j) ? dp[k + 1][j].cost : 0) +
                             sum(frequencies, i, j);

                if (cost < dp[i][j].cost) {
                    dp[i][j].cost = cost;
                    dp[i][j].root = new NodeBST(keys[k]);
                    dp[i][j].root->left = (k > i) ? dp[i][k - 1].root : nullptr;
                    dp[i][j].root->right = (k < j) ? dp[k + 1][j].root : nullptr;
                }
            }
        }
    }

    /*for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << dp[i][j].cost << " ";
        cout << '\n';
    }*/

    BST optimalBST(dp[0][n-1].root);
    return optimalBST;
}
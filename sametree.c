/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#include <stdbool.h>
#include <stdlib.h>

#define MAX_NODES 1000  // adjust if needed

bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    if (p == NULL && q == NULL)
        return true;
    else if (p && q) {
        if (p->val == q->val && isSameTree(p->left, q->left)  && isSameTree(p->right, q->right)){
            return true;
        }
        else{
            return false;
        }
    }
    return false;
}
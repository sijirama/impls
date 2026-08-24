#include "stdbool.h"
#include <stdatomic.h>

/**
 * Definition for a binary tree node.
 */

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool isChildrenSymmetric(struct TreeNode *child1, struct TreeNode *child2) {
    if (child1 == NULL && child2 == NULL) {
        return true;
    }
    if (child1 == NULL || child2 == NULL) {
        return false;
    }
    if (child1->val != child2->val) {
        return false;
    }
    return isChildrenSymmetric(child1->left, child2->right) &&
           isChildrenSymmetric(child1->right, child2->left);
}

bool isSymmetric(struct TreeNode *root) {
    if (root == NULL) {
        return true;
    }
    return isChildrenSymmetric(root->left, root->right);
}

#include "stdlib.h"
#include <stdio.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void getSortedArray(struct TreeNode *root, int *array, int *index) {
    if (root == NULL) {
        return;
    }

    if (root->left != NULL) {
        getSortedArray(root->left, array, index);
    }

    array[*index] = root->val;
    (*index)++;

    if (root->right != NULL) {
        getSortedArray(root->right, array, index);
    }
}

int minDiffInBST(struct TreeNode *root) {

    int array[1000];
    int index = 0;

    getSortedArray(root, array, &index);

    int mindiff = array[1] - array[0];
    int diff = 0;
    for (int i = 2; i < index; i++) {
        diff = array[i] - array[i - 1];
        mindiff = MIN(mindiff, diff);
    }
    return mindiff;
}

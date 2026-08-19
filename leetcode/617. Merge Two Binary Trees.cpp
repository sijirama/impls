#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

TreeNode *insert(TreeNode *root, int num) {
    TreeNode *node = new TreeNode(num);
    if (root == nullptr) {
        root = node;
        return root;
    }
    if (num <= root->val) {
        return root->left = insert(root->left, num);
    } else {
        return root->right = insert(root->right, num);
    }
}

TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2) {
    TreeNode *newroot = nullptr;
    if (root1 == nullptr && root2 == nullptr) {
        return newroot;
    }

    int val1 = (root1 != nullptr) ? root1->val : 0;
    int val2 = (root2 != nullptr) ? root2->val : 0;

    newroot = insert(newroot, val1 + val2);

    if (root1 != nullptr && root2 != nullptr) {
        newroot->left = mergeTrees(root1->left, root2->left);
        newroot->right = mergeTrees(root1->right, root2->right);
    } else if (root1 != nullptr) {
        newroot->left = mergeTrees(root1->left, nullptr);
        newroot->right = mergeTrees(root1->right, nullptr);
    } else {
        newroot->left = mergeTrees(nullptr, root2->left);
        newroot->right = mergeTrees(nullptr, root2->right);
    }

    return newroot;
}

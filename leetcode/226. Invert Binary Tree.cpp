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

TreeNode *invertTree(TreeNode *root) {
    if (root == nullptr) {
        return root;
    }

    swap(root->right, root->left);
    invertTree(root->left);
    invertTree(root->right);
    return root;
}

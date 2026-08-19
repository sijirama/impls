/*
    to validate a binary search tree, if you know what a binary search tree you
   know the limitations on a parent node and its child node and an Inorder
   Traversal of Valid BST is always strictly increasing array so thats how this
   one was solved, mucho gracias.
*/

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

vector<int> getArray(TreeNode *root) {
    vector<int> A, L, R, I;
    if (root == nullptr) {
        return A;
    }
    I.push_back(root->val);
    L = getArray(root->left);
    R = getArray(root->right);

    for (int i : L) {
        A.push_back(i);
    }
    for (int i : I) {
        A.push_back(i);
    }
    for (int i : R) {
        A.push_back(i);
    }
    return A;
}

bool isValidBST(TreeNode *root) {
    if (root == nullptr) {
        return false;
    }
    vector<int> Q = getArray(root);
    if (Q.size() == 1) {
        return true;
    }
    if (Q.size() < 2) {
        return false;
    }
    for (int i = 1; i < Q.size(); i++) {
        if (Q[i] <= Q[i - 1]) {
            return false;
        }
    }
    return true;
}

/*
 if (root == nullptr) {
        return false;
    }

    if (root->left == nullptr || root->right == nullptr) {
        return false;
    }

    if (!(root->right->val > root->val) || !(root->left->val < root->val)) {
        return false;
    }

    return isValidBST(root->left) || isValidBST(root->right);

*/

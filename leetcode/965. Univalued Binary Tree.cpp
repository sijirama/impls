#include <queue>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

bool isUnivalTree(TreeNode *root) {
    if (root == nullptr) {
        return true;
    }

    int NUMBER = root->val;
    std::queue<TreeNode *> Q;
    Q.push(root);
    while (!Q.empty()) {
        TreeNode *node = Q.front();
        Q.pop();
        if (node->val != NUMBER)
            return false;
        if (node->left)
            Q.push(node->left);
        if (node->right)
            Q.push(node->right);
    }

    return true;
}

#include <algorithm>
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

int minDepth(TreeNode *root) {
    if (!root) {
        return 0;
    }
    std::queue<TreeNode *> q;
    int depth = 0;
    q.push(root);
    while (!q.empty()) {
        int s = q.size();
        for (int i = 0; i < s; ++i) {
            TreeNode *temp = q.front();
            q.pop();
            if (!temp->left && !temp->right) {
                return depth + 1;
            }
            if (temp->left) {
                q.push(temp->left);
            }
            if (temp->right) {
                q.push(temp->right);
            }
        }
        ++depth;
    }
    return depth;
}

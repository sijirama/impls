#include <algorithm>
#include <iostream>
#include <queue>
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

vector<double> averageOfLevels(TreeNode *root) {
    vector<double> V;
    if (!root)
        return V;
    queue<TreeNode *> Q;
    Q.push(root);
    while (!Q.empty()) {
        int level = Q.size();
        double ans = 0;
        for (int i = 0; i < level; ++i) {
            TreeNode *temp = Q.front();
            Q.pop();
            if (!temp) {
                return V;
            }
            ans += temp->val;
            if (temp->left)
                Q.push(temp->left);
            if (temp->right)
                Q.push(temp->right);
        }
        V.push_back(ans / level);
    }

    // Check for values close to zero and set them to zero
    return V;
}

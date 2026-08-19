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

vector<vector<int>> levelOrderBottom(TreeNode *root) {
    vector<vector<int>> A;

    queue<TreeNode *> Q;
    Q.push(root);

    while (!Q.empty()) {
        int level = Q.size();
        vector<int> G;
        for (int i = 0; i < level; ++i) {
            TreeNode *temp = Q.front();
            Q.pop();
            if (!temp) {
                reverse(A.begin(), A.end());
                return A;
            }
            G.push_back(temp->val);
            if (temp->left)
                Q.push(temp->left);
            if (temp->right)
                Q.push(temp->right);
        }
        A.push_back(G);
    }
    reverse(A.begin(), A.end());
    return A;
}

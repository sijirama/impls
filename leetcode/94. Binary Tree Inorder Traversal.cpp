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

vector<int> postorderTraversal(TreeNode *root) {
    vector<int> V, L, R, Ans;
    if (root == nullptr) {
        return Ans;
    }

    L = postorderTraversal(root->left);

    V.push_back(root->val);

    R = postorderTraversal(root->right);

    for (int i : L) {
        Ans.push_back(i);
    }

    for (int i : V) {
        Ans.push_back(i);
    }

    for (int i : R) {
        Ans.push_back(i);
    }
    return Ans;
}

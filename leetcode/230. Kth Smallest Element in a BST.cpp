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

vector<int> BSTvalues(TreeNode *root) {
    vector<int> ans;
    if (root == nullptr) {
        return ans;
    }
    ans.emplace_back(root->val);

    // You need to concatenate the vectors returned by recursive calls.
    vector<int> leftValues = BSTvalues(root->left);
    vector<int> rightValues = BSTvalues(root->right);

    // Concatenate the vectors.
    ans.insert(ans.end(), leftValues.begin(), leftValues.end());
    ans.insert(ans.end(), rightValues.begin(), rightValues.end());

    return ans;
}

int kthSmallest(TreeNode *root, int k) {
    vector<int> lowest = BSTvalues(root);
    sort(lowest.rbegin(), lowest.rend());
    return lowest[lowest.size() - k];
}

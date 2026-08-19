#include <iostream>
#include <vector>

using namespace std;

class Node {
  public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val) { val = _val; }

    Node(int _val, vector<Node *> _children) {
        val = _val;
        children = _children;
    }
};

vector<int> preorder(Node *root) {
    vector<int> A, G, I;
    if (root == nullptr) {
        return A;
    }

    I.push_back(root->val);

    for (Node *temp : root->children) {
        vector<int> N;
        N = preorder(temp);
        for (int i : N) {
            G.push_back(i);
        }
    }
    for (int i : I) {
        A.push_back(i);
    }

    for (int i : G) {
        A.push_back(i);
    }

    return A;
}

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
#define show(x) std::cout << x << std::endl;

int pairSum(ListNode *head) {
    ListNode *temp = head;
    vector<int> A, B;
    while (temp != nullptr) {
        A.push_back(temp->val);
        temp = temp->next;
    }

    for (int i = 0; i < A.size() / 2; i++) {
        int g = A[i] + A[(A.size() - 1) - i];
        B.push_back(g);
    }

    int ans = B[0];

    for (int i = 1; i < B.size(); i++) {
        if (B[i] > ans) {
            ans = B[i];
        }
    }

    return ans;
}

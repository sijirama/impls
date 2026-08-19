#include <iostream>
#include <vector>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// int pow2(int base, int n) {
//     int ans = 1;
//     for (int i = 1; i <= n; ++i) {
//         ans *= base;
//     }
//     return ans;
// }

int pow(int base, int n) { return std::pow(base, n); }

int getDecimalValue(ListNode *head) {
    vector<int> vect;
    int ans = 0;
    ListNode *temp = head;
    int counter = 0;
    while (temp != nullptr) {
        vect.push_back(temp->val);
        temp = temp->next;
    }
    reverse(vect.begin(), vect.end());
    for (int i = 0; i < vect.size(); ++i) {
        ans += vect[i] * pow(2, counter);
        ++counter;
    }
    return ans;
}

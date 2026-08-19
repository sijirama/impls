#include <iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *middleNode(ListNode *head) {
    ListNode *temp = head;
    ListNode *temp2 = head;
    ListNode *ans = nullptr;
    int length = 0;
    while (temp != nullptr) {
        ++length;
        temp = temp->next;
    }
    if (length % 2 == 0) {
        length = (length / 2) + 1;
    } else {
        length = (length + 1) / 2;
    }
    int count = 0;
    while (temp2 != nullptr) {
        if (count == length - 1) {
            ans = temp2;
        }
        cout << temp2->val;
        temp2 = temp2->next;
        ++count;
    }
    return ans;
}

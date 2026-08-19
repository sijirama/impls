#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
#define show(x) std::cout << x << std::endl;

ListNode *deleteDuplicates(ListNode *head) {
    ListNode *curr = head;
    ListNode *prev = new ListNode(-101);

    if (!head)
        return head;

    while (curr->next != nullptr) {
        ListNode *nextNode = curr->next;
        if (curr->val == curr->next->val) {
            cout << curr->val << " " << curr->next->val;
            curr->next = curr->next->next;
            continue;
        }
        curr = nextNode;
    }

    return head;
}

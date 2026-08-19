#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

void deleteNode(ListNode *node) {
    node->val = node->next->val;
    node->next = node->next->next;
}

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

void insert(ListNode *&newhead, int val) {
    ListNode *temp = new ListNode(val);
    if (!newhead) {
        newhead = temp;
        return;
    }
    ListNode *head = newhead;
    while (head->next != nullptr) {
        head = head->next;
    }
    head->next = temp;
    return;
}

ListNode *removeElements(ListNode *head, int val) {
    ListNode *newHead = nullptr;
    ListNode *curr = head;
    while (curr != nullptr) {
        if (curr->val != val) {
            insert(newHead, curr->val);
        }
        curr = curr->next;
    }
    return newHead;
}



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

ListNode *push(ListNode *head, int data) {
    ListNode *node = new ListNode();
    node->val = data;
    node->next = nullptr;

    if (head == nullptr) {
        head = node;
        return head;
    }
    ListNode *temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = node;
    return head;
}

ListNode *oddEvenList(ListNode *head) {
    if (head == nullptr)
        return head;
    vector<int> A;
    while (head != nullptr) {
        A.push_back(head->val);
        head = head->next;
    }

    ListNode *newroot = nullptr;
    for (int i = 0; i < A.size(); i++) {
        if ((i + 1) % 2 != 0) {
            newroot = push(newroot, A[i]);
        }
    }
    for (int i = 0; i < A.size(); i++) {
        if ((i + 1) % 2 == 0) {
            newroot = push(newroot, A[i]);
        }
    }
    return newroot;
}

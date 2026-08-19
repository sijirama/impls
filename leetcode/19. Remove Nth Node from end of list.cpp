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

int getSize(ListNode *head) {
    int size = 0;
    while (head != nullptr) {
        ++size;
        head = head->next;
    }
    return size;
}

ListNode *removeNth(ListNode *head, int position) {
    ListNode *curr = head;
    ListNode *prev = nullptr;

    int pos = 0;
    while (curr != nullptr) {
        if (pos == position - 1) {
            if (curr->next) {
                prev = curr;
                curr = curr->next;
                prev->next = curr->next;
                delete curr;
                break;
            }
        }
        ++pos;
        curr = curr->next;
    }
    return head;
}

ListNode *removeNthFromEnd(ListNode *head, int n) {
    int size = getSize(head);
    int position = size - n;
    cout << position;
    if (position == 0) {
        ListNode *temp = head;
        head = temp->next;
        return head;
    }
    head = removeNth(head, position);
    return head;
}

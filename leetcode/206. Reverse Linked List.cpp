// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
};

ListNode *reverseList(ListNode *head) {
    ListNode *NewHead;
    ListNode *curr = head;
    ListNode *prev = nullptr;
    ListNode *nextNode;

    while (curr != nullptr) {
        nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }

    NewHead = prev;
    return NewHead;
}

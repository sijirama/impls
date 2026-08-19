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

// 1. get the elements in a vector
// 2. swap the required values
// 3. create a new List with the newly arranged values.

vector<int> getVectorFromList(ListNode *head) {
    vector<int> ans;
    if (head == nullptr) {
        return ans;
    }
    ListNode *temp = head;
    while (temp != nullptr) {
        ans.push_back(temp->val);
        temp = temp->next;
    }
    return ans;
}

void insert(ListNode *&head, int val) {
    ListNode *header = head;
    ListNode *temp = new ListNode(val);
    if (head == nullptr) {
        head = temp;
        return;
    }
    while (header->next != nullptr) {
        header = header->next;
    }
    header->next = temp;
}

void swapValue(vector<int> &que, int index) {
    int pos = index - 1;
    swap(que[pos], que[que.size() - index]);
}

ListNode *swapNodes(ListNode *head, int k) {
    ListNode *newHead = nullptr;
    vector<int> question = getVectorFromList(head);
    swapValue(question, k);
    for (auto i : question) {
        insert(newHead, i);
    }
    return newHead;
}

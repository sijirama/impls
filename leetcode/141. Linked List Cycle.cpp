#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

bool hasCycle(ListNode *head) {
    if (head == nullptr) {
        return false;
    }

    vector<ListNode *> V;

    while (head != nullptr) {
        bool it = count(V.begin(), V.end(), head);
        if (it) {
            return true;
        }
        V.push_back(head);
        head = head->next;
    }
    return false;
}

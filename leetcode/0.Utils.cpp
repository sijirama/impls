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

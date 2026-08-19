
/*
Given a sorted array of distinct integers and a target value, return the index
if the target is found. If not, return the index where it would be if it were
inserted in order.

You must write an algorithm with O(log n) runtime complexity.
*/
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

int searchInsert(vector<int> &nums, int target);

int main() {

    vector<int> question = {1, 3, 5, 6};
    int ans = searchInsert(question, 7);
    cout << ans;
}

int searchInsert(vector<int> &nums, int target) {

    vector<int>::iterator idx = find(nums.begin(), nums.end(), target);

    if (idx != nums.end()) {
        int index = distance(nums.begin(), idx);
        return index;
    } else {
        nums.push_back(target);
        sort(nums.begin(), nums.end());
        vector<int>::iterator idx = find(nums.begin(), nums.end(), target);
        int index = distance(nums.begin(), idx);
        return index;
    }
    return 0;
}

/*
Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You
may assume that the majority element always exists in the array.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int majorityElement(vector<int> &nums);

int main() {
    vector<int> question = {4, 5, 4};
    int num = majorityElement(question);
    cout << num << endl;
}

int majorityElement(vector<int> &nums) {
    sort(nums.rbegin(), nums.rend());
    // after the vector is sorted, the majority element will surely be the
    // nums[n/2] element
    return nums[nums.size() / 2];
}

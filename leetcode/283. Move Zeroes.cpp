/*
283. Move Zeroes
Companies
Given an integer array nums, move all 0's to the end of it while maintaining the
relative order of the non-zero elements. Note that you must do this in-place
without making a copy of the array.

Example 1:
Input: nums = [0,1,0,3,12]
Output: [1,3,12,0,0]
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void moveZeroes(vector<int> &nums) {
    int l = 0;
    if (nums.size() == 1)
        return;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] != 0) {
            swap(nums[i], nums[l]);
            ++l;
        }
    }
}

int main() {
    vector<int> question = {0, 0, 1};
    moveZeroes(question);
    for (int i : question) {
        cout << i << endl;
    }
}

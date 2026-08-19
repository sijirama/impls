/*
46. Permutations
Given an array nums of distinct integers, return all the possible permutations.
You can return the answer in any order. Example 1: Input: nums = [1,2,3] Output:
[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> permute(vector<int> &nums) {
    vector<vector<int>> Result;
    if (nums.size() <= 1)
        return {nums};

    if (nums.size() == 2) {
        Result.emplace_back(nums);
        sort(nums.rbegin(), nums.rend());
        Result.emplace_back(nums);
        return Result;
    }

    for (int i = 0; i < nums.size(); ++i) {

        vector<int> tempSorted;
        tempSorted.emplace_back(nums[i]);
        for (int j = 0; j < nums.size(); ++j) {
            if (i == j)
                continue;
            tempSorted.emplace_back(nums[j]);
        }
        Result.emplace_back(tempSorted);

        vector<int> tempOppSorted;
        tempOppSorted.emplace_back(nums[i]);
        for (int j = nums.size() - 1; j >= 0; --j) {
            if (i == j)
                continue;
            tempOppSorted.emplace_back(nums[j]);
        }
        Result.emplace_back(tempOppSorted);
    }

    return Result;
}

int main() {
    vector<int> ques = {1, 2};
    vector<vector<int>> ans = permute(ques);
    for (vector<int> i : ans) {
        cout << "[";
        for (int j : i) {
            cout << j << " ";
        }
        cout << "]";
    }
}

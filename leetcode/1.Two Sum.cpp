/*
Given an array of integers nums and an integer target, return indices of the two
numbers such that they add up to target. You may assume that each input would
have exactly one solution, and you may not use the same element twice. You can
return the answer in any order. Example 1: Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

vector<int> twoSum(vector<int> &nums, int target);

int main() {
  vector<int> Answer = {3, 2, 4};
  int target = 6;
  auto ans = twoSum(Answer, target);
  for (auto i : ans) {
    cout << i << ", ";
  }
}

vector<int> twoSum(vector<int> &nums, int target) {
  vector<int> Answer;

  for (int i = 0; i < nums.size(); ++i) {
    int num1 = nums[i];

    for (int j = 0; j < nums.size(); ++j) {
      if (j == i)
        continue;

      if (nums[i] + nums[j] == target) {
        return vector<int>{i, j};
      }
    }
  }

  return Answer;
}

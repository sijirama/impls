
/*
Given an array of integers nums containing n + 1 integers where each integer is
in the range [1, n] inclusive. There is only one repeated number in nums, return
this repeated number. You must solve the problem without modifying the array
nums and uses only constant extra space.
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

int findDuplicate(vector<int> &nums) {
    int ans = nums[0];
    int count = 1;

    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size() - 1; ++i) {
        if (nums[i] == nums[i + 1]) {
            ++count;
        } else {
            count = 1;
        }
        if (count == 2) {
            ans = nums[i];
        }
    }

    if (nums[nums.size() - 1] == ans) {
        ++count;
        ans = nums[nums.size() - 1];
    }

    cout << "Count is: " << count << endl;
    return ans;
}

int main() {
    vector<int> ques = {3, 1, 3, 4, 2};
    int ans = findDuplicate(ques);
    cout << "Final Answer is: " << ans << endl;
}

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> sortedSquares(vector<int> &nums) {
    auto cmp = [](int a, int b) { return abs(a) < abs(b); };
    sort(nums.begin(), nums.end(), cmp);
    for (int i = 0; i < nums.size(); i++) {
        nums[i] = abs(nums[i]) * abs(nums[i]);
    }
    return nums;
}

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void selsort(vector<int> &nums) {
    int n = nums.size();
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i; j < n; j++) {
            if (nums[j] < nums[min]) {
                min = j;
            }
        }
        if (min != i) {
            swap(nums[i], nums[min]);
        }
    }
}

int maxProduct(vector<int> &nums) {
    int size = nums.size();
    // sort(nums.begin(), nums.end());
    selsort(nums);
    int i = (nums[size - 1] - 1) * (nums[size - 2] - 1);
    return i;
}

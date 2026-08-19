#include <algorithm>
#include <vector>
using namespace std;

int numIdenticalPairs(vector<int> &nums) {
    int answer = 0;

    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size(); i++) {
        for (int j = i; j < nums.size(); j++) {
            if (i == j) {
                continue;
            }
            if (nums[i] == nums[j]) {
                answer++;
            }
        }
    }

    return answer;
}

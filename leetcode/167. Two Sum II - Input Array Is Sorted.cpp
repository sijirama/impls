#include <vector>

using namespace std;

vector<int> twoSum(vector<int> &numbers, int target) {
    vector<int> ans;
    for (int i = 0; i < numbers.size(); ++i) {
        for (int j = i; j < numbers.size(); ++j) {
            if (i == j) {
                continue;
            }
            if ((numbers[i] + numbers[j]) == target) {
                ans.push_back(i + 1);
                ans.push_back(j + 1);
                return ans;
            }
        }
    }
    return ans;
}

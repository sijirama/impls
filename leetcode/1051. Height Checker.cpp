#include <algorithm>
#include <vector>
using namespace std;

int heightChecker(vector<int> &heights) {
    vector<int> A = {heights.begin(), heights.end()};
    sort(A.begin(), A.end());
    int ans = 0;
    for (int i = 0; i < heights.size(); i++) {
        if (heights[i] != A[i]) {
            ans += 1;
        }
    }
    return ans;
}

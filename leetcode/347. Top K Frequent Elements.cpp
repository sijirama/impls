#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <vector>

using namespace std;

vector<int> topKFrequent(vector<int> &nums, int k) {
    vector<int> ans;
    map<int, int> M;
    for (int i : nums) {
        M[i] += 1;
    }
    vector<pair<int, int>> vec = {M.begin(), M.end()};

    auto cmp = [](pair<int, int> a, pair<int, int> b) {
        return a.second < b.second;
    };

    sort(vec.begin(), vec.end(), cmp);
    for (int i = 0; i < k; i++) {
        ans.push_back(vec[i].first);
    }

    return ans;
}

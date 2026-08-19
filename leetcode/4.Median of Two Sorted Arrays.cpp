

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2);

int main() {
    vector<int> question = {1};
    vector<int> question2 = {};
    auto num = findMedianSortedArrays(question, question2);
    cout << num << endl;
}

double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
    for (int i : nums2) {
        nums1.push_back(i);
    }
    sort(nums1.begin(), nums1.end());

    for (int i : nums1) {
        cout << i << ", ";
    }
    cout << endl;

    if (nums1.size() % 2 != 0) {
        return nums1[nums1.size() / 2];
    } else {
        double val1 = nums1[(nums1.size() / 2) - 1];
        double val2 = nums1[(nums1.size() / 2)];
        double ans = (val1 + val2) / 2;
        return ans;
    }

    return 0;
}

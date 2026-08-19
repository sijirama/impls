#include <algorithm>
#include <iostream>
#include <limits.h>
#include <vector>

using namespace std;

int maxProfit(vector<int> &prices) {

    int maxe = 0;
    int pist = 0;
    int lsf = INT_MAX;

    for (int i = 0; i < prices.size(); ++i) {
        if (prices[i] < lsf) {
            lsf = prices[i];
        }
        pist = prices[i] - lsf;
        if (maxe < pist) {
            maxe = pist;
        }
    }

    return maxe;
}

int main() {
    vector<int> que = {7, 1, 5, 3, 6, 4};
    // vector<int> que = {7, 6, 4, 3, 1};
    cout << maxProfit(que);
}

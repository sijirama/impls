#include <vector>
using namespace std;

vector<int> sortArrayByParity(vector<int> &nums) {
    vector<int> E, O;

    for (int i : nums) {
        if (i % 2 == 0) {
            E.push_back(i);
        } else {
            O.push_back(i);
        }
    }

    vector<int> A = {E.begin(), E.end()};
    for (int i : O) {
        A.push_back(i);
    }

    return A;
}
